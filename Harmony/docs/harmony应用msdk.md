# MSDK上HarmonyOS开发指南

## 概述
本文档介绍如何在HarmonyOS系统上使用C++ MSDK进行应用开发。

## 环境要求
1. **操作系统**：Windows 10以上
2. **硬盘空间**：至少100G可用空间
3. **内存**：至少16G RAM
4. **网络**：稳定的网络连接用于下载开发工具

### HarmonyOS版本与API Level对照表
| HarmonyOS版本 | API Level | 发布时间 | 主要特性 |
|--------------|-----------|----------|----------|
| HarmonyOS 5.0.5 | API 17 | 2024年 | 最新稳定版本，支持完整NAPI功能 |
| HarmonyOS 4.0 | API 9 | 2023年 | 基础NAPI支持 |
| HarmonyOS 3.1 | API 8 | 2022年 | 早期版本，功能有限 |

**注意**：本文档基于HarmonyOS 5.0.5 (API 17)编写，使用最新的NAPI功能和特性。

## 安装开发工具

### 1. 安装DevEco Studio
1. 访问华为开发者联盟官网：https://developer.harmonyos.com/
2. 下载DevEco Studio 5.0.5新版本
3. 运行安装程序，按提示完成安装
4. 首次启动时选择HarmonyOS开发模式

### 2. 安装HarmonyOS SDK
1. 打开DevEco Studio
2. 进入File → Settings → Appearance & Behavior → System Settings → HarmonyOS SDK
3. 点击"Download"下载SDK
4. 选择API版本（建议选择最新稳定版本）
5. 等待下载完成并安装

### 3. 安装NDK（Native Development Kit）
1. 在DevEco Studio中进入File → Settings → Appearance & Behavior → System Settings → HarmonyOS SDK
2. 选择"NDK"标签页
3. 下载并安装NDK工具链5.0.5
4. 配置NDK路径到环境变量

## 项目创建

### 1. 创建HarmonyOS项目
1. 打开DevEco Studio 5.0.5
2. 选择"Create HarmonyOS Project"
3. 选择项目模板：
   - **Empty Ability**：空白应用
   - **Native C++**：C++原生开发
   - **Service Ability**：服务应用
4. 配置项目信息：
   - **Project Name**：项目名称
   - **Bundle Name**：包名（如：com.example.myapp）
   - **Save Location**：项目保存路径
   - **Language**：选择C++
   - **Device Type**：选择目标设备类型
   - **API Version**：选择API 17（对应HarmonyOS 5.0.5）

### 2. 配置MSDK
1. 在`entry/src/main/cpp/`目录下创建MSDK相关文件
2. 在`entry/src/main/cpp/`目录下创建`CMakeLists.txt`文件
3. 配置CMake构建脚本：

```cmake
cmake_minimum_required(VERSION 3.4.1)
project(msdk_native)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件
add_library(msdk_native SHARED
    msdk_wrapper.cpp
    harmony_interface.cpp
)

# 包含头文件目录
target_include_directories(msdk_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接必要的库
target_link_libraries(msdk_native
    hilog_ndk.z
    ace_napi.z
)
```

## 代码结构

### 1. 项目目录结构（HarmonyOS 5.0.5）
```
MyHarmonyApp/
├── entry/                    # 应用入口模块
│   ├── src/
│   │   ├── main/
│   │   │   ├── cpp/         # C++源码目录
│   │   │   │   ├── CMakeLists.txt
│   │   │   │   ├── msdk_wrapper.cpp
│   │   │   │   ├── harmony_interface.cpp
│   │   │   │   └── include/ # 头文件目录
│   │   │   │       └── msdk_interface.h
│   │   │   ├── ets/         # ArkTS源码
│   │   │   │   ├── pages/
│   │   │   │   │   └── Index.ets
│   │   │   │   └── entryability/
│   │   │   │       └── EntryAbility.ets
│   │   │   ├── resources/   # 资源文件
│   │   │   │   ├── base/
│   │   │   │   │   ├── element/
│   │   │   │   │   ├── media/
│   │   │   │   │   └── profile/
│   │   │   │   └── rawfile/
│   │   │   └── module.json5 # 模块配置文件
│   │   └── ohosTest/        # 测试代码
│   │       └── ets/
│   │           └── test/
│   │               └── msdk_test.ets
│   ├── build-profile.json5  # 模块构建配置文件（原生模块配置）
│   └── oh-package.json5     # 模块包配置文件
├── oh_modules/              # 依赖模块
├── build-profile.json5      # 项目构建配置文件
├── hvigorfile.ts           # 构建脚本
└── oh-package.json5        # 项目配置文件
```

**重要文件说明：**
- **entry/build-profile.json5**: 模块级构建配置，包含原生模块的编译配置
- **build-profile.json5**: 项目级构建配置，包含应用级别的配置
- **CMakeLists.txt**: C++源码的CMake构建脚本

### 2. 模块配置文件
在`entry/src/main/module.json5`中配置：

