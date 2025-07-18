#include <hilog/log.h>
#include <napi/native_api.h>
#include <memory>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

#define LOG_DOMAIN 0x0001
#define LOG_TAG "API_LV2_ASYNC"

// 异步完成回调接口
template<typename T>
class IComplete {
public:
    virtual ~IComplete() = default;
    virtual void success(T result) = 0;
    virtual void failure(const std::string& error) = 0;
};

// 异步回调包装器，用于在JavaScript中表示回调对象
class AsyncCallbackWrapper : public IComplete<int32_t>, public std::enable_shared_from_this<AsyncCallbackWrapper> {
public:
    AsyncCallbackWrapper(napi_env env, napi_value successCallback, napi_value failureCallback);
    ~AsyncCallbackWrapper() = default;

    void success(int32_t result) override;
    void failure(const std::string& error) override;

    // 线程安全调用JavaScript回调
    void CallJSSuccess(int32_t result);
    void CallJSFailure(const std::string& error);

private:
    napi_env env_;
    napi_ref successCallbackRef_;
    napi_ref failureCallbackRef_;
    std::mutex mutex_;
    bool isDestroyed_ = false;
};

// 二级API类，包含异步操作
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
    
    // 同步版本的方法
    std::string getString() {
        return "Hello from api_lv2_1";
    }
    
    std::string getStringWithParam(const std::string& param) {
        return "Hello " + param + " from api_lv2_1";
    }
    
    int getStringLength(const std::string& str) {
        return static_cast<int>(str.length());
    }
};

// 主API类
class api {
public:
    static api& GetInstance() {
        static api instance;
        return instance;
    }
    
    api_lv2_1& getLv2_1() {
        return lv2_1_;
    }
    
    // 主API的其他方法
    std::string getMainStatus() {
        return "Main API is initialized";
    }
    
    bool initialize() {
        HILOG_INFO(LOG_DOMAIN, LOG_TAG, "API初始化");
        return true;
    }

private:
    api() = default;
    ~api() = default;
    api(const api&) = delete;
    api& operator=(const api&) = delete;
    
    api_lv2_1 lv2_1_;
};

// AsyncCallbackWrapper实现
AsyncCallbackWrapper::AsyncCallbackWrapper(napi_env env, napi_value successCallback, napi_value failureCallback) 
    : env_(env), isDestroyed_(false) {
    napi_create_reference(env, successCallback, 1, &successCallbackRef_);
    napi_create_reference(env, failureCallback, 1, &failureCallbackRef_);
}

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

void AsyncCallbackWrapper::success(int32_t result) {
    CallJSSuccess(result);
}

void AsyncCallbackWrapper::failure(const std::string& error) {
    CallJSFailure(error);
}

void AsyncCallbackWrapper::CallJSSuccess(int32_t result) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (isDestroyed_ || successCallbackRef_ == nullptr) {
        return;
    }

    // 获取成功回调函数
    napi_value callback;
    napi_status status = napi_get_reference_value(env_, successCallbackRef_, &callback);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "获取成功回调函数失败");
        return;
    }

    // 创建参数
    napi_value resultValue;
    napi_create_int32(env_, result, &resultValue);

    // 调用JavaScript回调函数
    napi_value undefined;
    napi_get_undefined(env_, &undefined);
    napi_value argv[1] = {resultValue};
    napi_value jsResult;
    status = napi_call_function(env_, undefined, callback, 1, argv, &jsResult);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "调用成功回调函数失败");
    }
}

void AsyncCallbackWrapper::CallJSFailure(const std::string& error) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (isDestroyed_ || failureCallbackRef_ == nullptr) {
        return;
    }

    // 获取失败回调函数
    napi_value callback;
    napi_status status = napi_get_reference_value(env_, failureCallbackRef_, &callback);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "获取失败回调函数失败");
        return;
    }

    // 创建参数
    napi_value errorValue;
    napi_create_string_utf8(env_, error.c_str(), NAPI_AUTO_LENGTH, &errorValue);

    // 调用JavaScript回调函数
    napi_value undefined;
    napi_get_undefined(env_, &undefined);
    napi_value argv[1] = {errorValue};
    napi_value jsResult;
    status = napi_call_function(env_, undefined, callback, 1, argv, &jsResult);
    if (status != napi_ok) {
        HILOG_ERROR(LOG_DOMAIN, LOG_TAG, "调用失败回调函数失败");
    }
}

