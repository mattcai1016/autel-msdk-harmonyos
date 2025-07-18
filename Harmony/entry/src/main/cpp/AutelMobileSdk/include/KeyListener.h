#ifndef KEY_LISTENER_H
#define KEY_LISTENER_H

#include <optional>
#include "IKeyListener.h"
#include "Util.h"
#include "SdkApiContext.h"

namespace AutelMobileSdk
{
template <typename T>
class AUTELSDK_API KeyListener : public IKeyListener
{
public:
    using IKeyListener::IKeyListener;

public:
    virtual void OnValueChanged(const std::any& oldValue, const std::any& newValue)  override
    {
        try {
            std::optional<T> oldVal;
            if (oldValue.has_value()) {
                oldVal = std::any_cast<T>(oldValue);
            }

            T newVal = std::any_cast<T>(newValue);

            // API_DEBUG("KeyListener::OnValueChanged: keyName={}, oldValue=[{}], newValue=[{}]",
            //     m_keyName, ToString(oldVal), ToString(newVal));

            OnValueChanged(oldVal, newVal); // 委托给实际的执行函数处理
        } catch (const std::bad_any_cast& e) {
            API_ERROR("Failed to cast from [{}] to [{}], error={}",
                GetRealTypeName(newValue.type().name()), GetTypeName<T>(), e.what());
        }
    }

    // 派生类只需要实现此接口
    virtual void OnValueChanged([[maybe_unused]]const std::optional<T>& oldValue, [[maybe_unused]]const T& newValue)
    {
        // 由派生类重写
    }

    virtual std::string ValueToString([[maybe_unused]]const std::any& data) const override
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

    // 派生类只需要实现此接口
    virtual std::string ValueToString(const T& value) const
    {
        // 派生类可根据需要重写此接口
        return ToString(value);
    }
};

template <>
class AUTELSDK_API KeyListener<void> : public IKeyListener
{
public:
    using IKeyListener::IKeyListener;

public:
    virtual void OnValueChanged([[maybe_unused]]const std::any& oldValue, [[maybe_unused]]const std::any& newValue)  override
    {
        API_DEBUG("KeyListener::OnValueChanged: keyName={}", m_keyName);
    }

    virtual std::string ValueToString([[maybe_unused]]const std::any& value) const override
    {
        return FORMAT("keyName={}, No value", m_keyName);
    }
};

//在当前的模式下， std::any跨模块(exe + dll)是有风险的，所以在这里加一层 (*_*)
template<typename T>
class AUTELSDK_API KeyListenerWrap : public KeyListener<T>
{
    std::shared_ptr<KeyListener<T>> m_listener;
public:
    KeyListenerWrap(std::shared_ptr<KeyListener<T>> listener) : m_listener(listener){}

    void OnValueChanged(const std::optional<T>& oldValue, const T& newValue) override
    {
        m_listener->OnValueChanged(oldValue, newValue);
    }
};

template<>
class AUTELSDK_API KeyListenerWrap<void> : public KeyListener<void>
{
    std::shared_ptr<KeyListener<bool>> m_listener;
public:
    KeyListenerWrap(std::shared_ptr<KeyListener<bool>> listener) : m_listener(listener){}

    void OnValueChanged([[maybe_unused]]const std::any& oldValue, [[maybe_unused]]const std::any& newValue) override
    {
        bool old_value_is_void = true;
        bool new_value_is_void = true;
        m_listener->OnValueChanged(old_value_is_void, new_value_is_void);
    }
};

} // namespace AutelMobileSdk

#endif
