import hilog from '@ohos.hilog';
import api from 'libapi_lv2.so';

const TAG = '[APILv2Demo]';
const DOMAIN = 0x0001;

@Entry
@Component
struct APILv2Demo {
  @State mainStatus: string = 'unknown';
  @State lv2_1Result: string = '';
  @State lv2_2Result: string = '';

  build() {
    Column() {
      Text('二级API演示')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      // 主API操作
      Button('获取主API状态')
        .width('80%')
        .height(50)
        .margin({ bottom: 10 })
        .onClick(() => this.getMainStatus())

      Button('初始化API')
        .width('80%')
        .height(50)
        .margin({ bottom: 10 })
        .onClick(() => this.initializeAPI())

      // 二级API1操作
      Button('测试api_lv2_1')
        .width('80%')
        .height(50)
        .margin({ bottom: 10 })
        .onClick(() => this.testLv2_1())

      // 二级API2操作
      Button('测试api_lv2_2')
        .width('80%')
        .height(50)
        .margin({ bottom: 10 })
        .onClick(() => this.testLv2_2())

      // 状态显示
      Text(`主API状态: ${this.mainStatus}`)
        .fontSize(16)
        .margin({ top: 20, bottom: 10 })

      Text(`api_lv2_1结果: ${this.lv2_1Result}`)
        .fontSize(16)
        .margin({ bottom: 10 })

      Text(`api_lv2_2结果: ${this.lv2_2Result}`)
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }

  // 获取主API状态
  getMainStatus() {
    hilog.info(DOMAIN, TAG, '获取主API状态');
    
    try {
      const status = api.getMainStatus();
      this.mainStatus = status;
      hilog.info(DOMAIN, TAG, '主API状态: %{public}s', status);
    } catch (error) {
      hilog.error(DOMAIN, TAG, '获取主API状态失败: %{public}s', error.message);
    }
  }

  // 初始化API
  initializeAPI() {
    hilog.info(DOMAIN, TAG, '初始化API');
    
    try {
      const result = api.initialize();
      hilog.info(DOMAIN, TAG, 'API初始化结果: %{public}s', result ? '成功' : '失败');
    } catch (error) {
      hilog.error(DOMAIN, TAG, 'API初始化失败: %{public}s', error.message);
    }
  }

  // 测试api_lv2_1
  testLv2_1() {
    hilog.info(DOMAIN, TAG, '测试api_lv2_1');
    
    try {
      const lv2_1 = api.getLv2_1();
      
      // 调用getString方法
      const str1 = lv2_1.getString();
      hilog.info(DOMAIN, TAG, 'getString结果: %{public}s', str1);
      
      // 调用getStringWithParam方法
      const str2 = lv2_1.getStringWithParam('World');
      hilog.info(DOMAIN, TAG, 'getStringWithParam结果: %{public}s', str2);
      
      // 调用getStringLength方法
      const length = lv2_1.getStringLength('Hello World');
      hilog.info(DOMAIN, TAG, 'getStringLength结果: %{public}d', length);
      
      this.lv2_1Result = `getString: ${str1}, getStringWithParam: ${str2}, getStringLength: ${length}`;
    } catch (error) {
      hilog.error(DOMAIN, TAG, '测试api_lv2_1失败: %{public}s', error.message);
      this.lv2_1Result = `错误: ${error.message}`;
    }
  }

  // 测试api_lv2_2
  testLv2_2() {
    hilog.info(DOMAIN, TAG, '测试api_lv2_2');
    
    try {
      const lv2_2 = api.getLv2_2();
      
      // 调用getInt32方法
      const int32 = lv2_2.getInt32();
      hilog.info(DOMAIN, TAG, 'getInt32结果: %{public}d', int32);
      
      // 调用addInt32方法
      const sum = lv2_2.addInt32(10, 20);
      hilog.info(DOMAIN, TAG, 'addInt32结果: %{public}d', sum);
      
      // 调用getDouble方法
      const doubleVal = lv2_2.getDouble();
      hilog.info(DOMAIN, TAG, 'getDouble结果: %{public}f', doubleVal);
      
      // 调用getStatus方法
      const status = lv2_2.getStatus();
      hilog.info(DOMAIN, TAG, 'getStatus结果: %{public}s', status);
      
      this.lv2_2Result = `getInt32: ${int32}, addInt32: ${sum}, getDouble: ${doubleVal}, getStatus: ${status}`;
    } catch (error) {
      hilog.error(DOMAIN, TAG, '测试api_lv2_2失败: %{public}s', error.message);
      this.lv2_2Result = `错误: ${error.message}`;
    }
  }
}

// 高级用法示例
class APILv2AdvancedUsage {
  private static instance: APILv2AdvancedUsage;
  private isInitialized: boolean = false;

