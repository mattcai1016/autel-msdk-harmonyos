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
 * 最佳实践：Native侧实现autelsdk集成
 */
import { resourceManager } from '@kit.LocalizationKit';

// 定义返回对象的类型
export interface NativeResult {
  success: boolean;
  message: string;
  [key: string]: any; // 动态键值对
}

export const initAutelSdk: (bl: Boolean) => NativeResult;
export const getSdkVersion: () => NativeResult;
export const getSdkFullVersion: () => NativeResult;
export const isSdkValidate: () => NativeResult;
export const getGimbalType: () => NativeResult;
export const destroySdk: () => NativeResult;
