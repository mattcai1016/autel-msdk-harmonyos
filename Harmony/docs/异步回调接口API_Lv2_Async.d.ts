// 异步二级API类型定义

// 异步完成回调接口
export interface IComplete<T> {
  /**
   * 操作成功回调
   * @param result 操作结果
   */
  success(result: T): void;

  /**
   * 操作失败回调
   * @param error 错误信息
   */
  failure(error: string): void;
}

// 异步回调函数类型
export type SuccessCallback<T> = (result: T) => void;
export type FailureCallback = (error: string) => void;

// api_lv2_1接口（包含异步操作）
export interface APILv2_1 {
  /**
   * 获取字符串
   * @returns 返回字符串
   */
  getString(): string;

  /**
   * 获取带参数的字符串
   * @param param 参数
   * @returns 返回带参数的字符串
   */
  getStringWithParam(param: string): string;

  /**
   * 获取字符串长度
   * @param str 输入字符串
   * @returns 返回字符串长度
   */
  getStringLength(str: string): number;

  /**
   * 异步操作
   * @param state 操作状态
   * @param successCallback 成功回调函数
   * @param failureCallback 失败回调函数
   * @returns 返回操作状态字符串
   */
  doSomething(
    state: number,
    successCallback: SuccessCallback<number>,
    failureCallback: FailureCallback
  ): string;
}

// 主API接口
export interface MainAPI {
  /**
   * 获取主API状态
   * @returns 返回主API状态字符串
   */
  getMainStatus(): string;

  /**
   * 初始化API
   * @returns 返回初始化是否成功
   */
  initialize(): boolean;

  /**
   * 获取二级API1对象
   * @returns 返回api_lv2_1对象
   */
  getLv2_1(): APILv2_1;
}

// Promise包装的异步操作接口
export interface AsyncAPILv2_1 {
  /**
   * Promise版本的异步操作
   * @param state 操作状态
   * @returns Promise<number> 操作结果
   */
  doSomethingAsync(state: number): Promise<number>;

  /**
   * 带超时的异步操作
   * @param state 操作状态
   * @param timeoutMs 超时时间（毫秒）
   * @returns Promise<number> 操作结果
   */
  doSomethingWithTimeout(state: number, timeoutMs: number): Promise<number>;

  /**
   * 带重试的异步操作
   * @param state 操作状态
   * @param maxRetries 最大重试次数
   * @returns Promise<number> 操作结果
   */
  doSomethingWithRetry(state: number, maxRetries?: number): Promise<number>;

  /**
   * 批量异步操作
   * @param states 操作状态数组
   * @returns Promise<number[]> 操作结果数组
   */
  performBatchAsyncOperations(states: number[]): Promise<number[]>;

  /**
   * 并发异步操作
   * @param states 操作状态数组
   * @returns Promise<number[]> 操作结果数组
   */
  performConcurrentAsyncOperations(states: number[]): Promise<number[]>;
}

// 高级用法管理器
export interface APILv2AsyncManager {
  /**
   * 获取管理器实例
   * @returns 管理器实例
   */
  getInstance(): APILv2AsyncManager;

  /**
   * Promise包装的异步操作
   * @param state 操作状态
   * @returns Promise<number> 操作结果
   */
  doSomethingAsync(state: number): Promise<number>;

  /**
   * 批量异步操作
   * @param states 操作状态数组
   * @returns Promise<number[]> 操作结果数组
   */
  performBatchAsyncOperations(states: number[]): Promise<number[]>;

  /**
   * 并发异步操作
   * @param states 操作状态数组
   * @returns Promise<number[]> 操作结果数组
   */
  performConcurrentAsyncOperations(states: number[]): Promise<number[]>;

  /**
   * 带超时的异步操作
   * @param state 操作状态
   * @param timeoutMs 超时时间（毫秒）
   * @returns Promise<number> 操作结果
   */
  doSomethingWithTimeout(state: number, timeoutMs: number): Promise<number>;

  /**
   * 带重试的异步操作
   * @param state 操作状态
   * @param maxRetries 最大重试次数
   * @returns Promise<number> 操作结果
   */
  doSomethingWithRetry(state: number, maxRetries?: number): Promise<number>;

  /**
   * 错误处理工具
   * @param operation 异步操作函数
   * @returns Promise<any> 操作结果
   */
  handleAsyncError(operation: () => Promise<any>): Promise<any>;

  /**
   * 性能测试
   * @param iterations 测试迭代次数
   * @returns Promise<void>
   */
  performanceTest(iterations?: number): Promise<void>;
}

// 导出默认模块
declare const api: MainAPI;
export default api; 