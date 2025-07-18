import hilog from '@ohos.hilog';
import api from 'libapi_lv2_async.so';

const TAG = '[APILv2AsyncDemo]';
const DOMAIN = 0x0001;

@Entry
@Component
struct APILv2AsyncDemo {
  @State mainStatus: string = 'unknown';
  @State syncResult: string = '';
  @State asyncResult: string = '';
  @State asyncStatus: string = 'idle';

  build() {
    Column() {
      Text('异步二级API演示')
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

      // 同步操作
      Button('测试同步方法')
        .width('80%')
        .height(50)
        .margin({ bottom: 10 })
        .onClick(() => this.testSyncMethods())

      // 异步操作
      Button('测试异步方法')
        .width('80%')
        .height(50)
        .margin({ bottom: 10 })
        .onClick(() => this.testAsyncMethods())

      // 状态显示
      Text(`主API状态: ${this.mainStatus}`)
        .fontSize(16)
        .margin({ top: 20, bottom: 10 })

      Text(`同步结果: ${this.syncResult}`)
        .fontSize(16)
        .margin({ bottom: 10 })

      Text(`异步状态: ${this.asyncStatus}`)
        .fontSize(16)
        .margin({ bottom: 10 })

      Text(`异步结果: ${this.asyncResult}`)
        .fontSize(16)
        .margin({ bottom: 10 })

      if (this.asyncStatus === 'running') {
        Progress({ value: 0, total: 100 })
          .width('80%')
          .height(20)
          .margin({ bottom: 10 })
      }
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

  // 测试同步方法
  testSyncMethods() {
    hilog.info(DOMAIN, TAG, '测试同步方法');
    
    try {
      const lv2_1 = api.getLv2_1();
      
      // 调用同步方法
      const str1 = lv2_1.getString();
      const str2 = lv2_1.getStringWithParam('World');
      const length = lv2_1.getStringLength('Hello World');
      
      this.syncResult = `getString: ${str1}, getStringWithParam: ${str2}, getStringLength: ${length}`;
      hilog.info(DOMAIN, TAG, '同步方法测试完成');
    } catch (error) {
      hilog.error(DOMAIN, TAG, '同步方法测试失败: %{public}s', error.message);
      this.syncResult = `错误: ${error.message}`;
    }
  }

  // 测试异步方法
  testAsyncMethods() {
    hilog.info(DOMAIN, TAG, '开始测试异步方法');
    this.asyncStatus = 'running';
    this.asyncResult = '';
    
    try {
      const lv2_1 = api.getLv2_1();
      
      // 调用异步方法
      const operationStatus = lv2_1.doSomething(10, 
        // 成功回调
        (result) => {
          hilog.info(DOMAIN, TAG, '异步操作成功: %{public}d', result);
          this.asyncStatus = 'success';
          this.asyncResult = `操作成功，结果: ${result}`;
        },
        // 失败回调
        (error) => {
          hilog.error(DOMAIN, TAG, '异步操作失败: %{public}s', error);
          this.asyncStatus = 'failed';
          this.asyncResult = `操作失败: ${error}`;
        }
      );
      
      hilog.info(DOMAIN, TAG, '异步操作状态: %{public}s', operationStatus);
    } catch (error) {
      hilog.error(DOMAIN, TAG, '异步方法调用失败: %{public}s', error.message);
      this.asyncStatus = 'error';
      this.asyncResult = `调用失败: ${error.message}`;
    }
  }
}

// 高级用法示例
class APILv2AsyncAdvancedUsage {
  private static instance: APILv2AsyncAdvancedUsage;
  private isInitialized: boolean = false;

  static getInstance(): APILv2AsyncAdvancedUsage {
    if (!APILv2AsyncAdvancedUsage.instance) {
      APILv2AsyncAdvancedUsage.instance = new APILv2AsyncAdvancedUsage();
    }
    return APILv2AsyncAdvancedUsage.instance;
  }

  // Promise包装异步操作
  async doSomethingAsync(state: number): Promise<number> {
    return new Promise((resolve, reject) => {
      const lv2_1 = api.getLv2_1();
      
      lv2_1.doSomething(state,
        (result) => {
          hilog.info(DOMAIN, TAG, 'Promise异步操作成功: %{public}d', result);
          resolve(result);
        },
        (error) => {
          hilog.error(DOMAIN, TAG, 'Promise异步操作失败: %{public}s', error);
          reject(new Error(error));
        }
      );
    });
  }

  // 批量异步操作
  async performBatchAsyncOperations(states: number[]): Promise<number[]> {
    const results: number[] = [];
    
    for (const state of states) {
      try {
        const result = await this.doSomethingAsync(state);
        results.push(result);
        hilog.info(DOMAIN, TAG, '批量操作完成: state=%{public}d, result=%{public}d', state, result);
      } catch (error) {
        hilog.error(DOMAIN, TAG, '批量操作失败: state=%{public}d, error=%{public}s', state, error.message);
        throw error;
      }
    }
    
    return results;
  }

  // 并发异步操作
  async performConcurrentAsyncOperations(states: number[]): Promise<number[]> {
    const promises = states.map(state => this.doSomethingAsync(state));
    
    try {
      const results = await Promise.all(promises);
      hilog.info(DOMAIN, TAG, '并发操作完成，结果: %{public}s', JSON.stringify(results));
      return results;
    } catch (error) {
      hilog.error(DOMAIN, TAG, '并发操作失败: %{public}s', error.message);
      throw error;
    }
  }

  // 带超时的异步操作
  async doSomethingWithTimeout(state: number, timeoutMs: number): Promise<number> {
    return Promise.race([
      this.doSomethingAsync(state),
      new Promise<never>((_, reject) => {
        setTimeout(() => {
          reject(new Error(`操作超时: ${timeoutMs}ms`));
        }, timeoutMs);
      })
    ]);
  }

  // 重试机制
  async doSomethingWithRetry(state: number, maxRetries: number = 3): Promise<number> {
    let lastError: Error;
    
    for (let i = 0; i < maxRetries; i++) {
      try {
        return await this.doSomethingAsync(state);
      } catch (error) {
        lastError = error as Error;
        hilog.warn(DOMAIN, TAG, '操作失败，重试第%{public}d次: %{public}s', i + 1, error.message);
        
        if (i < maxRetries - 1) {
          // 等待一段时间后重试
          await new Promise(resolve => setTimeout(resolve, 1000 * (i + 1)));
        }
      }
    }
    
    throw lastError;
  }

  // 错误处理工具
  handleAsyncError(operation: () => Promise<any>): Promise<any> {
    return operation().catch(error => {
      hilog.error(DOMAIN, TAG, '异步操作错误: %{public}s', error.message);
      // 可以在这里添加错误处理逻辑，如日志记录、错误上报等
      throw error;
    });
  }

  // 性能测试
  async performanceTest(iterations: number = 10): Promise<void> {
    const startTime = Date.now();
    const results: number[] = [];
    
    for (let i = 0; i < iterations; i++) {
      try {
        const result = await this.doSomethingAsync(i + 1);
        results.push(result);
      } catch (error) {
        hilog.error(DOMAIN, TAG, '性能测试失败: %{public}s', error.message);
      }
    }
    
    const endTime = Date.now();
    const duration = endTime - startTime;
    
    hilog.info(DOMAIN, TAG, '性能测试完成: %{public}d次操作耗时%{public}dms，成功率: %{public}d%%', 
               iterations, duration, (results.length / iterations) * 100);
  }
}

// 使用示例
export default APILv2AsyncDemo; 