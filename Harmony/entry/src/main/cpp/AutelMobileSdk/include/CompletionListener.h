#ifndef COMPLETION_LISTENER_H
#define COMPLETION_LISTENER_H

#include <memory>
#include "ICompletionListener.h"
#include "Util.h"
#include "SdkApiContext.h"

namespace AutelMobileSdk
{
template <typename T>
class AUTELSDK_API CompletionListener : public ICompletionListener
{
public:
    using ICompletionListener::ICompletionListener;

public:
    virtual void OnSuccess(const std::any& data) override
    {
        // 转换成指向实际类型的指针，委托给可以处理此结果的执行函数
        auto value = AnyCast<T>(data);
        if (!value.has_value()) {
            auto errorMsg = FORMAT("The value of {} type should be return, but return nothing.", GetTypeName<T>());
            OnFailure(AutelStatusCode::InternalError, errorMsg);
            return;
        } else if (value.value() == nullptr) {
            auto errorMsg = FORMAT("Failed to cast data from [{}] to [{}], value is nullptr,throw std::bad_cast.",
                GetRealTypeName(data.type().name()), GetTypeName<T>());
            OnFailure(AutelStatusCode::InternalError, errorMsg);
            return;
        }

        OnSuccess(*value.value());
        API_DEBUG("[SUCCESS]: operName={}, returnValue=[{}]", m_operName, AnyToString(data));
    }

    virtual void OnSuccess(const T& value)
    {
        // 由派生类重写
    }

    virtual std::string AnyToString(const std::any& data) override
    {
        auto value = AnyCast<T>(data);
        if (!value.has_value()) {
            return "";
        }

        if (value.value() == nullptr) {
            auto msg = FORMAT("[bad_cast] Failed to cast data from [{}] to [{}]",
                GetRealTypeName(data.type().name()), GetTypeName<T>());
            return msg;
        }

        return ToString(*value.value());
    }
};

template <>
class CompletionListener<void> : public ICompletionListener
{
public:
    using ICompletionListener::ICompletionListener;

public:

    virtual void OnSuccess([[maybe_unused]]const std::any& data) override
    {
        API_DEBUG("[SUCCESS]: operName={}, return nothing.", m_operName);
    }

    virtual std::string AnyToString([[maybe_unused]]const std::any& data) override
    {
        return "nothing";
    }
};

using CompletionListenerWithoutData = CompletionListener<void>;

template <typename T>
class MultiDevCompletionListener : public IMultiDevCompletionListener
{
public:
    using IMultiDevCompletionListener::IMultiDevCompletionListener;

public:
    virtual void OnSuccess(DeviceId deviceId, const std::any& data) override
    {
        // 转换成指向实际类型的指针，委托给可以处理此结果的执行函数
        auto value = AnyCast<T>(data);
        if (!value.has_value()) {
            auto errorMsg = FORMAT("The value of {} type should be return, but return nothing. deviceId={}",
                GetTypeName<T>(), deviceId);
            OnFailure(AutelStatusCode::InternalError, errorMsg);
            return;
        } else if (value.value() == nullptr) {
            auto errorMsg = FORMAT("Failed to cast data from [{}] to [{}], throw std::bad_cast. deviceId={}",
                GetRealTypeName(data.type().name()), GetTypeName<T>(), deviceId);
            OnFailure(AutelStatusCode::InternalError, errorMsg);
            return;
        }

        OnSuccess(deviceId, *value.value());
        API_DEBUG("[SUCCESS]: deviceId={}, operName={}, returnValue=[{}]", deviceId, m_operName, AnyToString(data));
    }

    virtual void OnSuccess(DeviceId deviceId, const T& value)
    {
        // 由派生类重写
    }

    virtual std::string AnyToString([[maybe_unused]]const std::any& data) override
    {
        auto value = AnyCast<T>(data);
        if (!value.has_value()) {
            return "";
        }

        if (value.value() == nullptr) {
            auto msg = FORMAT("[bad_cast] Failed to cast data from [{}] to [{}]",
                GetRealTypeName(data.type().name()), GetTypeName<T>());
            return msg;
        }

        return ToString(*value.value());
    }
};

template <>
class MultiDevCompletionListener<void> : public IMultiDevCompletionListener
{
public:
    using IMultiDevCompletionListener::IMultiDevCompletionListener;

public:
    virtual void OnSuccess(DeviceId deviceId, [[maybe_unused]]const std::any& data) override
    {
        API_DEBUG("[SUCCESS]: deviceId={}, operName={}, return nothing.", deviceId, m_operName);
    }

    virtual std::string AnyToString([[maybe_unused]]const std::any& data) override
    {
        return "";
    }
};

//在当前的模式下， std::any跨模块(exe + dll)是有风险的，所以在这里加一层 (*_*)
//Failed to cast data from [float] to [float], throw std::bad_cast.
template<typename T>
class CompletionListenerWrap : public CompletionListener<T>
{
    std::shared_ptr<CompletionListener<T>> m_listener;
public:
    CompletionListenerWrap(std::shared_ptr<CompletionListener<T>> listener) : m_listener(listener){}

    void OnSuccess(const T& value) override
    {
        m_listener->OnSuccess(value);
    }
};
} // namespace AutelMobileSdk
#endif
