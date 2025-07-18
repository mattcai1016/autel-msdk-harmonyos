# 二级API使用指南

## 概述

本文档介绍如何在HarmonyOS中处理C++的二级API结构，并将其暴露给JavaScript调用。二级API是一种常见的C++设计模式，通过主API对象提供多个子API对象，每个子API负责特定的功能领域。

## 设计模式分析

### 1. 原始C++结构

```cpp
class api_lv2_1 {
public:
    string getString();
};

class api_lv2_2 {
public:
    int getInt32();
};

class api {
public:
    static api GetInstance();
    api_lv2_1 getLv2_1();
    api_lv2_2 getLv2_2();
};
```

### 2. 设计特点

- **单例模式**：主API使用单例模式
- **组合模式**：主API包含多个子API对象
- **职责分离**：每个子API负责特定功能
- **层次结构**：形成主API → 子API的层次关系

## 实现方案

### 1. C++端实现

#### 包装器设计
```cpp
// 包装器类，用于在JavaScript中表示二级API对象
class APIWrapper {
public:
    static napi_value CreateLv2_1Wrapper(napi_env env);
    static napi_value CreateLv2_2Wrapper(napi_env env);
    
private:
    // 各个子API的方法实现
    static napi_value GetString(napi_env env, napi_callback_info info);
    static napi_value GetInt32(napi_env env, napi_callback_info info);
    // ... 其他方法
};
```

#### 关键实现点

1. **对象包装**：为每个子API创建JavaScript对象包装器
2. **方法映射**：将C++方法映射到JavaScript方法
3. **参数处理**：正确处理JavaScript参数到C++参数的转换
4. **返回值处理**：将C++返回值转换为JavaScript值

### 2. JavaScript端调用

#### 基本调用方式
```typescript
// 获取主API
const mainAPI = api;

// 获取子API
const lv2_1 = api.getLv2_1();
const lv2_2 = api.getLv2_2();

// 调用子API方法
const str = lv2_1.getString();
const num = lv2_2.getInt32();
```

#### 链式调用
```typescript
// 链式调用示例
const result = api.getLv2_1().getStringWithParam('test');
const sum = api.getLv2_2().addInt32(10, 20);
```

## 实现步骤

### 1. 创建C++包装器

#### 步骤1：定义包装器类
```cpp
class APIWrapper {
public:
    static napi_value CreateLv2_1Wrapper(napi_env env);
    static napi_value CreateLv2_2Wrapper(napi_env env);
};
```

#### 步骤2：实现子API方法
```cpp
static napi_value GetString(napi_env env, napi_callback_info info) {
    std::string result = api::GetInstance().getLv2_1().getString();
    
    napi_value resultValue;
    napi_create_string_utf8(env, result.c_str(), NAPI_AUTO_LENGTH, &resultValue);
    return resultValue;
}
```

#### 步骤3：注册主API方法
```cpp
static napi_value GetLv2_1(napi_env env, napi_callback_info info) {
    return APIWrapper::CreateLv2_1Wrapper(env);
}

static napi_value GetLv2_2(napi_env env, napi_callback_info info) {
    return APIWrapper::CreateLv2_2Wrapper(env);
}
```

### 2. 配置构建系统

#### CMake配置
```cmake
cmake_minimum_required(VERSION 3.4.1)
project(api_lv2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(api_lv2 SHARED
    api_lv2_wrapper.cpp
)

target_link_libraries(api_lv2
    hilog_ndk.z
    ace_napi.z
)
```

#### 模块配置
```json5
{
  "module": {
    "name": "entry",
    "type": "entry",
    "nativeLibrary": [
      "libapi_lv2.so"
    ]
  }
}
```

### 3. 创建TypeScript定义

#### 接口定义
```typescript
export interface APILv2_1 {
  getString(): string;
  getStringWithParam(param: string): string;
  getStringLength(str: string): number;
}

export interface APILv2_2 {
  getInt32(): number;
  addInt32(a: number, b: number): number;
  getDouble(): number;
  getStatus(): string;
}

export interface MainAPI {
  getMainStatus(): string;
  initialize(): boolean;
  getLv2_1(): APILv2_1;
  getLv2_2(): APILv2_2;
}
```

## 最佳实践

### 1. 错误处理

```cpp
static napi_value GetStringWithParam(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    if (argc < 1) {
        napi_throw_error(env, nullptr, "需要一个参数");
        return nullptr;
    }
    
    // 参数类型检查
    napi_valuetype paramType;
    napi_typeof(env, args[0], &paramType);
    if (paramType != napi_string) {
        napi_throw_type_error(env, nullptr, "参数必须是字符串");
        return nullptr;
    }
    
    // 执行操作
    char param[256];
    size_t paramLen;
    napi_get_value_string_utf8(env, args[0], param, sizeof(param), &paramLen);
    
    std::string result = api::GetInstance().getLv2_1().getStringWithParam(param);
    
    napi_value resultValue;
    napi_create_string_utf8(env, result.c_str(), NAPI_AUTO_LENGTH, &resultValue);
    return resultValue;
}
```

