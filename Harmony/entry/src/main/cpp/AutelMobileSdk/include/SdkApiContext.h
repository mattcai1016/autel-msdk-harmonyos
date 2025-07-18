#ifndef SDK_API_CONTEXT_H
#define SDK_API_CONTEXT_H

#include "Common.h"
#include "BaseType.h"

#ifdef _WIN32
#include "Logger.h"
#else
#include <autelsdk-support/simple-logger/Logger.h>
#endif

namespace AutelMobileSdk
{
#define API_DEBUG(fmt, ...) DBG_DEBUG(SdkApiContext::GetInstance().GetLogger(), static_cast<int>(SdkApiContext::GetInstance().GetModule()), fmt, ##__VA_ARGS__)
#define API_INFO(fmt, ...) DBG_INFO(SdkApiContext::GetInstance().GetLogger(), static_cast<int>(SdkApiContext::GetInstance().GetModule()), fmt, ##__VA_ARGS__)
#define API_WARN(fmt, ...) DBG_WARN(SdkApiContext::GetInstance().GetLogger(), static_cast<int>(SdkApiContext::GetInstance().GetModule()), fmt, ##__VA_ARGS__)
#define API_ERROR(fmt, ...) DBG_ERROR(SdkApiContext::GetInstance().GetLogger(), static_cast<int>(SdkApiContext::GetInstance().GetModule()), fmt, ##__VA_ARGS__)
#define API_FATAL(fmt, ...) DBG_FATAL(SdkApiContext::GetInstance().GetLogger(), static_cast<int>(SdkApiContext::GetInstance().GetModule()), fmt, ##__VA_ARGS__)

class AUTELSDK_API SdkApiContext
{
public:
    static SdkApiContext& GetInstance();

public:
    simple_logger::Log& GetLogger();
    SdkModule GetModule() const;

private:
    SdkApiContext();
    SdkApiContext(const SdkApiContext&) = delete;
    SdkApiContext(SdkApiContext&&) = delete;
    SdkApiContext operator=(const SdkApiContext&) = delete;
    SdkApiContext operator=(SdkApiContext&&) = delete;
    ~SdkApiContext() = default;

private:
    simple_logger::Log& m_log;
    SdkModule m_module = SdkModule::Api;
};
} // namespace AutelMobileSdk

#endif
