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
 * AutelSdk SDK Integration - Native Implementation
 */
#include "napi/native_api.h"
#include "hilog/log.h"
#include <cstdio>
#include <memory>
#include <string>
#include <exception>
#include "SdkApiManager.h"
#include <string>
#include <iostream>


const int DOMAIN = 0xFF00;
const char *TAG = "[MsdkHarmonyMethods]";

// Global SDK manager instance
static AutelMobileSdk::SdkApiManager* g_sdkManager = nullptr;

// Helper function to create result object
static napi_value CreateResultObject(napi_env env, bool success, const std::string& message) {
    napi_value result;
    napi_create_object(env, &result);
    
    napi_value successValue;
    napi_get_boolean(env, success, &successValue);
    napi_set_named_property(env, result, "success", successValue);
    
    napi_value messageValue;
    napi_create_string_utf8(env, message.c_str(), NAPI_AUTO_LENGTH, &messageValue);
    napi_set_named_property(env, result, "message", messageValue);
    
    return result;
}

// Helper function to create result object with additional data
static napi_value CreateResultObject(napi_env env, bool success, const std::string& message, 
                                   const std::string& key, const std::string& value) {
    napi_value result = CreateResultObject(env, success, message);
    
    napi_value dataValue;
    napi_create_string_utf8(env, value.c_str(), NAPI_AUTO_LENGTH, &dataValue);
    napi_set_named_property(env, result, key.c_str(), dataValue);
    
    return result;
}

// Helper function to create result object with boolean data
static napi_value CreateResultObject(napi_env env, bool success, const std::string& message, 
                                   const std::string& key, bool value) {
    napi_value result = CreateResultObject(env, success, message);
    
    napi_value dataValue;
    napi_get_boolean(env, value, &dataValue);
    napi_set_named_property(env, result, key.c_str(), dataValue);
    
    return result;
}

// Initialize AutelSdk SDK
static napi_value InitAutelSdk(napi_env env, napi_callback_info info) {
    try {
        size_t argc = 1;
        napi_value argv[1] = {nullptr};
        napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

        bool isDebugMode = false;
        if (argc > 0) {
            napi_get_value_bool(env, argv[0], &isDebugMode);
        }

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "Initializing AutelSdk SDK with debug mode: %s", 
                    isDebugMode ? "true" : "false");

        // Check if SDK is already initialized
        if (g_sdkManager != nullptr) {
            OH_LOG_Print(LOG_APP, LOG_WARN, DOMAIN, TAG, "SDK already initialized");
            return CreateResultObject(env, false, "SDK already initialized");
        }

        // Get SDK manager instance
        g_sdkManager = &AutelMobileSdk::SdkApiManager::GetInstance();

        // Initialize SDK
        g_sdkManager->Init(isDebugMode);

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "AutelSdk SDK initialized successfully!");

        return CreateResultObject(env, true, "SDK initialized successfully");

    } catch (const std::exception& e) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to initialize SDK: %s", e.what());
        return CreateResultObject(env, false, std::string("SDK initialization failed: ") + e.what());
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to initialize SDK: Unknown error");
        return CreateResultObject(env, false, "SDK initialization failed: Unknown error");
    }
}

// Get SDK version
static napi_value GetSdkVersion(napi_env env, napi_callback_info info) {
    try {
        if (!g_sdkManager) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "SDK not initialized");
            return CreateResultObject(env, false, "SDK not initialized");
        }

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "Getting SDK version");

        std::string version = g_sdkManager->GetSdkVersion();

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "SDK version: %s", version.c_str());

        return CreateResultObject(env, true, "Version retrieved successfully", "version", version);

    } catch (const std::exception& e) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to get SDK version: %s", e.what());
        return CreateResultObject(env, false, std::string("Failed to get version: ") + e.what());
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to get SDK version: Unknown error");
        return CreateResultObject(env, false, "Failed to get version: Unknown error");
    }
}

// Destroy SDK
static napi_value DestroySdk(napi_env env, napi_callback_info info) {
    try {
        if (!g_sdkManager) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "SDK not initialized");
            return CreateResultObject(env, false, "SDK not initialized");
        }

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "Destroying AutelSdk SDK");

        g_sdkManager->Destroy();
        g_sdkManager = nullptr;

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "AutelSdk SDK destroyed successfully!");

        return CreateResultObject(env, true, "SDK destroyed successfully");

    } catch (const std::exception& e) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to destroy SDK: %s", e.what());
        return CreateResultObject(env, false, std::string("SDK destruction failed: ") + e.what());
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to destroy SDK: Unknown error");
        return CreateResultObject(env, false, "SDK destruction failed: Unknown error");
    }
}