```json
{
  "module": {
    "name": "entry",
    "type": "entry",
    "description": "$string:module_desc",
    "mainElement": "EntryAbility",
    "deviceTypes": [
      "phone",
      "tablet"
    ],
    "deliveryWithInstall": true,
    "installationFree": false,
    "pages": "$profile:main_pages",
    "abilities": [
      {
        "name": "EntryAbility",
        "srcEntry": "./ets/entryability/EntryAbility.ets",
        "description": "$string:EntryAbility_desc",
        "icon": "$media:icon",
        "label": "$string:EntryAbility_label",
        "startWindowIcon": "$media:icon",
        "startWindowBackground": "$color:start_window_background",
        "exported": true,
        "skills": [
          {
            "entities": [
              "entity.system.home"
            ],
            "actions": [
              "action.system.home"
            ]
          }
        ]
      }
    ],
    "requestPermissions": [
      {
        "name": "ohos.permission.INTERNET",
        "reason": "$string:internet_permission",
        "usedScene": {
          "abilities": [
            "EntryAbility"
          ],
          "when": "always"
        }
      },
      {
        "name": "ohos.permission.ACCESS_NETWORK_STATE",
        "reason": "$string:network_permission",
        "usedScene": {
          "abilities": [
            "EntryAbility"
          ],
          "when": "always"
        }
      }
    ]
  }
}
```
* 添加了网络权限配置
* 添加了必要的权限声明

### 3. 构建配置文件
在项目根目录的`build-profile.json5`中配置：

```json5
{
  "app": {
    "signingConfigs": [],
    "compileSdkVersion": 17,
    "compatibleSdkVersion": 17,
    "products": [
      {
        "name": "default",
        "signingConfig": "default"
      }
    ]
  },
  "modules": [
    {
      "name": "entry",
      "srcPath": "./entry",
      "targets": [
        {
          "name": "default",
          "applyToProducts": [
            "default"
          ]
        }
      ]
    }
  ]
}
```

**配置说明：**
- **compileSdkVersion**: 编译SDK版本，对应HarmonyOS 5.0.5 (API 17)
- **compatibleSdkVersion**: 兼容SDK版本，对应HarmonyOS 5.0.5 (API 17)
- **modules**: 模块配置，指定entry模块的路径和目标

### 4. MSDK包装器示例（更新版本）
```cpp
// entry/src/main/cpp/msdk_wrapper.cpp
#include <hilog/log.h>
#include <napi/native_api.h>
#include <uv.h>

#include "SdkApiManager.h" // AutelMobileSdk header

#define LOG_DOMAIN 0x0001 // dev: 0~0xFFFF sys: 0xD0|000|00~0xD0|FFF|FF
#define LOG_TAG "MSDK_WRAPPER"

static napi_value Init(napi_env env, napi_value exports) {
    // 初始化MSDK
    napi_property_descriptor desc[] = {
        {"initMSDK", nullptr, InitMSDK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"startRTK", nullptr, StartRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"stopRTK", nullptr, StopRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getRTKStatus", nullptr, GetRTKStatus, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

static napi_value InitMSDK(napi_env env, napi_callback_info info) {
    // MSDK初始化逻辑
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "MSDK初始化开始");
    
    // 获取传入参数
    size_t argc = 1;
    napi_value args[1];
    napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "获取参数失败");
        napi_value result;
        napi_get_boolean(env, false, &result);
        return result;
    }
    
    // 检查参数数量
    if (argc < 1) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "参数数量不足，需要传入isDebugMode参数");
        napi_value result;
        napi_get_boolean(env, false, &result);
        return result;
    }
    
    // 解析bool参数
    bool isDebugMode = false;
    status = napi_get_value_bool(env, args[0], &isDebugMode);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "参数类型错误，需要传入boolean类型");
        napi_value result;
        napi_get_boolean(env, false, &result);
        return result;
    }
    
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "调试模式: %{public}s", isDebugMode ? "开启" : "关闭");
    
    // 初始化MSDK
    SdkApiManager::GetInstance().Init(isDebugMode);
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "MSDK初始化完成");
    napi_value result;
    napi_get_boolean(env, initResult, &result);
    return result;
}

static napi_value StartRTK(napi_env env, napi_callback_info info) {
    // 启动RTK功能
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "启动RTK连接");
    
    // 实现RTK启动逻辑
    // 调用MSDK的RTK相关API
    
    napi_value result;
    napi_get_boolean(env, true, &result);
    return result;
}

static napi_value StopRTK(napi_env env, napi_callback_info info) {
    // 停止RTK功能
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "停止RTK连接");
    
    // 实现RTK停止逻辑
    
    napi_value result;
    napi_get_boolean(env, true, &result);
    return result;
}

static napi_value GetRTKStatus(napi_env env, napi_callback_info info) {
    // 获取RTK状态
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "获取RTK状态");
    
    // 创建返回对象
    napi_value status_obj;
    napi_create_object(env, &status_obj);
    
    // 添加状态属性
    napi_value connected;
    napi_get_boolean(env, true, &connected);
    napi_set_named_property(env, status_obj, "connected", connected);
    
    return status_obj;
}

// HarmonyOS 5.0.5 正确的模块导出方式
static napi_module msdk_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "msdk_native",
    .nm_priv = nullptr,
    .reserved = {nullptr}
};

extern "C" __attribute__((constructor)) void RegisterModule(void) {
    napi_module_register(&msdk_module);
}
```
* nodejs Api调用

