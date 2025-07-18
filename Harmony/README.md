# Harmony SDK 集成示例

本示例演示了如何使用 Native API (NAPI) 桥接将 Autel Mobile SDK 集成到 HarmonyOS 应用程序中。

## 概述

Harmony SDK 集成示例提供了完整的实现：

- 使用 NAPI 的原生 C++ SDK 集成
- TypeScript/ArkTS UI 界面
- 错误处理和日志记录
- 资源管理和本地化

## 项目结构

```
examples/MsdkHarmony/
├── entry/src/main/
│   ├── cpp/                    # 原生 C++ 实现
│   │   ├── AutelSdkMethods.cpp # NAPI 桥接函数
│   │   ├── CMakeLists.txt      # C++ 构建配置
│   │   ├── types/              # 类型定义
│   │   └── AutelMobileSdk/     # SDK 依赖
│   │       ├── include/        # SDK 头文件
│   │       │   ├── key_manager/
│   │       │   ├── data_type/
│   │       │   ├── autelsdk-support/
│   │       │   └── *.h         # SDK 头文件
│   │       └── libs/           # SDK 库文件
│   │           ├── arm64-v8a/  # ARM64 库文件
│   │           └── x86_64/     # x86_64 库文件
│   ├── ets/                    # TypeScript/ArkTS UI
│   │   ├── pages/
│   │   │   └── Index.ets       # 主 UI 组件
│   │   ├── common/utils/
│   │   │   └── Logger.ets      # 日志工具
│   │   ├── entryability/       # 入口能力
│   │   └── entrybackupability/ # 备份能力
│   ├── resources/              # 本地化资源
│   │   ├── base/element/
│   │   │   ├── string.json     # UI 文本资源
│   │   │   └── color.json      # 颜色定义
│   │   ├── zh_CN/             # 中文本地化
│   │   └── en_US/             # 英文本地化
│   └── module.json5           # 模块配置
├── AppScope/                   # 应用范围
│   ├── app.json5              # 应用配置
│   └── resources/             # 应用级资源
├── docs/                      # 文档
│   ├── harmony应用msdk.md     # 主要文档
│   ├── 异步回调接口API_Lv2_Async_Usage_Guide.md
│   ├── 多级模块接口API_Lv2_Usage_Guide.md
│   └── *.cpp, *.d.ts, *.ets  # API 示例
├── screenshots/               # 项目截图
├── hvigor/                   # 构建配置
├── oh_modules/               # 依赖项
├── .hvigor/                  # 构建缓存
├── .idea/                    # IDE 配置
├── verify_sdk.sh            # SDK 验证脚本
├── log.txt                  # 构建日志
├── oh-package.json5         # 包配置
├── build-profile.json5      # 构建配置文件
├── hvigorfile.ts           # 构建脚本
├── CONFIGURATION_GUIDE.md  # 配置指南
├── DEVELOPMENT_GUIDE.md    # 开发指南
├── LICENSE                 # 许可证文件
├── .clangd                 # Clangd 配置
├── .clang-format          # 代码格式化规则
└── .clang-tidy            # 代码分析规则
```

## 功能特性

### 核心 SDK 功能

- **SDK 初始化**: 支持调试模式的 Autel Mobile SDK 初始化
- **版本管理**: 获取 SDK 版本和完整版本信息
- **设备信息**: 获取云台类型和其他设备信息
- **资源管理**: 正确的 SDK 清理和资源管理

### UI 功能

- **交互式界面**: 所有 SDK 操作的用户友好按钮
- **状态显示**: 实时状态更新和错误消息
- **加载指示器**: 操作期间的视觉反馈
- **本地化**: 通过资源文件的多语言支持
- **错误处理**: 全面的错误显示和日志记录

### 技术功能

- **NAPI 桥接**: 健壮的 C++ 到 TypeScript 通信
- **异常处理**: C++ 和 TypeScript 中的全面错误处理
- **日志记录**: 用于调试和监控的详细日志
- **内存管理**: 正确的资源清理和内存管理
- **类型安全**: 所有 API 调用和响应的强类型

## 前置条件

1. **HarmonyOS 开发环境**
   
   - DevEco Studio 4.0 或更高版本
   - HarmonyOS SDK API 17 或更高版本
   - Node.js 16.0 或更高版本

2. **Autel Mobile SDK**
   
   - Autel Mobile SDK 库和头文件
   - 正确的 SDK 许可和注册

3. **构建工具**
   
   - CMake 3.5.0 或更高版本
   - 支持 C++11 或更高版本的 C++ 编译器

## 安装

1. **设置 SDK 依赖**
   
   - 确保 Autel Mobile SDK 正确安装在 `entry/src/main/cpp/AutelMobileSdk/` 中
   - 验证 `libs/` 目录中存在所有必需的库
   - 检查 `include/` 目录中是否有头文件

