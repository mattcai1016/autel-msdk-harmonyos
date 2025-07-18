#ifndef ICONTROLLCOMPLETIONLISTENER_H
#define ICONTROLLCOMPLETIONLISTENER_H

#include <memory>
#include <unordered_map>

#include "Common.h"
#include "CompletionListener.h"

namespace AutelMobileSdk
{

class AUTELSDK_API IControllCompletionListener
{
public:
    IControllCompletionListener();

    virtual ~IControllCompletionListener();

    virtual void OnSuccess();
    void EmplaceData(int32_t key, int32_t value);
    void EmplaceError(int32_t key, int32_t value);

protected:
    std::unordered_map<int32_t, int32_t> m_mpData;
    std::unordered_map<int32_t, int32_t> m_mpErrorCode;
};

template <typename T>
class AUTELSDK_API CompletionListenerListItemSwitchState : public CompletionListener<T>
{
public:
    using CompletionListener<T>::CompletionListener;
public:
    CompletionListenerListItemSwitchState(int32_t s32DeviceId, int32_t retry = 0);
    void OnSuccess(const T& data) override;
    void OnFailure(AutelStatusCode errorCode, const std::string& msg) override;
    bool IsCompeleted() const;
    AutelStatusCode GetErrorCode() const;

    int32_t GetDeviceId() const;

    int32_t GetResult() const;

private:
        int32_t m_DeviceId;
        bool m_blComplete = false;
        int32_t m_s32Sw = -1;
        int32_t m_retry = 0;
        AutelStatusCode m_eCode = AutelStatusCode::Unknown;
};


template <>
class CompletionListenerListItemSwitchState<void> : public CompletionListener<void>
{
public:
    using CompletionListener<void>::CompletionListener;
public:
    CompletionListenerListItemSwitchState(int32_t s32DeviceId, int32_t retry = 0):m_DeviceId(s32DeviceId), m_retry(retry){}
    void OnSuccess([[maybe_unused]]const std::any& data) override
    {
        API_DEBUG("[SUCCESS]: operName={}, return nothing.", ICompletionListener::m_operName);
        m_eCode = AutelStatusCode::ProtoResponseSuccess;
        m_blComplete = true;
    }
    void OnFailure(AutelStatusCode errorCode, const std::string& msg) override
    {
        m_eCode = errorCode;
        if (m_retry > 0)
        {
            m_retry--;
            API_DEBUG("[FAILED]: operName={}, errMsg=[{}] retry={}", ICompletionListener::m_operName, msg, m_retry);
            return;
        }
        API_DEBUG("[FAILED]: operName={}, errMsg=[{}]", ICompletionListener::m_operName, msg);
        m_blComplete = true;
    }
    bool IsCompeleted() const { return m_blComplete; }
    AutelStatusCode GetErrorCode() const { return m_eCode; }
    int32_t GetDeviceId() const { return m_DeviceId; }
    int32_t GetResult() const { return m_s32Sw; }

private:
    int32_t m_DeviceId;
    bool m_blComplete = false;
    int32_t m_s32Sw = -1;
    int32_t m_retry = 0;
    AutelStatusCode m_eCode = AutelStatusCode::Unknown;
};

template <typename T>
class ListContainerCompletionContext
{
public:
    ListContainerCompletionContext(){}
    ~ListContainerCompletionContext();
    ListContainerCompletionContext& AttachListener(std::shared_ptr<IControllCompletionListener> lstn);
    ListContainerCompletionContext& RunOnece(std::function<void()> runInitHandler);
    void EmplaceData(int32_t key, int32_t value);
    void EmplaceError(int32_t key, int32_t value);
    void EmplaceBack(std::shared_ptr<CompletionListenerListItemSwitchState<T>> item);
    void WaiteResult(int msec = 3550, int interval = 30); // sdk timeout 3500
    void Exec(int timeout = 3550);
private:
    void OnSuccess();

private:
    std::list<std::shared_ptr<CompletionListenerListItemSwitchState<T> >> m_Imp;
    std::shared_ptr<IControllCompletionListener> m_listener = nullptr;
    std::function<void()> m_funInit;
    std::thread m_thread;
    bool m_running = false;
};

} // namespace AutelMobileSdk
#endif // ICONTROLLCOMPLETIONLISTENER_H
