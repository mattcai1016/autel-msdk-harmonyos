#ifndef IRC_DEVICE_H
#define IRC_DEVICE_H

#include "CompletionListener.h"
#include "ErrorCode.h"
#include "MiscDataType.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IRCDeviceOperator
{
public:
    // ==========参数查询、设置，执行操作类接口==========
    // 查询遥控器设备信息，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode GetDeviceInfo(uint32_t deviceId, std::shared_ptr<CompletionListener<std::vector<DroneComponentVerInfo>>> listener, int retryCount = 0) = 0;

    // 设置遥控器系统时间，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode SetSystemTime(uint32_t deviceId, const SystemTimeInfo& aiDetectConfig, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 摇杆操控模式，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode GetRockerControlMode(uint32_t deviceId, std::shared_ptr<CompletionListener<RcOperateMode>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRockerControlMode(uint32_t deviceId, RcOperateMode operateMode, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 进入遥控器校准模式，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode EnterCalibration(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出遥控器校准模式，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode ExitCalibration(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 开启遥控器定频上报，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode SetStateReport(uint32_t deviceId, EmRcStartHardwareState enable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
};
}
#endif // IAISERVICE_H