### 5. HarmonyOS接口层（更新版本）
```cpp
// entry/src/main/cpp/harmony_interface.cpp
#include <hilog/log.h>
#include <ability_context.h>
#include <want.h>
#include <napi/native_api.h>

#define LOG_DOMAIN 0xD000D01
#define LOG_TAG "HARMONY_INTERFACE"

class HarmonyMSDKInterface {
public:
    static bool InitializeMSDK() {
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "HarmonyOS MSDK接口初始化");
        
        // 获取应用上下文
        auto context = AbilityContext::GetInstance();
        if (!context) {
            HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "无法获取应用上下文");
            return false;
        }
        
        // 初始化MSDK组件
        return InitializeMSDKComponents();
    }
    
    static bool StartRTKService() {
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "启动RTK服务");
        
        // 创建Want对象，启动RTK服务
        Want want;
        want.SetElementName("com.example.myapp", "RTKService");
        
        // 启动服务
        auto context = AbilityContext::GetInstance();
        if (context) {
            context->StartAbility(want);
            return true;
        }
        
        return false;
    }
    
    static napi_value CreateRTKService(napi_env env, napi_callback_info info) {
        // 创建RTK服务的NAPI接口
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "创建RTK服务");
        
        napi_value result;
        napi_get_boolean(env, StartRTKService(), &result);
        return result;
    }
    
private:
    static bool InitializeMSDKComponents() {
        // 初始化MSDK各个组件
        // 1. 初始化网络模块
        // 2. 初始化RTK模块
        // 3. 初始化数据存储模块
        
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "MSDK组件初始化完成");
        return true;
    }
};
```

## 编译和部署

### 1. 编译配置
在`entry/build-profile.json5`文件中配置原生模块编译：

```json5
{
  "apiType": "stageMode",
  "buildOption": {
    "externalNativeOptions": {
      "path": "./src/main/cpp/CMakeLists.txt",
      "arguments": "",
      "cppFlags": "-std=c++17",
      "cFlags": "-Wall",
      "abiFilters": [
        "arm64-v8a",
        "armeabi-v7a"
      ]
    }
  },
  "targets": [
    {
      "name": "default",
      "runtimeOS": "HarmonyOS"
    }
  ]
}
```

**配置参数说明：**
- **path**: CMake构建脚本路径，指向CMakeLists.txt文件
- **arguments**: CMake编译参数
- **cppFlags**: C++编译器参数，设置C++17标准
- **cFlags**: C编译器参数，启用警告
- **abiFilters**: 目标架构，支持arm64-v8a和armeabi-v7a

### 2. 编译项目
1. 在DevEco Studio中点击"Build" → "Build Hap(s)/APP(s)" → "Build App(s)"
2. 等待编译完成
3. 检查编译日志，确保没有错误

### 3. 部署到设备
1. 连接HarmonyOS设备或启动模拟器
2. 在DevEco Studio中点击"Run"按钮
3. 选择目标设备
4. 等待应用安装和启动

## 调试和测试

### 1. 日志调试
```cpp
#include <hilog/log.h>

// 使用HILOG进行日志输出
HILOG_INFO("信息日志");
HILOG_WARN("警告日志");
HILOG_ERROR("错误日志");
HILOG_DEBUG("调试日志");
```

### 2. 单元测试
创建测试文件`ohosTest/ets/test/msdk_test.ets`：

```typescript
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium';
import msdk from '@ohos.msdk';

export default function testSuite() {
  describe('MSDK功能测试', () => {
    it('MSDK初始化测试', 0, () => {
      let result = msdk.initMSDK();
      expect(result).assertTrue();
    });
    
    it('RTK启动测试', 0, () => {
      let result = msdk.startRTK();
      expect(result).assertTrue();
    });
  });
}
```

## 性能优化

### 1. 内存管理
```cpp
// 使用智能指针管理内存
#include <memory>

class MSDKManager {
private:
    std::unique_ptr<RTKConnection> rtkConnection;
    std::shared_ptr<DataProcessor> dataProcessor;
    
public:
    MSDKManager() {
        rtkConnection = std::make_unique<RTKConnection>();
        dataProcessor = std::make_shared<DataProcessor>();
    }
};
```

### 2. 异步处理
```cpp
#include <uv.h>

void AsyncRTKOperation(uv_work_t* req) {
    // 在后台线程执行RTK操作
    // 避免阻塞主线程
}

void CompleteRTKOperation(uv_work_t* req, int status) {
    // 操作完成后的回调
    // 更新UI或通知主线程
}
```

## 常见问题解决

### 1. 编译错误
- **问题**：CMake找不到头文件
- **解决**：检查`CMakeLists.txt`中的include路径配置

### 2. 配置文件问题
- **问题**：找不到`entry/build.gradle`文件
- **解决**：HarmonyOS 5.0.5使用`entry/build-profile.json5`配置原生模块，不再使用Gradle配置

### 3. 运行时错误
- **问题**：MSDK初始化失败
- **解决**：检查权限配置和网络连接

### 4. 性能问题
- **问题**：应用运行缓慢
- **解决**：使用异步操作和内存优化

## 参考资料