  static getInstance(): APILv2AdvancedUsage {
    if (!APILv2AdvancedUsage.instance) {
      APILv2AdvancedUsage.instance = new APILv2AdvancedUsage();
    }
    return APILv2AdvancedUsage.instance;
  }

  // 链式调用示例
  async performCompleteTest(): Promise<void> {
    hilog.info(DOMAIN, TAG, '开始完整测试');
    
    // 1. 初始化API
    const initResult = api.initialize();
    if (!initResult) {
      throw new Error('API初始化失败');
    }
    this.isInitialized = true;
    
    // 2. 获取主API状态
    const mainStatus = api.getMainStatus();
    hilog.info(DOMAIN, TAG, '主API状态: %{public}s', mainStatus);
    
    // 3. 测试api_lv2_1
    const lv2_1 = api.getLv2_1();
    const lv2_1Results = {
      getString: lv2_1.getString(),
      getStringWithParam: lv2_1.getStringWithParam('Test'),
      getStringLength: lv2_1.getStringLength('Test String')
    };
    hilog.info(DOMAIN, TAG, 'api_lv2_1测试完成');
    
    // 4. 测试api_lv2_2
    const lv2_2 = api.getLv2_2();
    const lv2_2Results = {
      getInt32: lv2_2.getInt32(),
      addInt32: lv2_2.addInt32(5, 15),
      getDouble: lv2_2.getDouble(),
      getStatus: lv2_2.getStatus()
    };
    hilog.info(DOMAIN, TAG, 'api_lv2_2测试完成');
    
    // 5. 输出结果
    hilog.info(DOMAIN, TAG, '完整测试结果:');
    hilog.info(DOMAIN, TAG, '  api_lv2_1: %{public}s', JSON.stringify(lv2_1Results));
    hilog.info(DOMAIN, TAG, '  api_lv2_2: %{public}s', JSON.stringify(lv2_2Results));
  }

  // 批量操作示例
  async performBatchOperations(): Promise<void> {
    const operations = [
      () => this.testLv2_1Operations(),
      () => this.testLv2_2Operations(),
      () => this.testMainAPIOperations()
    ];

    for (const operation of operations) {
      try {
        await operation();
        hilog.info(DOMAIN, TAG, '操作完成');
      } catch (error) {
        hilog.error(DOMAIN, TAG, '操作失败: %{public}s', error.message);
        throw error;
      }
    }
  }

  private async testLv2_1Operations(): Promise<void> {
    const lv2_1 = api.getLv2_1();
    
    // 测试所有api_lv2_1方法
    const results = {
      getString: lv2_1.getString(),
      getStringWithParam: lv2_1.getStringWithParam('Batch Test'),
      getStringLength: lv2_1.getStringLength('Batch Test String')
    };
    
    hilog.info(DOMAIN, TAG, 'api_lv2_1批量测试结果: %{public}s', JSON.stringify(results));
  }

  private async testLv2_2Operations(): Promise<void> {
    const lv2_2 = api.getLv2_2();
    
    // 测试所有api_lv2_2方法
    const results = {
      getInt32: lv2_2.getInt32(),
      addInt32: lv2_2.addInt32(25, 35),
      getDouble: lv2_2.getDouble(),
      getStatus: lv2_2.getStatus()
    };
    
    hilog.info(DOMAIN, TAG, 'api_lv2_2批量测试结果: %{public}s', JSON.stringify(results));
  }

  private async testMainAPIOperations(): Promise<void> {
    // 测试主API方法
    const mainStatus = api.getMainStatus();
    const initResult = api.initialize();
    
    hilog.info(DOMAIN, TAG, '主API测试结果: status=%{public}s, init=%{public}s', 
               mainStatus, initResult ? 'true' : 'false');
  }

  // 错误处理示例
  handleAPIError(operation: () => any): any {
    try {
      return operation();
    } catch (error) {
      hilog.error(DOMAIN, TAG, 'API操作失败: %{public}s', error.message);
      // 可以在这里添加错误处理逻辑，如重试、降级等
      throw error;
    }
  }

  // 性能测试示例
  async performanceTest(): Promise<void> {
    const iterations = 1000;
    const startTime = Date.now();
    
    for (let i = 0; i < iterations; i++) {
      const lv2_1 = api.getLv2_1();
      const lv2_2 = api.getLv2_2();
      
      lv2_1.getString();
      lv2_2.getInt32();
    }
    
    const endTime = Date.now();
    const duration = endTime - startTime;
    
    hilog.info(DOMAIN, TAG, '性能测试完成: %{public}d次操作耗时%{public}dms', 
               iterations, duration);
  }
}

// 使用示例
export default APILv2Demo; 