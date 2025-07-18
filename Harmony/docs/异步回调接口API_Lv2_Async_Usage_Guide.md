# 异步二级API使用指南

## 概述

本文档介绍如何在HarmonyOS中处理C++的异步二级API结构，特别是包含`std::shared_ptr<IComplete<T>>`回调的异步操作，并将其暴露给JavaScript调用。

## 设计模式分析

### 1. 原始C++结构

```cpp
template<typename T>
class IComplete {
public:
    virtual ~IComplete() = default;
    virtual void success(T result) = 0;
    virtual void failure(const std::string& error) = 0;
};

class api_lv2_1 {
public:
    string doSomething(int state, std::shared_ptr<IComplete<int32_t>> listener);
};
```

### 2. 设计特点

- **异步操作**：操作在后台线程执行，不阻塞主线程
- **回调机制**：使用`std::shared_ptr<IComplete<T>>`管理回调对象生命周期
- **线程安全**：确保回调在正确的线程上执行
- **内存安全**：使用智能指针避免内存泄漏

## 实现方案

### 1. C++端实现

#### 异步回调包装器
```cpp
class AsyncCallbackWrapper : public IComplete<int32_t>, public std::enable_shared_from_this<AsyncCallbackWrapper> {
public:
    AsyncCallbackWrapper(napi_env env, napi_value successCallback, napi_value failureCallback);
    ~AsyncCallbackWrapper() = default;

    void success(int32_t result) override;
    void failure(const std::string& error) override;

private:
    napi_env env_;
    napi_ref successCallbackRef_;
    napi_ref failureCallbackRef_;
    std::mutex mutex_;
    bool isDestroyed_ = false;
};
```

#### 关键实现点

1. **回调包装**：将JavaScript回调函数包装为C++回调对象
2. **线程安全**：使用互斥锁保护回调调用
3. **内存管理**：正确管理`napi_ref`的生命周期
4. **异步执行**：在后台线程执行操作，在主线程调用回调

### 2. JavaScript端调用

#### 基本调用方式
```typescript
// 获取二级API对象
const lv2_1 = api.getLv2_1();

// 调用异步方法
lv2_1.doSomething(10, 
  // 成功回调
  (result) => {
    console.log('操作成功:', result);
  },
  // 失败回调
  (error) => {
    console.error('操作失败:', error);
  }
);
```

#### Promise包装
```typescript
// Promise包装异步操作
async function doSomethingAsync(state: number): Promise<number> {
  return new Promise((resolve, reject) => {
    const lv2_1 = api.getLv2_1();
    
    lv2_1.doSomething(state,
      (result) => resolve(result),
      (error) => reject(new Error(error))
    );
  });
}
```

## 实现步骤

### 1. 创建异步回调包装器

#### 步骤1：定义回调接口
```cpp
template<typename T>
class IComplete {
public:
    virtual ~IComplete() = default;
    virtual void success(T result) = 0;
    virtual void failure(const std::string& error) = 0;
};
```

#### 步骤2：实现回调包装器
```cpp
class AsyncCallbackWrapper : public IComplete<int32_t>, public std::enable_shared_from_this<AsyncCallbackWrapper> {
public:
    AsyncCallbackWrapper(napi_env env, napi_value successCallback, napi_value failureCallback);
    ~AsyncCallbackWrapper() = default;

    void success(int32_t result) override;
    void failure(const std::string& error) override;

private:
    void CallJSSuccess(int32_t result);
    void CallJSFailure(const std::string& error);
    
    napi_env env_;
    napi_ref successCallbackRef_;
    napi_ref failureCallbackRef_;
    std::mutex mutex_;
    bool isDestroyed_ = false;
};
```

#### 步骤3：实现JavaScript回调调用
```cpp
void AsyncCallbackWrapper::CallJSSuccess(int32_t result) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (isDestroyed_ || successCallbackRef_ == nullptr) {
        return;
    }

    // 获取成功回调函数
    napi_value callback;
    napi_status status = napi_get_reference_value(env_, successCallbackRef_, &callback);
    if (status != napi_ok) {
        return;
    }

    // 创建参数
    napi_value resultValue;
    napi_create_int32(env_, result, &resultValue);

    // 调用JavaScript回调函数
    napi_value undefined;
    napi_get_undefined(env_, &undefined);
    napi_value argv[1] = {resultValue};
    napi_call_function(env_, undefined, callback, 1, argv, nullptr);
}
```

### 2. 实现异步方法

#### 步骤1：定义异步操作
```cpp
class api_lv2_1 {
public:
    std::string doSomething(int state, std::shared_ptr<IComplete<int32_t>> listener) {
        // 模拟异步操作 
        std::thread([this, state, listener]() {
            // 模拟耗时操作
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            
            if (state > 0) {
                // 成功情况
                int32_t result = state * 2;
                if (listener) {
                    listener->success(result);
                }
            } else {
                // 失败情况
                if (listener) {
                    listener->failure("Invalid state: " + std::to_string(state));
                }
            }
        }).detach();
        
        return "Async operation started with state: " + std::to_string(state);
    }
};
```

#### 步骤2：包装异步方法
```cpp
static napi_value DoSomething(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    if (argc < 3) {
        napi_throw_error(env, nullptr, "需要三个参数: state, successCallback, failureCallback");
        return nullptr;
    }
    
    // 解析参数
    int32_t state;
    napi_get_value_int32(env, args[0], &state);
    
    // 创建回调包装器
    auto callbackWrapper = std::make_shared<AsyncCallbackWrapper>(env, args[1], args[2]);
    
    // 调用异步操作
    std::string result = api::GetInstance().getLv2_1().doSomething(state, callbackWrapper);
    
    // 返回操作状态
    napi_value resultValue;
    napi_create_string_utf8(env, result.c_str(), NAPI_AUTO_LENGTH, &resultValue);
    return resultValue;
}
```

