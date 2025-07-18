// 二级API类型定义

// api_lv2_1接口
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
}

// api_lv2_2接口
export interface APILv2_2 {
  /**
   * 获取32位整数
   * @returns 返回32位整数
   */
  getInt32(): number;

  /**
   * 两个32位整数相加
   * @param a 第一个数
   * @param b 第二个数
   * @returns 返回两数之和
   */
  addInt32(a: number, b: number): number;

  /**
   * 获取双精度浮点数
   * @returns 返回双精度浮点数
   */
  getDouble(): number;

  /**
   * 获取状态字符串
   * @returns 返回状态字符串
   */
  getStatus(): string;
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

  /**
   * 获取二级API2对象
   * @returns 返回api_lv2_2对象
   */
  getLv2_2(): APILv2_2;
}

// 导出默认模块
declare const api: MainAPI;
export default api; 