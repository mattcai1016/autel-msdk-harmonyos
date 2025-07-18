#include <hilog/log.h>
#include <napi/native_api.h>
#include <memory>
#include <string>

#define LOG_DOMAIN 0x0001
#define LOG_TAG "API_LV2_WRAPPER"

// 二级API类1
class api_lv2_1 {
public:
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

// 二级API类2
class api_lv2_2 {
public:
    int getInt32() {
        return 42;
    }
    
    int addInt32(int a, int b) {
        return a + b;
    }
    
    double getDouble() {
        return 3.14159;
    }
    
    std::string getStatus() {
        return "api_lv2_2 is ready";
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
    
    api_lv2_2& getLv2_2() {
        return lv2_2_;
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
    api_lv2_2 lv2_2_;
};

// 包装器类，用于在JavaScript中表示二级API对象
class APIWrapper {
public:
    static napi_value CreateLv2_1Wrapper(napi_env env) {
        napi_value wrapper;
        napi_create_object(env, &wrapper);
        
        // 添加getString方法
        napi_property_descriptor getStringDesc = {
            "getString", nullptr, GetString, nullptr, nullptr, nullptr, napi_default, nullptr
        };
        napi_define_properties(env, wrapper, 1, &getStringDesc);
        
        // 添加getStringWithParam方法
        napi_property_descriptor getStringWithParamDesc = {
            "getStringWithParam", nullptr, GetStringWithParam, nullptr, nullptr, nullptr, napi_default, nullptr
        };
        napi_define_properties(env, wrapper, 1, &getStringWithParamDesc);
        
        // 添加getStringLength方法
        napi_property_descriptor getStringLengthDesc = {
            "getStringLength", nullptr, GetStringLength, nullptr, nullptr, nullptr, napi_default, nullptr
        };
        napi_define_properties(env, wrapper, 1, &getStringLengthDesc);
        
        return wrapper;
    }
    
    static napi_value CreateLv2_2Wrapper(napi_env env) {
        napi_value wrapper;
        napi_create_object(env, &wrapper);
        
        // 添加getInt32方法
        napi_property_descriptor getInt32Desc = {
            "getInt32", nullptr, GetInt32, nullptr, nullptr, nullptr, napi_default, nullptr
        };
        napi_define_properties(env, wrapper, 1, &getInt32Desc);
        
        // 添加addInt32方法
        napi_property_descriptor addInt32Desc = {
            "addInt32", nullptr, AddInt32, nullptr, nullptr, nullptr, napi_default, nullptr
        };
        napi_define_properties(env, wrapper, 1, &addInt32Desc);
        
        // 添加getDouble方法
        napi_property_descriptor getDoubleDesc = {
            "getDouble", nullptr, GetDouble, nullptr, nullptr, nullptr, napi_default, nullptr
        };
        napi_define_properties(env, wrapper, 1, &getDoubleDesc);
        
        // 添加getStatus方法
        napi_property_descriptor getStatusDesc = {
            "getStatus", nullptr, GetStatus, nullptr, nullptr, nullptr, napi_default, nullptr
        };
        napi_define_properties(env, wrapper, 1, &getStatusDesc);
        
        return wrapper;
    }

private:
    // api_lv2_1的方法实现
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
    
    // api_lv2_2的方法实现
    static napi_value GetInt32(napi_env env, napi_callback_info info) {
        int result = api::GetInstance().getLv2_2().getInt32();
        
        napi_value resultValue;
        napi_create_int32(env, result, &resultValue);
        return resultValue;
    }
    
    static napi_value AddInt32(napi_env env, napi_callback_info info) {
        size_t argc = 2;
        napi_value args[2];
        napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
        
        if (argc < 2) {
            napi_throw_error(env, nullptr, "需要两个参数");
            return nullptr;
        }
        
        int32_t a, b;
        napi_get_value_int32(env, args[0], &a);
        napi_get_value_int32(env, args[1], &b);
        
        int result = api::GetInstance().getLv2_2().addInt32(a, b);
        
        napi_value resultValue;
        napi_create_int32(env, result, &resultValue);
        return resultValue;
    }
    
    static napi_value GetDouble(napi_env env, napi_callback_info info) {
        double result = api::GetInstance().getLv2_2().getDouble();
        
        napi_value resultValue;
        napi_create_double(env, result, &resultValue);
        return resultValue;
    }
    
    static napi_value GetStatus(napi_env env, napi_callback_info info) {
        std::string result = api::GetInstance().getLv2_2().getStatus();
        
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
    return APIWrapper::CreateLv2_1Wrapper(env);
}

static napi_value GetLv2_2(napi_env env, napi_callback_info info) {
    return APIWrapper::CreateLv2_2Wrapper(env);
}

// 模块初始化
static napi_value Init(napi_env env, napi_value exports) {
    // 初始化主API
    api::GetInstance().initialize();
    
    napi_property_descriptor desc[] = {
        {"getMainStatus", nullptr, GetMainStatus, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"initialize", nullptr, Initialize, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getLv2_1", nullptr, GetLv2_1, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getLv2_2", nullptr, GetLv2_2, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

// 模块注册
static napi_module api_lv2_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "api_lv2",
    .nm_priv = nullptr,
    .reserved = {nullptr}
};

extern "C" __attribute__((constructor)) void RegisterAPILv2Module(void) {
    napi_module_register(&api_lv2_module);
} 