### 2. 性能优化

```cpp
// 缓存包装器对象，避免重复创建
class APIWrapper {
private:
    static std::map<napi_env, napi_value> lv2_1_cache_;
    static std::map<napi_env, napi_value> lv2_2_cache_;
    static std::mutex cache_mutex_;

public:
    static napi_value CreateLv2_1Wrapper(napi_env env) {
        std::lock_guard<std::mutex> lock(cache_mutex_);
        
        auto it = lv2_1_cache_.find(env);
        if (it != lv2_1_cache_.end()) {
            return it->second;
        }
        
        napi_value wrapper = CreateLv2_1WrapperImpl(env);
        lv2_1_cache_[env] = wrapper;
        return wrapper;
    }
};
```

### 3. 内存管理

```cpp
// 在模块卸载时清理缓存
extern "C" __attribute__((destructor)) void CleanupAPILv2Module(void) {
    std::lock_guard<std::mutex> lock(APIWrapper::cache_mutex_);
    APIWrapper::lv2_1_cache_.clear();
    APIWrapper::lv2_2_cache_.clear();
}
```

## 使用示例

### 1. 基本使用

```typescript
// 初始化API
const initResult = api.initialize();
if (!initResult) {
    console.error('API初始化失败');
    return;
}

// 获取主API状态
const mainStatus = api.getMainStatus();
console.log('主API状态:', mainStatus);

// 使用api_lv2_1
const lv2_1 = api.getLv2_1();
const str1 = lv2_1.getString();
const str2 = lv2_1.getStringWithParam('World');
const length = lv2_1.getStringLength('Hello World');

console.log('api_lv2_1结果:', { str1, str2, length });

// 使用api_lv2_2
const lv2_2 = api.getLv2_2();
const int32 = lv2_2.getInt32();
const sum = lv2_2.addInt32(10, 20);
const doubleVal = lv2_2.getDouble();
const status = lv2_2.getStatus();

console.log('api_lv2_2结果:', { int32, sum, doubleVal, status });
```

### 2. 高级使用

```typescript
class APILv2Manager {
  private static instance: APILv2Manager;
  private isInitialized: boolean = false;

  static getInstance(): APILv2Manager {
    if (!APILv2Manager.instance) {
      APILv2Manager.instance = new APILv2Manager();
    }
    return APILv2Manager.instance;
  }

  async initialize(): Promise<void> {
    if (this.isInitialized) {
      return;
    }

    const result = api.initialize();
    if (!result) {
      throw new Error('API初始化失败');
    }

    this.isInitialized = true;
  }

  async testAllAPIs(): Promise<void> {
    await this.initialize();

    // 测试所有API
    const results = {
      mainStatus: api.getMainStatus(),
      lv2_1: {
        getString: api.getLv2_1().getString(),
        getStringWithParam: api.getLv2_1().getStringWithParam('Test'),
        getStringLength: api.getLv2_1().getStringLength('Test String')
      },
      lv2_2: {
        getInt32: api.getLv2_2().getInt32(),
        addInt32: api.getLv2_2().addInt32(5, 15),
        getDouble: api.getLv2_2().getDouble(),
        getStatus: api.getLv2_2().getStatus()
      }
    };

    console.log('所有API测试结果:', results);
  }
}
```

## 常见问题解决

### 1. 对象创建失败

**问题**：JavaScript无法获取子API对象
**解决**：
- 检查包装器创建函数是否正确实现
- 确保所有方法都已正确注册
- 验证参数传递是否正确

### 2. 方法调用失败

**问题**：子API方法调用时出现错误
**解决**：
- 检查参数类型和数量
- 确保C++方法实现正确
- 验证返回值转换是否正确

### 3. 性能问题

**问题**：频繁调用子API导致性能下降
**解决**：
- 实现对象缓存机制
- 减少不必要的对象创建
- 使用异步调用处理耗时操作

## 总结

通过以上实现，我们成功地将C++的二级API结构暴露给JavaScript，实现了：

1. **层次结构映射**：正确映射C++的层次结构到JavaScript
2. **类型安全**：完整的TypeScript类型定义
3. **错误处理**：完善的参数验证和错误处理
4. **性能优化**：对象缓存和异步处理
5. **扩展性**：支持复杂数据类型和异步操作

这种设计模式可以广泛应用于需要将复杂C++ API层次结构暴露给JavaScript的场景。 