// 包装器类，用于在JavaScript中表示二级API对象
class APIAsyncWrapper {
public:
    static napi_value CreateLv2_1Wrapper(napi_env env) {
        napi_value wrapper;
        napi_create_object(env, &wrapper);
        
        // 添加同步方法
        napi_property_descriptor syncMethods[] = {
            {"getString", nullptr, GetString, nullptr, nullptr, nullptr, napi_default, nullptr},
            {"getStringWithParam", nullptr, GetStringWithParam, nullptr, nullptr, nullptr, napi_default, nullptr},
            {"getStringLength", nullptr, GetStringLength, nullptr, nullptr, nullptr, napi_default, nullptr}
        };
        napi_define_properties(env, wrapper, sizeof(syncMethods) / sizeof(syncMethods[0]), syncMethods);
        
        // 添加异步方法
        napi_property_descriptor asyncMethods[] = {
            {"doSomething", nullptr, DoSomething, nullptr, nullptr, nullptr, napi_default, nullptr}
        };
        napi_define_properties(env, wrapper, sizeof(asyncMethods) / sizeof(asyncMethods[0]), asyncMethods);
        
        return wrapper;
    }

private:
    // 同步方法实现
    static napi_value GetString(napi_env env, napi_callback_info info) {
        std::string result = api::GetInstance().getLv2_1().getString();
        
        napi_value resultValue;
        napi_create_string_utf8(env, result.c_str(), NAPI_AUTO_LENGTH, &resultValue);
        return resultValue;
    }
    
    static napi_value GetStringWithParam(napi_env env, napi_callback_info info) {
        size_t argc = 1;
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
        
        if (argc < 1) {
            napi_throw_error(env, nullptr, "需要一个参数");
            return nullptr;
        }
        
        char param[256];
        size_t paramLen;
        napi_get_value_string_utf8(env, args[0], param, sizeof(param), &paramLen);
        
        std::string result = api::GetInstance().getLv2_1().getStringWithParam(param);
        
        napi_value resultValue;
        napi_create_string_utf8(env, result.c_str(), NAPI_AUTO_LENGTH, &resultValue);
        return resultValue;
    }
    
    static napi_value GetStringLength(napi_env env, napi_callback_info info) {
        size_t argc = 1;
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
        
        if (argc < 1) {
            napi_throw_error(env, nullptr, "需要一个参数");
            return nullptr;
        }
        
        char str[256];
        size_t strLen;
        napi_get_value_string_utf8(env, args[0], str, sizeof(str), &strLen);
        
        int length = api::GetInstance().getLv2_1().getStringLength(str);
        
        napi_value resultValue;
        napi_create_int32(env, length, &resultValue);
        return resultValue;
    }
    
    // 异步方法实现
    static napi_value DoSomething(napi_env env, napi_callback_info info) {
        size_t argc = 3;
        napi_value args[3];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
        
        if (argc < 3) {
            napi_throw_error(env, nullptr, "需要三个参数: state, successCallback, failureCallback");
            return nullptr;
        }
        
        // 解析第一个参数：state
        int32_t state;
        napi_status status = napi_get_value_int32(env, args[0], &state);
        if (status != napi_ok) {
            napi_throw_type_error(env, nullptr, "第一个参数必须是数字");
            return nullptr;
        }
        
        // 解析第二个参数：successCallback
        napi_valuetype successCallbackType;
        napi_typeof(env, args[1], &successCallbackType);
        if (successCallbackType != napi_function) {
            napi_throw_type_error(env, nullptr, "第二个参数必须是函数");
            return nullptr;
        }
        
        // 解析第三个参数：failureCallback
        napi_valuetype failureCallbackType;
        napi_typeof(env, args[2], &failureCallbackType);
        if (failureCallbackType != napi_function) {
            napi_throw_type_error(env, nullptr, "第三个参数必须是函数");
            return nullptr;
        }
        
        // 创建回调包装器
        auto callbackWrapper = std::make_shared<AsyncCallbackWrapper>(env, args[1], args[2]);
        
        // 调用异步操作
        std::string result = api::GetInstance().getLv2_1().doSomething(state, callbackWrapper);
        
        // 返回操作状态
        napi_value resultValue;
        napi_create_string_utf8(env, result.c_str(), NAPI_AUTO_LENGTH, &resultValue);
        return resultValue;
    }
};

// 主API的NAPI包装函数
static napi_value GetMainStatus(napi_env env, napi_callback_info info) {
    std::string result = api::GetInstance().getMainStatus();
    
    napi_value resultValue;
    napi_create_string_utf8(env, result.c_str(), NAPI_AUTO_LENGTH, &resultValue);
    return resultValue;
}

static napi_value Initialize(napi_env env, napi_callback_info info) {
    bool result = api::GetInstance().initialize();
    
    napi_value resultValue;
    napi_get_boolean(env, result, &resultValue);
    return resultValue;
}

static napi_value GetLv2_1(napi_env env, napi_callback_info info) {
    return APIAsyncWrapper::CreateLv2_1Wrapper(env);
}

// 模块初始化
static napi_value Init(napi_env env, napi_value exports) {
    // 初始化主API
    api::GetInstance().initialize();
    
    napi_property_descriptor desc[] = {
        {"getMainStatus", nullptr, GetMainStatus, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"initialize", nullptr, Initialize, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getLv2_1", nullptr, GetLv2_1, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

// 模块注册
static napi_module api_lv2_async_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "api_lv2_async",
    .nm_priv = nullptr,
    .reserved = {nullptr}
};

extern "C" __attribute__((constructor)) void RegisterAPILv2AsyncModule(void) {
    napi_module_register(&api_lv2_async_module);
} 