// Get SDK full version
static napi_value GetSdkFullVersion(napi_env env, napi_callback_info info) {
    try {
        if (!g_sdkManager) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "SDK not initialized");
            return CreateResultObject(env, false, "SDK not initialized");
        }

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "Getting SDK full version");

        std::string fullVersion = g_sdkManager->GetSdkFullVersion();

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "SDK full version: %s", fullVersion.c_str());

        return CreateResultObject(env, true, "Full version retrieved successfully", "fullVersion", fullVersion);

    } catch (const std::exception& e) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to get SDK full version: %s", e.what());
        return CreateResultObject(env, false, std::string("Failed to get full version: ") + e.what());
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to get SDK full version: Unknown error");
        return CreateResultObject(env, false, "Failed to get full version: Unknown error");
    }
}

// Check SDK validation
static napi_value IsSdkValidate(napi_env env, napi_callback_info info) {
    try {
        if (!g_sdkManager) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "SDK not initialized");
            return CreateResultObject(env, false, "SDK not initialized");
        }

        size_t argc = 1;
        napi_value argv[1] = {nullptr};
        napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

        if (argc < 1) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "AuthorityState parameter required");
            return CreateResultObject(env, false, "AuthorityState parameter required");
        }

        int32_t authorityState;
        napi_get_value_int32(env, argv[0], &authorityState);

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "Checking SDK validation with authority state: %d", authorityState);

        bool isValid = g_sdkManager->IsSdkValidate(static_cast<AutelMobileSdk::AuthorityState>(authorityState));

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "SDK validation result: %s", 
                    isValid ? "valid" : "invalid");

        return CreateResultObject(env, true, "Validation check completed", "isValid", isValid);

    } catch (const std::exception& e) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to check SDK validation: %s", e.what());
        return CreateResultObject(env, false, std::string("Validation check failed: ") + e.what());
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to check SDK validation: Unknown error");
        return CreateResultObject(env, false, "Validation check failed: Unknown error");
    }
}

// Get gimbal type
static napi_value GetGimbalType(napi_env env, napi_callback_info info) {
    try {
        if (!g_sdkManager) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "SDK not initialized");
            return CreateResultObject(env, false, "SDK not initialized");
        }

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "Getting gimbal type");

        AutelMobileSdk::GimbalType gimbalType = g_sdkManager->GetGimbalType();

        OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "Gimbal type: %d", static_cast<int>(gimbalType));

        napi_value result = CreateResultObject(env, true, "Gimbal type retrieved successfully");

        napi_value gimbalTypeValue;
        napi_create_int32(env, static_cast<int32_t>(gimbalType), &gimbalTypeValue);
        napi_set_named_property(env, result, "gimbalType", gimbalTypeValue);

        return result;

    } catch (const std::exception& e) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to get gimbal type: %s", e.what());
        return CreateResultObject(env, false, std::string("Failed to get gimbal type: ") + e.what());
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to get gimbal type: Unknown error");
        return CreateResultObject(env, false, "Failed to get gimbal type: Unknown error");
    }
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    OH_LOG_Print(LOG_APP, LOG_INFO, DOMAIN, TAG, "NAPI Init called!"); // 确认模块加载
    std::cout << "Init napi start!!!" << std::endl;
    napi_status status;
    napi_property_descriptor desc[] = {
        {"initAutelSdk", nullptr, InitAutelSdk, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSdkVersion", nullptr, GetSdkVersion, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSdkFullVersion", nullptr, GetSdkFullVersion, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"isSdkValidate", nullptr, IsSdkValidate, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getGimbalType", nullptr, GetGimbalType, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"destroySdk", nullptr, DestroySdk, nullptr, nullptr, nullptr, napi_default, nullptr},
    };

    status = napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, DOMAIN, TAG, "Failed to register: %s", std::to_string(static_cast<int>(status)).c_str());
        return NULL;
    }
    
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "autel_sdk",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) { napi_module_register(&demoModule); }