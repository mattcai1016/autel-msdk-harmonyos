if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
interface Index_Params {
    sdkVersion?: string;
    sdkFullVersion?: string;
    isInitialized?: boolean;
    statusMessage?: string;
    isLoading?: boolean;
    resMgr?: resourceManager.ResourceManager;
}
import type { BusinessError as BusinessError } from "@ohos:base";
import type resourceManager from "@ohos:resourceManager";
import autelSdk from "@normalized:Y&&&libautel_sdk.so&";
import Logger from "@normalized:N&&&entry/src/main/ets/common/utils/Logger&";
class Index extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__sdkVersion = new ObservedPropertySimplePU('Unknown', this, "sdkVersion");
        this.__sdkFullVersion = new ObservedPropertySimplePU('Unknown', this, "sdkFullVersion");
        this.__isInitialized = new ObservedPropertySimplePU(false, this, "isInitialized");
        this.__statusMessage = new ObservedPropertySimplePU('SDK not initialized', this, "statusMessage");
        this.__isLoading = new ObservedPropertySimplePU(false, this, "isLoading");
        this.resMgr = this.getUIContext().getHostContext()!.resourceManager;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params: Index_Params) {
        if (params.sdkVersion !== undefined) {
            this.sdkVersion = params.sdkVersion;
        }
        if (params.sdkFullVersion !== undefined) {
            this.sdkFullVersion = params.sdkFullVersion;
        }
        if (params.isInitialized !== undefined) {
            this.isInitialized = params.isInitialized;
        }
        if (params.statusMessage !== undefined) {
            this.statusMessage = params.statusMessage;
        }
        if (params.isLoading !== undefined) {
            this.isLoading = params.isLoading;
        }
        if (params.resMgr !== undefined) {
            this.resMgr = params.resMgr;
        }
    }
    updateStateVars(params: Index_Params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__sdkVersion.purgeDependencyOnElmtId(rmElmtId);
        this.__sdkFullVersion.purgeDependencyOnElmtId(rmElmtId);
        this.__isInitialized.purgeDependencyOnElmtId(rmElmtId);
        this.__statusMessage.purgeDependencyOnElmtId(rmElmtId);
        this.__isLoading.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__sdkVersion.aboutToBeDeleted();
        this.__sdkFullVersion.aboutToBeDeleted();
        this.__isInitialized.aboutToBeDeleted();
        this.__statusMessage.aboutToBeDeleted();
        this.__isLoading.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    private __sdkVersion: ObservedPropertySimplePU<string>;
    get sdkVersion() {
        return this.__sdkVersion.get();
    }
    set sdkVersion(newValue: string) {
        this.__sdkVersion.set(newValue);
    }
    private __sdkFullVersion: ObservedPropertySimplePU<string>;
    get sdkFullVersion() {
        return this.__sdkFullVersion.get();
    }
    set sdkFullVersion(newValue: string) {
        this.__sdkFullVersion.set(newValue);
    }
    private __isInitialized: ObservedPropertySimplePU<boolean>;
    get isInitialized() {
        return this.__isInitialized.get();
    }
    set isInitialized(newValue: boolean) {
        this.__isInitialized.set(newValue);
    }
    private __statusMessage: ObservedPropertySimplePU<string>;
    get statusMessage() {
        return this.__statusMessage.get();
    }
    set statusMessage(newValue: string) {
        this.__statusMessage.set(newValue);
    }
    private __isLoading: ObservedPropertySimplePU<boolean>;
    get isLoading() {
        return this.__isLoading.get();
    }
    set isLoading(newValue: boolean) {
        this.__isLoading.set(newValue);
    }
    private resMgr: resourceManager.ResourceManager;
    customToast(str: string) {
        Logger.info('Harmony SDK: ' + str);
        try {
            this.getUIContext().getPromptAction().showToast({
                message: str,
                duration: 2000,
                bottom: '80vp',
                backgroundColor: Color.White,
                backgroundBlurStyle: BlurStyle.NONE
            });
        }
        catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            Logger.error(`showToast args error code is ${code}, message is ${message}`);
        }
    }
    async initSdk() {
        this.isLoading = true;
        this.statusMessage = this.resMgr.getStringSync({ "id": 16777233, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" });
        try {
            Logger.info('Harmony SDK: initSdk');
            const result = await autelSdk.initAutelSdk(true); // Enable debug mode
            if (result.success) {
                this.isInitialized = true;
                this.statusMessage = this.resMgr.getStringSync({ "id": 16777232, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" });
                this.customToast(this.resMgr.getStringSync({ "id": 16777232, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" }));
                // Get SDK version after initialization
                await this.getSdkVersion();
            }
            else {
                this.statusMessage = `SDK initialization failed: ${result.message}`;
                this.customToast(`SDK initialization failed: ${result.message}`);
            }
        }
        catch (error) {
            this.statusMessage = `SDK initialization error: ${error}`;
            this.customToast(`SDK initialization error: ${error}`);
        }
        finally {
            this.isLoading = false;
        }
    }
    async getSdkVersion() {
        if (!this.isInitialized) {
            this.customToast('SDK not initialized');
            return;
        }
        try {
            Logger.info('Harmony SDK: getSdkVersion');
            const result = await autelSdk.getSdkVersion();
            const fullVersionResult = await autelSdk.getSdkFullVersion();
            if (result.success) {
                this.sdkVersion = result.version;
                this.statusMessage = `${this.resMgr.getStringSync({ "id": 16777228, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" })}: ${result.version}`;
                if (fullVersionResult.success) {
                    this.sdkFullVersion = fullVersionResult.fullVersion;
                    this.statusMessage = `${this.resMgr.getStringSync({ "id": 16777227, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" })}: ${fullVersionResult.fullVersion}`;
                }
            }
            else {
                this.statusMessage = `Failed to get version: ${result.message}`;
            }
        }
        catch (error) {
            this.statusMessage = `Version error: ${error}`;
        }
    }
    async registerApp() {
        if (!this.isInitialized) {
            this.customToast('SDK not initialized');
            return;
        }
        this.isLoading = true;
        this.statusMessage = this.resMgr.getStringSync({ "id": 16777238, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" });
    }
    async destroySdk() {
        if (!this.isInitialized) {
            this.customToast('SDK not initialized');
            return;
        }
        this.isLoading = true;
        this.statusMessage = this.resMgr.getStringSync({ "id": 16777231, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" });
        try {
            Logger.info('Harmony SDK: destroySdk');
            const result = await autelSdk.destroySdk();
            if (result.success) {
                this.isInitialized = false;
                this.sdkVersion = 'Unknown';
                this.sdkFullVersion = 'Unknown';
                this.statusMessage = this.resMgr.getStringSync({ "id": 16777230, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" });
                this.customToast(this.resMgr.getStringSync({ "id": 16777230, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" }));
            }
            else {
                this.statusMessage = `SDK destruction failed: ${result.message}`;
                this.customToast(`SDK destruction failed: ${result.message}`);
            }
        }
        catch (error) {
            this.statusMessage = `SDK destruction error: ${error}`;
            this.customToast(`SDK destruction error: ${error}`);
        }
        finally {
            this.isLoading = false;
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: 12 });
            Column.width('100%');
            Column.height('100%');
            Column.backgroundColor(0xF1F3F5);
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Center);
            Column.padding({ top: '24vp', left: '16vp', right: '16vp', bottom: '24vp' });
            Column.expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM]);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            // Title
            Text.create(this.resMgr.getStringSync({ "id": 16777220, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" }));
            // Title
            Text.margin({ bottom: '24vp' });
            // Title
            Text.fontSize(20);
            // Title
            Text.fontWeight(FontWeight.Bold);
            // Title
            Text.textAlign(TextAlign.Center);
        }, Text);
        // Title
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            // Status Display
            Text.create(this.statusMessage);
            // Status Display
            Text.margin({ bottom: '16vp' });
            // Status Display
            Text.fontSize(14);
            // Status Display
            Text.fontColor('#666666');
            // Status Display
            Text.textAlign(TextAlign.Center);
        }, Text);
        // Status Display
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            // SDK Version Display
            if (this.sdkVersion !== 'Unknown') {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(`${this.resMgr.getStringSync({ "id": 16777228, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" })}: ${this.sdkVersion}`);
                        Text.margin({ bottom: '16vp' });
                        Text.fontSize(14);
                        Text.fontColor('#666666');
                        Text.textAlign(TextAlign.Center);
                    }, Text);
                    Text.pop();
                });
            }
            // SDK Version Display
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            // SDK Version Display
            if (this.sdkFullVersion !== 'Unknown') {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(`${this.resMgr.getStringSync({ "id": 16777227, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" })}: ${this.sdkFullVersion}`);
                        Text.margin({ bottom: '16vp' });
                        Text.fontSize(14);
                        Text.fontColor('#666666');
                        Text.textAlign(TextAlign.Center);
                    }, Text);
                    Text.pop();
                });
            }
            // Loading Indicator
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            // Loading Indicator
            if (this.isLoading) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        LoadingProgress.create();
                        LoadingProgress.width(24);
                        LoadingProgress.height(24);
                        LoadingProgress.margin({ bottom: '16vp' });
                    }, LoadingProgress);
                });
            }
            // SDK Management Buttons
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            // SDK Management Buttons
            Button.createWithLabel(this.resMgr.getStringSync({ "id": 16777224, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" }));
            // SDK Management Buttons
            Button.width('288vp');
            // SDK Management Buttons
            Button.height('40vp');
            // SDK Management Buttons
            Button.margin({ bottom: '12vp' });
            // SDK Management Buttons
            Button.enabled(!this.isInitialized && !this.isLoading);
            // SDK Management Buttons
            Button.onClick(() => {
                this.initSdk();
            });
        }, Button);
        // SDK Management Buttons
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel(this.resMgr.getStringSync({ "id": 16777223, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" }));
            Button.width('288vp');
            Button.height('40vp');
            Button.margin({ bottom: '12vp' });
            Button.enabled(this.isInitialized && !this.isLoading);
            Button.onClick(() => {
                this.getSdkVersion();
            });
        }, Button);
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel(this.resMgr.getStringSync({ "id": 16777222, "type": 10003, params: [], "bundleName": "com.samples.MsdkHarmony", "moduleName": "entry" }));
            Button.width('288vp');
            Button.height('40vp');
            Button.margin({ bottom: '12vp' });
            Button.enabled(this.isInitialized && !this.isLoading);
            Button.onClick(() => {
                this.destroySdk();
            });
        }, Button);
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            // Spacer
            Blank.create();
            // Spacer
            Blank.layoutWeight(1);
        }, Blank);
        // Spacer
        Blank.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
    static getEntryName(): string {
        return "Index";
    }
}
function requireNativeModule(arg0: string) {
    throw new Error('Function not implemented.');
}
registerNamedRoute(() => new Index(undefined, {}), "", { bundleName: "com.samples.MsdkHarmony", moduleName: "entry", pagePath: "pages/Index", pageFullPath: "entry/src/main/ets/pages/Index", integratedHsp: "false", moduleType: "followWithHap" });