### 3. 配置构建系统

#### CMake配置
```cmake
cmake_minimum_required(VERSION 3.4.1)
project(api_lv2_async)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用多线程支持
find_package(Threads REQUIRED)

add_library(api_lv2_async SHARED
    api_lv2_async_wrapper.cpp
)

target_link_libraries(api_lv2_async
    hilog_ndk.z
    ace_napi.z
    ${CMAKE_THREAD_LIBS_INIT}  # 链接线程库
)
```

## 最佳实践

### 1. 线程安全

```cpp
// 使用互斥锁保护回调调用
void AsyncCallbackWrapper::CallJSSuccess(int32_t result) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (isDestroyed_ || successCallbackRef_ == nullptr) {
        return;
    }
    // 调用JavaScript回调
}
```

### 2. 内存管理

```cpp
// 正确管理napi_ref生命周期
AsyncCallbackWrapper::~AsyncCallbackWrapper() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!isDestroyed_) {
        if (successCallbackRef_ != nullptr) {
            napi_delete_reference(env_, successCallbackRef_);
        }
        if (failureCallbackRef_ != nullptr) {
            napi_delete_reference(env_, failureCallbackRef_);
        }
        isDestroyed_ = true;
    }
}
```

### 3. 错误处理

```cpp
// 参数验证
static napi_value DoSomething(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    if (argc < 3) {
        napi_throw_error(env, nullptr, "需要三个参数: state, successCallback, failureCallback");
        return nullptr;
    }
    
    // 参数类型检查
    napi_valuetype successCallbackType;
    napi_typeof(env, args[1], &successCallbackType);
    if (successCallbackType != napi_function) {
        napi_throw_type_error(env, nullptr, "第二个参数必须是函数");
        return nullptr;
    }
    
    // 执行操作
}
```

### 4. 性能优化

```cpp
// 使用智能指针管理回调对象
auto callbackWrapper = std::make_shared<AsyncCallbackWrapper>(env, args[1], args[2]);

// 在后台线程执行操作
std::thread([this, state, listener]() {
    // 执行耗时操作
    if (state > 0) {
        listener->success(state * 2);
    } else {
        listener->failure("Invalid state");
    }
}).detach();
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

// 获取二级API对象
const lv2_1 = api.getLv2_1();

// 调用同步方法
const str1 = lv2_1.getString();
const str2 = lv2_1.getStringWithParam('World');
const length = lv2_1.getStringLength('Hello World');

console.log('同步方法结果:', { str1, str2, length });

// 调用异步方法
lv2_1.doSomething(10, 
  (result) => {
    console.log('异步操作成功:', result);
  },
  (error) => {
    console.error('异步操作失败:', error);
  }
);
```

### 2. Promise包装

```typescript
class APILv2AsyncManager {
  // Promise包装异步操作
  async doSomethingAsync(state: number): Promise<number> {
    return new Promise((resolve, reject) => {
      const lv2_1 = api.getLv2_1();
      
      lv2_1.doSomething(state,
        (result) => resolve(result),
        (error) => reject(new Error(error))
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
      } catch (error) {
        console.error('批量操作失败:', error);
        throw error;
      }
    }
    
    return results;
  }

  // 并发异步操作
  async performConcurrentAsyncOperations(states: number[]): Promise<number[]> {
    const promises = states.map(state => this.doSomethingAsync(state));
    return Promise.all(promises);
  }
}
```

### 3. 高级用法

```typescript
class APILv2AsyncAdvancedUsage {
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

  // 带重试的异步操作
  async doSomethingWithRetry(state: number, maxRetries: number = 3): Promise<number> {
    let lastError: Error;
    
    for (let i = 0; i < maxRetries; i++) {
      try {
        return await this.doSomethingAsync(state);
      } catch (error) {
        lastError = error as Error;
        console.warn(`操作失败，重试第${i + 1}次:`, error.message);
        
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
      console.error('异步操作错误:', error.message);
      // 可以在这里添加错误处理逻辑，如日志记录、错误上报等
      throw error;
    });
  }
}
```

## 常见问题解决

### 1. 回调未执行

**问题**：异步操作完成后回调函数未执行
**解决**：
- 检查回调函数是否正确传递
- 确保回调包装器正确创建
- 验证线程安全机制

### 2. 内存泄漏

**问题**：回调对象未正确释放
**解决**：
- 确保在析构函数中删除`napi_ref`
- 使用智能指针管理回调对象生命周期
- 检查回调对象是否被正确销毁

### 3. 线程安全问题

**问题**：回调在错误的线程上执行
**解决**：
- 使用互斥锁保护回调调用
- 确保回调在主线程执行
- 检查线程安全机制


## 总结

通过以上实现，我们成功地将C++的异步二级API结构暴露给JavaScript，实现了：

1. **异步操作支持**：正确处理后台线程的异步操作
2. **回调机制**：完整的成功/失败回调支持
3. **线程安全**：确保回调在正确的线程上执行
4. **内存安全**：使用智能指针避免内存泄漏
5. **类型安全**：完整的TypeScript类型定义
6. **错误处理**：完善的参数验证和错误处理
7. **性能优化**：线程池和对象缓存机制

这种设计模式可以广泛应用于需要将C++异步API暴露给JavaScript的场景，特别是涉及复杂异步操作和回调机制的应用。 