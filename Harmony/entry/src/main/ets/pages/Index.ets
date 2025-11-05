/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * Harmony SDK Integration - UI Implementation
 */
import { promptAction } from '@kit.ArkUI';
import { BusinessError } from '@kit.BasicServicesKit';
import { resourceManager } from '@kit.LocalizationKit';
import autelSdk from 'libautel_sdk.so';
import Logger from '../common/utils/Logger';

@Entry
@Component
struct Index {
  @State sdkVersion: string = 'Unknown';
  @State sdkFullVersion: string = 'Unknown';
  @State isInitialized: boolean = false;
  @State statusMessage: string = 'SDK not initialized';
  @State isLoading: boolean = false;
  private resMgr: resourceManager.ResourceManager = this.getUIContext().getHostContext()!.resourceManager;

  @Styles
  customButtonStyle() {
    .width('288vp')
    .height('40vp')
    .margin({ bottom: '12vp' })
  }

  @Styles
  statusTextStyle() {
    .margin({ bottom: '16vp' })
  }

  @Styles
  titleStyle() {
    .margin({ bottom: '24vp' })
  }

  customToast(str: string) {
    Logger.info('Harmony SDK: ' + str);
    try {
      this.getUIContext().getPromptAction().showToast({
        message: str,
        duration: 2000,
        bottom: '80vp',
        backgroundColor: Color.White,
        backgroundBlurStyle: BlurStyle.NONE
      })
    } catch (error) {
      let message = (error as BusinessError).message;
      let code = (error as BusinessError).code;
      Logger.error(`showToast args error code is ${code}, message is ${message}`);
    }
  }

  async initSdk() {
    const result: number = await autelSdk.nativeAdd(1, 1)
    this.statusMessage = `nativeAdd: ${result}`

    return

    this.isLoading = true;
    this.statusMessage = this.resMgr.getStringSync($r('app.string.status_initializing'));

    try {
      Logger.info('Harmony SDK: initSdk');
      const result = await autelSdk.initAutelSdk(true); // Enable debug mode
      if (result.success) {
        this.isInitialized = true;
        this.statusMessage = this.resMgr.getStringSync($r('app.string.status_initialized'));
        this.customToast(this.resMgr.getStringSync($r('app.string.status_initialized')));

        // Get SDK version after initialization
        await this.getSdkVersion();
      } else {
        this.statusMessage = `SDK initialization failed: ${result.message}`;
        this.customToast(`SDK initialization failed: ${result.message}`);
      }
    } catch (error) {
      this.statusMessage = `SDK initialization error: ${error}`;
      this.customToast(`SDK initialization error: ${error}`);
    } finally {
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
        this.statusMessage = `${this.resMgr.getStringSync($r('app.string.label_sdk_version'))}: ${result.version}`;
        if (fullVersionResult.success)
        {
          this.sdkFullVersion = fullVersionResult.fullVersion;
          this.statusMessage = `${this.resMgr.getStringSync($r('app.string.label_sdk_full_version'))}: ${fullVersionResult.fullVersion}`;
        }
      } else {
        this.statusMessage = `Failed to get version: ${result.message}`;
      }
    } catch (error) {
      this.statusMessage = `Version error: ${error}`;
    }
  }

  async registerApp() {
    if (!this.isInitialized) {
      this.customToast('SDK not initialized');
      return;
    }

    this.isLoading = true;
    this.statusMessage = this.resMgr.getStringSync($r('app.string.status_registering'));
  }

  async destroySdk() {
    if (!this.isInitialized) {
      this.customToast('SDK not initialized');
      return;
    }

    this.isLoading = true;
    this.statusMessage = this.resMgr.getStringSync($r('app.string.status_destroying'));

    try {
      Logger.info('Harmony SDK: destroySdk');
      const result = await autelSdk.destroySdk();
      if (result.success) {
        this.isInitialized = false;
        this.sdkVersion = 'Unknown';
        this.sdkFullVersion = 'Unknown';
        this.statusMessage = this.resMgr.getStringSync($r('app.string.status_destroyed'));
        this.customToast(this.resMgr.getStringSync($r('app.string.status_destroyed')));
      } else {
        this.statusMessage = `SDK destruction failed: ${result.message}`;
        this.customToast(`SDK destruction failed: ${result.message}`);
      }
    } catch (error) {
      this.statusMessage = `SDK destruction error: ${error}`;
      this.customToast(`SDK destruction error: ${error}`);
    } finally {
      this.isLoading = false;
    }
  }

  build() {
    Column({ space: 12 }) {
      // Title
      Text(this.resMgr.getStringSync($r('app.string.app_title')))
        .titleStyle()
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)

      // Status Display
      Text(this.statusMessage)
        .statusTextStyle()
        .fontSize(14)
        .fontColor('#666666')
        .textAlign(TextAlign.Center)

      // SDK Version Display
      if (this.sdkVersion !== 'Unknown') {
        Text(`${this.resMgr.getStringSync($r('app.string.label_sdk_version'))}: ${this.sdkVersion}`)
          .statusTextStyle()
          .fontSize(14)
          .fontColor('#666666')
          .textAlign(TextAlign.Center)
      }

      // SDK Version Display
      if (this.sdkFullVersion !== 'Unknown') {
        Text(`${this.resMgr.getStringSync($r('app.string.label_sdk_full_version'))}: ${this.sdkFullVersion}`)
          .statusTextStyle()
          .fontSize(14)
          .fontColor('#666666')
          .textAlign(TextAlign.Center)
      }

      // Loading Indicator
      if (this.isLoading) {
        LoadingProgress()
          .width(24)
          .height(24)
          .margin({ bottom: '16vp' })
      }

      // SDK Management Buttons
      Button(this.resMgr.getStringSync($r('app.string.button_init_sdk')))
        .customButtonStyle()
        .enabled(!this.isInitialized && !this.isLoading)
        .onClick(() => {
          this.initSdk();
        })

      Button(this.resMgr.getStringSync($r('app.string.button_get_version')))
        .customButtonStyle()
        .enabled(this.isInitialized && !this.isLoading)
        .onClick(() => {
          this.getSdkVersion();
        })


      Button(this.resMgr.getStringSync($r('app.string.button_destroy_sdk')))
        .customButtonStyle()
        .enabled(this.isInitialized && !this.isLoading)
        .onClick(() => {
          this.destroySdk();
        })

      // Spacer
      Blank()
        .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF1F3F5)
    .justifyContent(FlexAlign.Start)
    .alignItems(HorizontalAlign.Center)
    .padding({ top: '24vp', left: '16vp', right: '16vp', bottom: '24vp' })
    .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM])
  }
}

function requireNativeModule(arg0: string) {
  throw new Error('Function not implemented.');
}