2. **构建配置**
   
   - 项目使用 CMake 进行 C++ 编译
   - NAPI 模块在构建期间自动注册
   - TypeScript/ArkTS 代码由 HarmonyOS 构建系统编译

## 使用方法

### 基本 SDK 操作

1. **初始化 SDK**
   
   ```typescript
   const result = await HarmonySdk.initSdk(true); // 启用调试模式
   if (result.success) {
     console.log('SDK 初始化成功');
   }
   ```

2. **获取 SDK 版本**
   
   ```typescript
   const result = await HarmonySdk.getSdkVersion();
   if (result.success) {
     console.log('SDK 版本:', result.version);
   }
   ```

3. **销毁 SDK**
   
   ```typescript
   const result = await HarmonySdk.destroySdk();
   if (result.success) {
     console.log('SDK 销毁成功');
   }
   ```

### 错误处理

所有 SDK 函数都返回一致的结果对象：

```typescript
interface SdkResult {
  success: boolean;
  message: string;
  [key: string]: any; // 每个函数的特定附加数据
}
```

错误处理示例：

```typescript
try {
  const result = await HarmonySdk.initSdk(true);
  if (result.success) {
    // 处理成功
    console.log(result.message);
  } else {
    // 处理错误
    console.error('SDK 错误:', result.message);
  }
} catch (error) {
  // 处理异常
  console.error('异常:', error);
}
```

### 日志记录

应用程序包含全面的日志记录：

```typescript
import Logger from '../common/utils/Logger';

// 日志级别
Logger.info('信息消息');
Logger.debug('调试消息');
Logger.warn('警告消息');
Logger.error('错误消息');
Logger.fatal('致命错误消息');
```

## API 参考

### HarmonySdk 模块

#### `initSdk(debugMode: boolean): Promise<SdkResult>`

初始化 Harmony SDK。

- **参数:**
  - `debugMode`: 启用调试模式以进行详细日志记录
- **返回:** 包含初始化结果的 Promise

#### `getSdkVersion(): Promise<SdkResult>`

获取 SDK 版本。

- **返回:** 包含版本信息的 Promise，版本在 `result.version` 中

#### `getSdkFullVersion(): Promise<SdkResult>`

获取完整的 SDK 版本信息。

- **返回:** 包含云台类型的 Promise，类型在 `result.gimbalType` 中

#### `destroySdk(): Promise<SdkResult>`

销毁 SDK 并清理资源。

- **返回:** 包含销毁结果的 Promise

## 构建和运行

1. **在 DevEco Studio 中打开**
   
   ```bash
   # 在 DevEco Studio 中打开项目
   # 或使用命令行构建
   ```

2. **构建项目**
   
   ```bash
   # 构建 C++ 组件
   cd entry/src/main/cpp
   mkdir build && cd build
   cmake ..
   make
   
   # 构建 HarmonyOS 应用程序
   # 使用 DevEco Studio 或 hvigor 构建系统
   ```

3. **在设备上运行**
   
   - 连接 HarmonyOS 设备或模拟器
   - 部署应用程序
   - 通过 UI 测试 SDK 功能

## 故障排除

### 常见问题

1. **找不到 SDK**
   
   - 验证 Autel Mobile SDK 是否正确安装
   - 检查 CMakeLists.txt 中的库路径
   - 确保所有必需的依赖项都存在

2. **初始化失败**
   
   - 检查 SDK 许可和注册
   - 验证设备兼容性
   - 查看调试日志以获取详细的错误信息

3. **构建错误**
   
   - 确保 CMake 版本兼容性
   - 检查 C++ 编译器支持
   - 验证 HarmonyOS SDK 安装

4. **运行时错误**
   
   - 检查设备权限
   - 验证 SDK 初始化顺序
   - 查看应用程序日志

### 调试模式

启用调试模式以进行详细日志记录：

```typescript
const result = await HarmonySdk.initSdk(true);
```

调试日志将在设备日志中可用，可以使用以下命令查看：

```bash
hdc shell hilog
```

## 贡献

1. 遵循现有的代码风格和模式
2. 为新功能添加全面的错误处理
3. 为新功能包含适当的日志记录
4. 为任何 API 更改更新文档
5. 在目标设备上彻底测试

## 许可证

本项目根据 Apache License 2.0 获得许可。详情请参阅 LICENSE 文件。

## 支持

对于问题和疑问：

1. 查看故障排除部分
2. 查看日志以获取错误详情
3. 查阅 Autel Mobile SDK 文档
4. 联系开发团队

## 版本历史

- **v1.0.0**: 具有基本 SDK 集成的初始实现
- **v1.1.0**: 添加了全面的错误处理和日志记录
- **v1.2.0**: 增强了具有本地化支持的 UI
- **v1.3.0**: 添加了额外的 SDK 功能和验证 
