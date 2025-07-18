#ifndef ICOMPLETION_LISTENER_H
#define ICOMPLETION_LISTENER_H

#include <memory>
#include <string>
#include <any>
#include "ErrorCode.h"
#include "BaseType.h"
#include "Common.h"

namespace AutelMobileSdk
{
class AUTELSDK_API ICompletionListener
{
public:
    ICompletionListener();
    ICompletionListener(const std::string& operName);
    virtual ~ICompletionListener();

public:
    void SetOperName(const std::string& operName);
    virtual void OnSuccess(const std::any& data);
    virtual void OnFailure(AutelStatusCode errorCode, const std::string& msg = "");

    virtual void InitProgressParam(uint64_t totalValue, uint64_t initValue = 0, uint64_t valueUnit = 8);
    virtual void OnProgressUpdate(uint64_t currentValue);
    double GetProcessProgress() const;
    double GetProcessSpeed() const;
    uint64_t GetTotalValue() const;
    uint64_t GetFinishedValue() const;

    virtual void OnProgressInfoUpdate(double progress, double speed);

    virtual std::string AnyToString(const std::any& data);

protected:
    uint64_t m_lastProgressUpdateTime = 0;
    uint64_t m_totalValue = 0;
    uint64_t m_initValue = 0;
    uint64_t m_lastValue = 0;
    uint64_t m_valueUnit = 8;                   // 前述数值默认为字节，1个字节bit数为8

    double m_progress = 0.0;
    double m_speed = 0.0;

    std::string m_operName;
};

class IMultiDevCompletionListener
{
public:
    IMultiDevCompletionListener();
    IMultiDevCompletionListener(const std::string& operName);
    virtual ~IMultiDevCompletionListener();

public:
    void SetOperName(const std::string& operName);
    virtual void OnSuccess(DeviceId deviceId, const std::any& data);
    virtual void OnFailure(DeviceId deviceId, AutelStatusCode errorCode, const std::string& msg = "");
    virtual std::string AnyToString(const std::any& data);

protected:
    std::string m_operName;
};

} // namespace AutelMobileSdk

#endif