1. [HarmonyOS开发者文档](https://developer.harmonyos.com/cn/docs/documentation/doc-guides/start-overview-0000001053822404)
2. [NDK开发指南](https://developer.harmonyos.com/cn/docs/documentation/doc-guides/ndk-overview-0000001053822404)
3. [C++ API参考](https://developer.harmonyos.com/cn/docs/documentation/doc-references/cpp-0000001053822404)

## 更新日志

- **v1.0.0** (2025-07-15 14:00)：初始版本，包含基础MSDK集成
- **v1.1.0** (2025-07-15 15:30)：添加RTK功能支持
- **v1.2.0** (2025-07-15 16:45)：优化性能和内存管理
- **v1.3.0** (2025-07-15 18:00)：更新HarmonyOS 5.0.5配置方式，将Gradle配置替换为build-profile.json5配置

> **注意**：以上版本时间为示例时间，实际使用时请根据项目实际情况调整。当前文档更新时间：2025年7月15日。

### 6. 参数处理示例（完整版）
```cpp
// 处理多种参数类型的示例
static napi_value InitMSDKWithParams(napi_env env, napi_callback_info info) {
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "MSDK初始化开始（带参数）");
    
    // 获取参数信息
    size_t argc = 3; // 期望3个参数：isDebugMode, config, callback
    napi_value args[3];
    napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "获取参数失败");
        return CreateErrorResult(env, "参数获取失败");
    }
    
    // 检查参数数量
    if (argc < 1) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "参数数量不足，至少需要传入isDebugMode参数");
        return CreateErrorResult(env, "参数数量不足");
    }
    
    // 解析第一个参数：bool isDebugMode
    bool isDebugMode = false;
    status = napi_get_value_bool(env, args[0], &isDebugMode);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "第一个参数类型错误，需要传入boolean类型");
        return CreateErrorResult(env, "isDebugMode参数类型错误");
    }
    
    // 解析第二个参数：object config（可选）
    napi_value configObj = nullptr;
    if (argc >= 2) {
        bool isObject = false;
        status = napi_is_object(env, args[1], &isObject);
        if (status == napi_ok && isObject) {
            configObj = args[1];
            HILOG_INFO(LOG_DOMAIN, LOG_TAG, "检测到配置对象");
            
            // 从配置对象中提取具体参数
            napi_value serverUrl;
            status = napi_get_named_property(env, configObj, "serverUrl", &serverUrl);
            if (status == napi_ok) {
                char url[256];
                size_t urlLen;
                status = napi_get_value_string_utf8(env, serverUrl, url, sizeof(url), &urlLen);
                if (status == napi_ok) {
                    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "服务器地址: %{public}s", url);
                }
            }
            
            // 提取超时时间
            napi_value timeout;
            status = napi_get_named_property(env, configObj, "timeout", &timeout);
            if (status == napi_ok) {
                int32_t timeoutValue;
                status = napi_get_value_int32(env, timeout, &timeoutValue);
                if (status == napi_ok) {
                    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "超时时间: %{public}d ms", timeoutValue);
                }
            }
        }
    }
    
    // 解析第三个参数：function callback（可选）
    napi_value callback = nullptr;
    if (argc >= 3) {
        bool isFunction = false;
        status = napi_is_function(env, args[2], &isFunction);
        if (status == napi_ok && isFunction) {
            callback = args[2];
            HILOG_INFO(LOG_DOMAIN, LOG_TAG, "检测到回调函数");
        }
    }
    
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "调试模式: %{public}s", isDebugMode ? "开启" : "关闭");
    
    // 初始化MSDK
    bool initResult = SdkApiManager::GetInstance().Init(isDebugMode);
    
    // 如果有回调函数，异步调用
    if (callback != nullptr) {
        // 创建异步工作
        napi_value global;
        status = napi_get_global(env, &global);
        if (status == napi_ok) {
            napi_value argv[2];
            napi_get_boolean(env, initResult, &argv[0]);
            napi_create_string_utf8(env, initResult ? "初始化成功" : "初始化失败", NAPI_AUTO_LENGTH, &argv[1]);
            
            status = napi_call_function(env, global, callback, 2, argv, nullptr);
            if (status != napi_ok) {
                HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "回调函数调用失败");
            }
        }
    }
    
    // 返回结果
    napi_value result;
    napi_get_boolean(env, initResult, &result);
    return result;
}

// 创建错误结果的辅助函数
static napi_value CreateErrorResult(napi_env env, const char* message) {
    napi_value result;
    napi_get_boolean(env, false, &result);
    HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "%{public}s", message);
    return result;
}

// 在Init函数中注册新的方法
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"initMSDK", nullptr, InitMSDK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"initMSDKWithParams", nullptr, InitMSDKWithParams, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"startRTK", nullptr, StartRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"stopRTK", nullptr, StopRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getRTKStatus", nullptr, GetRTKStatus, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
```

### 7. JavaScript调用示例
```javascript
// 简单调用
const result1 = msdk.initMSDK(true);

// 带配置对象的调用
const result2 = msdk.initMSDKWithParams(
    true, // isDebugMode
    {
        serverUrl: "https://rtk.example.com",
        timeout: 5000,
        retryCount: 3
    },
    (success, message) => {
        console.log(`初始化结果: ${success}, 消息: ${message}`);
    }
);

// 只传必要参数
const result3 = msdk.initMSDKWithParams(false);
```

### 8. HarmonyOS 5.0.5 NAPI模块导出方式

#### 方式一：使用napi_module结构体（推荐）
```cpp
// 定义模块结构体
static napi_module msdk_module = {
    .nm_version = 1,                    // 模块版本
    .nm_flags = 0,                      // 模块标志
    .nm_filename = nullptr,              // 文件名（可选）
    .nm_register_func = Init,            // 注册函数
    .nm_modname = "msdk_native",        // 模块名称
    .nm_priv = nullptr,                 // 私有数据
    .reserved = {nullptr}               // 保留字段
};

// 使用构造函数自动注册模块
extern "C" __attribute__((constructor)) void RegisterModule(void) {
    napi_module_register(&msdk_module);
}
```

#### 方式二：使用NAPI_MODULE_INIT宏（如果支持）
```cpp
// 如果HarmonyOS支持NAPI_MODULE_INIT宏
NAPI_MODULE_INIT() {
    napi_value exports;
    napi_create_object(env, &exports);
    
    // 注册函数
    napi_property_descriptor desc[] = {
        {"initMSDK", nullptr, InitMSDK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"startRTK", nullptr, StartRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"stopRTK", nullptr, StopRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getRTKStatus", nullptr, GetRTKStatus, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
```

#### 方式三：使用动态注册
```cpp
// 动态注册方式
extern "C" napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"initMSDK", nullptr, InitMSDK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"startRTK", nullptr, StartRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"stopRTK", nullptr, StopRTK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getRTKStatus", nullptr, GetRTKStatus, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

// 手动注册函数
extern "C" void RegisterMSDKModule(void) {
    static napi_module module = {
        .nm_version = 1,
        .nm_flags = 0,
        .nm_filename = nullptr,
        .nm_register_func = Init,
        .nm_modname = "msdk_native",
        .nm_priv = nullptr,
        .reserved = {nullptr}
    };
    napi_module_register(&module);
}
```

### 9. CMakeLists.txt配置更新
```cmake
cmake_minimum_required(VERSION 3.4.1)
project(msdk_native)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件
add_library(msdk_native SHARED
    msdk_wrapper.cpp
    harmony_interface.cpp
)

# 包含头文件目录
target_include_directories(msdk_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接必要的库
target_link_libraries(msdk_native
    hilog_ndk.z
    ace_napi.z
    # 外部依赖动态库需要使用完整路径
    /path/to/external/libs/libautel_mobile_sdk.so
    /path/to/external/libs/libmsdk_core.so
    /path/to/external/libs/libnetwork_utils.so
)

# 或者使用相对路径（如果库文件在项目内）
target_link_libraries(msdk_native
    hilog_ndk.z
    ace_napi.z
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/libautel_mobile_sdk.so
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/libmsdk_core.so
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/libnetwork_utils.so
)

# HarmonyOS特定的编译选项
target_compile_options(msdk_native PRIVATE
    -fPIC
    -Wall
    -Wextra
)

# 设置输出名称
set_target_properties(msdk_native PROPERTIES
    OUTPUT_NAME "msdk_native"
    PREFIX ""
    SUFFIX ".so"
)
```

### 10. 模块使用示例
```javascript
// 在ArkTS中从动态库导入
import msdk from 'libmsdk_native.so';

// 或者使用完整的库路径
// import msdk from '/system/lib64/libmsdk_native.so';

// 初始化MSDK
const result = msdk.initMSDK(true);
console.log('MSDK初始化结果:', result);

// 启动RTK
const rtkResult = msdk.startRTK();
console.log('RTK启动结果:', rtkResult);

// 获取RTK状态
const status = msdk.getRTKStatus();
console.log('RTK状态:', status);
```

### 10.1. 动态库路径配置
```json5
// 在entry/src/main/module.json5中配置
{
  "module": {
    "name": "entry",
    "type": "entry",
    "description": "$string:module_desc",
    "mainElement": "EntryAbility",
    "deviceTypes": [
      "phone",
      "tablet"
    ],
    "deliveryWithInstall": true,
    "installationFree": false,
    "pages": "$profile:main_pages",
    "abilities": [
      {
        "name": "EntryAbility",
        "srcEntry": "./ets/entryability/EntryAbility.ets",
        "description": "$string:EntryAbility_desc",
        "icon": "$media:icon",
        "label": "$string:EntryAbility_label",
        "startWindowIcon": "$media:icon",
        "startWindowBackground": "$color:start_window_background",
        "exported": true,
        "skills": [
          {
            "entities": [
              "entity.system.home"
            ],
            "actions": [
              "action.system.home"
            ]
          }
        ]
      }
    ],
    "requestPermissions": [
      {
        "name": "ohos.permission.INTERNET",
        "reason": "$string:internet_permission",
        "usedScene": {
          "abilities": [
            "EntryAbility"
          ],
          "when": "always"
        }
      },
      {
        "name": "ohos.permission.ACCESS_NETWORK_STATE",
        "reason": "$string:network_permission",
        "usedScene": {
          "abilities": [
            "EntryAbility"
          ],
          "when": "always"
        }
      }
    ],
    "nativeLibrary": [
      "libmsdk_native.so"
    ]
  }
}
```

### 10.2. 动态库部署配置
```cmake
# 在CMakeLists.txt中配置库文件部署
cmake_minimum_required(VERSION 3.4.1)
project(msdk_native)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件
add_library(msdk_native SHARED
    msdk_wrapper.cpp
    harmony_interface.cpp
)

# 包含头文件目录
target_include_directories(msdk_native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接必要的库
target_link_libraries(msdk_native
    hilog_ndk.z
    ace_napi.z
    # 如果使用MSDK，需要链接相应的库
    # autel_mobile_sdk
)

# HarmonyOS特定的编译选项
target_compile_options(msdk_native PRIVATE
    -fPIC
    -Wall
    -Wextra
)

# 设置输出名称和部署路径
set_target_properties(msdk_native PROPERTIES
    OUTPUT_NAME "msdk_native"
    PREFIX "lib"
    SUFFIX ".so"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/main/resources/rawfile"
)

# 安装规则
install(TARGETS msdk_native
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
```

### 10.3. 运行时动态库加载
```cpp
// 在C++代码中确保库正确加载
extern "C" __attribute__((constructor)) void RegisterModule(void) {
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "开始注册MSDK模块");
    
    // 检查库文件是否存在
    FILE* file = fopen("/system/lib64/libmsdk_native.so", "r");
    if (file) {
        fclose(file);
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "MSDK库文件存在");
    } else {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "MSDK库文件不存在");
    }
    
    napi_status status = napi_module_register(&msdk_module);
    if (status == napi_ok) {
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "MSDK模块注册成功");
    } else {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "MSDK模块注册失败: %d", status);
    }
}
```

### 10.4. 库文件路径说明
```bash
# HarmonyOS中常见的库文件路径
/system/lib64/libmsdk_native.so          # 系统库路径
/data/app/.../lib/arm64/libmsdk_native.so # 应用私有库路径
/vendor/lib64/libmsdk_native.so          # 厂商库路径
```

### 10.5. 外部依赖动态库配置

#### 方式一：使用绝对路径（推荐）
```cmake
# 定义外部库路径变量
set(EXTERNAL_LIB_PATH "/opt/harmony/external/libs")
set(MSDK_LIB_PATH "/opt/harmony/msdk/libs")

# 链接外部依赖库
target_link_libraries(msdk_native
    hilog_ndk.z
    ace_napi.z
    # 使用完整路径链接外部库
    ${EXTERNAL_LIB_PATH}/libautel_mobile_sdk.so
    ${MSDK_LIB_PATH}/libmsdk_core.so
    ${MSDK_LIB_PATH}/libnetwork_utils.so
)

# 注意：HarmonyOS构建系统会自动将链接的外部库复制到HAP包中
# 不需要手动添加复制命令
```

#### 方式二：使用环境变量
```cmake
# 使用环境变量定义库路径
if(DEFINED ENV{MSDK_LIB_PATH})
    set(MSDK_LIB_PATH $ENV{MSDK_LIB_PATH})
else()
    set(MSDK_LIB_PATH "/opt/harmony/msdk/libs")
endif()

target_link_libraries(msdk_native
    hilog_ndk.z
    ace_napi.z
    ${MSDK_LIB_PATH}/libautel_mobile_sdk.so
    ${MSDK_LIB_PATH}/libmsdk_core.so
    ${MSDK_LIB_PATH}/libnetwork_utils.so
)
# HarmonyOS构建系统会自动处理库文件的复制
```

#### 方式三：使用find_library查找
```cmake
# 查找外部库文件
find_library(AUTEL_MOBILE_SDK_LIB
    NAMES libautel_mobile_sdk.so autel_mobile_sdk
    PATHS /opt/harmony/external/libs /usr/local/lib /opt/lib
    NO_DEFAULT_PATH
)

find_library(MSDK_CORE_LIB
    NAMES libmsdk_core.so msdk_core
    PATHS /opt/harmony/msdk/libs /usr/local/lib /opt/lib
    NO_DEFAULT_PATH
)

if(AUTEL_MOBILE_SDK_LIB AND MSDK_CORE_LIB)
    target_link_libraries(msdk_native
        hilog_ndk.z
        ace_napi.z
        ${AUTEL_MOBILE_SDK_LIB}
        ${MSDK_CORE_LIB}
    )
    # 构建系统会自动复制找到的库文件
else()
    message(FATAL_ERROR "找不到必需的MSDK库文件")
endif()
```

### 10.6. 模块配置文件更新
```json5
{
  "module": {
    "name": "entry",
    "type": "entry",
    "description": "$string:module_desc",
    "mainElement": "EntryAbility",
    "deviceTypes": [
      "phone",
      "tablet"
    ],
    "deliveryWithInstall": true,
    "installationFree": false,
    "pages": "$profile:main_pages",
    "abilities": [
      {
        "name": "EntryAbility",
        "srcEntry": "./ets/entryability/EntryAbility.ets",
        "description": "$string:EntryAbility_desc",
        "icon": "$media:icon",
        "label": "$string:EntryAbility_label",
        "startWindowIcon": "$media:icon",
        "startWindowBackground": "$color:start_window_background",
        "exported": true,
        "skills": [
          {
            "entities": [
              "entity.system.home"
            ],
            "actions": [
              "action.system.home"
            ]
          }
        ]
      }
    ],
    "requestPermissions": [
      {
        "name": "ohos.permission.INTERNET",
        "reason": "$string:internet_permission",
        "usedScene": {
          "abilities": [
            "EntryAbility"
          ],
          "when": "always"
        }
      },
      {
        "name": "ohos.permission.ACCESS_NETWORK_STATE",
        "reason": "$string:network_permission",
        "usedScene": {
          "abilities": [
            "EntryAbility"
          ],
          "when": "always"
        }
      }
    ],
    "nativeLibrary": [
      "libmsdk_native.so",
      "libs/libautel_mobile_sdk.so",
      "libs/libmsdk_core.so",
      "libs/libnetwork_utils.so"
    ]
  }
}
```

### 10.7. 运行时动态库加载检查
```cpp
// 在模块注册时检查所有依赖库
extern "C" __attribute__((constructor)) void RegisterModule(void) {
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "开始注册MSDK模块");
    
    // 检查主库文件
    const char* libs[] = {
        "/system/lib64/libmsdk_native.so",
        "/data/app/.../lib/arm64/libautel_mobile_sdk.so",
        "/data/app/.../lib/arm64/libmsdk_core.so",
        "/data/app/.../lib/arm64/libnetwork_utils.so"
    };
    
    for (int i = 0; i < sizeof(libs) / sizeof(libs[0]); i++) {
        FILE* file = fopen(libs[i], "r");
        if (file) {
            HILOG_INFO(LOG_DOMAIN, LOG_TAG, "库文件存在: %s", libs[i]);
            fclose(file);
        } else {
            HILOG_WARN(LOG_DOMAIN, LOG_TAG, "库文件不存在: %s", libs[i]);
        }
    }
    
    napi_status status = napi_module_register(&msdk_module);
    if (status == napi_ok) {
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "MSDK模块注册成功");
    } else {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "MSDK模块注册失败: %d", status);
    }
}
```

### 10.8. 构建脚本示例
```bash
#!/bin/bash
# build_msdk.sh - MSDK构建脚本

# 设置环境变量
export MSDK_LIB_PATH="/opt/harmony/msdk/libs"
export EXTERNAL_LIB_PATH="/opt/harmony/external/libs"

# 检查依赖库是否存在
check_libs() {
    local libs=(
        "$MSDK_LIB_PATH/libautel_mobile_sdk.so"
        "$MSDK_LIB_PATH/libmsdk_core.so"
        "$MSDK_LIB_PATH/libnetwork_utils.so"
    )
    
    for lib in "${libs[@]}"; do
        if [ ! -f "$lib" ]; then
            echo "错误: 找不到库文件 $lib"
            exit 1
        fi
    done
    echo "所有依赖库文件检查通过"
}

# 构建项目
build_project() {
    check_libs
    
    # 创建构建目录
    mkdir -p build
    cd build
    
    # 配置CMake
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DMSDK_LIB_PATH="$MSDK_LIB_PATH" \
        -DEXTERNAL_LIB_PATH="$EXTERNAL_LIB_PATH"
    
    # 编译
    make -j$(nproc)
    
    echo "构建完成"
    echo "注意：HarmonyOS构建系统会自动将链接的外部库复制到HAP包中"
}

build_project
```

### 10.9. HarmonyOS构建系统自动处理说明

#### 自动复制机制
```cmake
# 当使用target_link_libraries链接外部库时
target_link_libraries(msdk_native
    ${MSDK_LIB_PATH}/libautel_mobile_sdk.so
    ${MSDK_LIB_PATH}/libmsdk_core.so
)

# HarmonyOS构建系统会：
# 1. 自动检测链接的外部库
# 2. 将库文件复制到HAP包的适当位置
# 3. 更新模块配置文件中的nativeLibrary列表
# 4. 确保运行时能正确加载所有依赖库
```

#### 构建流程
```bash
# HarmonyOS构建流程
1. CMake配置阶段：解析target_link_libraries中的库路径
2. 编译阶段：编译原生代码并链接外部库
3. 打包阶段：自动复制外部库到HAP包
4. 部署阶段：确保所有库文件在设备上可用
```

#### 验证方法
```bash
# 检查HAP包中是否包含外部库
unzip -l myapp.hap | grep "\.so"

# 应该看到类似输出：
# libmsdk_native.so
# libs/libautel_mobile_sdk.so
# libs/libmsdk_core.so
```

### 11. 常见问题解决

#### 问题1：模块加载失败
```cpp
// 确保模块名称正确
.nm_modname = "msdk_native",  // 必须与JavaScript中的import名称一致
```

#### 问题2：函数未找到
```cpp
// 检查函数注册是否正确
napi_property_descriptor desc[] = {
    {"initMSDK", nullptr, InitMSDK, nullptr, nullptr, nullptr, napi_default, nullptr},
    // 确保函数名与JavaScript调用一致
};
```

#### 问题3：编译错误
```cmake
# 确保链接了正确的库
target_link_libraries(msdk_native
    hilog_ndk.z
    ace_napi.z
)
```

### 12. Want对象详解

#### 12.1. Want对象概念
Want对象是HarmonyOS中用于描述应用间通信意图的核心组件，类似于Android的Intent。

**Want对象的作用：**
- **应用间通信**：启动其他应用的Ability
- **服务调用**：启动或绑定服务
- **数据传递**：在应用间传递数据
- **系统功能调用**：调用系统提供的功能

#### 12.2. Want对象结构
```cpp
// Want对象的基本结构
class Want {
public:
    // 设置组件名称
    void SetElementName(const std::string& bundleName, const std::string& abilityName);
    
    // 设置URI
    void SetUri(const std::string& uri);
    
    // 设置操作类型
    void SetAction(const std::string& action);
    
    // 设置数据类型
    void SetType(const std::string& type);
    
    // 添加参数
    void SetParam(const std::string& key, const std::string& value);
    
    // 获取参数
    std::string GetParam(const std::string& key) const;
};
```

#### 12.3. Want对象使用示例

##### 示例1：启动其他应用的Ability
```cpp
// 启动其他应用的Ability
Want want;
want.SetElementName("com.example.targetapp", "MainAbility");
want.SetAction("action.system.home");

// 添加参数
want.SetParam("userId", "12345");
want.SetParam("action", "login");

// 启动Ability
auto context = AbilityContext::GetInstance();
if (context) {
    context->StartAbility(want);
}
```

##### 示例2：启动服务
```cpp
// 启动RTK服务
Want want;
want.SetElementName("com.example.myapp", "RTKService");
want.SetAction("action.start.service");

// 添加服务参数
want.SetParam("serverUrl", "https://rtk.example.com");
want.SetParam("port", "8080");
want.SetParam("timeout", "5000");

// 启动服务
auto context = AbilityContext::GetInstance();
if (context) {
    context->StartAbility(want);
}
```

##### 示例3：绑定服务
```cpp
// 绑定服务
Want want;
want.SetElementName("com.example.myapp", "DataService");
want.SetAction("action.bind.service");

// 绑定服务并获取连接
auto context = AbilityContext::GetInstance();
if (context) {
    context->ConnectAbility(want, serviceConnection);
}
```

#### 12.4. Want对象参数类型

| 参数类型 | 设置方法 | 示例 |
|---------|---------|------|
| 字符串 | `SetParam(key, value)` | `want.SetParam("url", "https://example.com")` |
| 整数 | `SetParam(key, std::to_string(value))` | `want.SetParam("port", "8080")` |
| 布尔值 | `SetParam(key, value ? "true" : "false")` | `want.SetParam("debug", "true")` |
| 对象 | 序列化为JSON字符串 | `want.SetParam("config", jsonString)` |

#### 12.5. 在MSDK中的应用

##### RTK服务启动
```cpp
static bool StartRTKService() {
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "启动RTK服务");
    
    // 创建Want对象
    Want want;
    want.SetElementName("com.example.myapp", "RTKService");
    want.SetAction("action.start.rtk");
    
    // 设置RTK服务参数
    want.SetParam("serverUrl", "https://rtk.example.com");
    want.SetParam("port", "8080");
    want.SetParam("timeout", "5000");
    want.SetParam("retryCount", "3");
    want.SetParam("debugMode", "true");
    
    // 启动服务
    auto context = AbilityContext::GetInstance();
    if (context) {
        context->StartAbility(want);
        return true;
    }
    
    return false;
}
```

##### 数据服务绑定
```cpp
// 数据服务连接回调
class DataServiceConnection : public IAbilityConnection {
public:
    void OnAbilityConnectDone(const AppExecFwk::ElementName& element, 
                             const sptr<IRemoteObject>& remoteObject, int resultCode) override {
        if (resultCode == 0) {
            HILOG_INFO(LOG_DOMAIN, LOG_TAG, "数据服务连接成功");
            // 处理服务连接成功
        } else {
            HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "数据服务连接失败: %d", resultCode);
        }
    }
    
    void OnAbilityDisconnectDone(const AppExecFwk::ElementName& element, int resultCode) override {
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "数据服务断开连接");
    }
};

// 绑定数据服务
static bool BindDataService() {
    Want want;
    want.SetElementName("com.example.myapp", "DataService");
    want.SetAction("action.bind.data");
    
    auto context = AbilityContext::GetInstance();
    if (context) {
        sptr<DataServiceConnection> connection = new DataServiceConnection();
        context->ConnectAbility(want, connection);
        return true;
    }
    
    return false;
}
```

#### 12.6. Want对象最佳实践

##### 1. 参数验证
```cpp
// 验证Want对象参数
bool ValidateWantParams(const Want& want) {
    // 检查必需参数
    if (want.GetParam("serverUrl").empty()) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "缺少必需参数: serverUrl");
        return false;
    }
    
    // 验证参数格式
    std::string port = want.GetParam("port");
    if (!port.empty()) {
        try {
            int portNum = std::stoi(port);
            if (portNum < 1 || portNum > 65535) {
                HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "端口号无效: %s", port.c_str());
                return false;
            }
        } catch (...) {
            HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "端口号格式错误: %s", port.c_str());
            return false;
        }
    }
    
    return true;
}
```

##### 2. 错误处理
```cpp
// 启动服务并处理错误
bool StartServiceWithErrorHandling(const Want& want) {
    auto context = AbilityContext::GetInstance();
    if (!context) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "无法获取应用上下文");
        return false;
    }
    
    // 验证参数
    if (!ValidateWantParams(want)) {
        return false;
    }
    
    // 启动服务
    int result = context->StartAbility(want);
    if (result != 0) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "启动服务失败: %d", result);
        return false;
    }
    
    HILOG_INFO(LOG_DOMAIN, LOG_TAG, "服务启动成功");
    return true;
}
```

##### 3. 异步处理
```cpp
// 异步启动服务
void StartServiceAsync(const Want& want, std::function<void(bool)> callback) {
    auto context = AbilityContext::GetInstance();
    if (!context) {
        callback(false);
        return;
    }
    
    // 在后台线程执行
    std::thread([context, want, callback]() {
        int result = context->StartAbility(want);
        callback(result == 0);
    }).detach();
}
```
