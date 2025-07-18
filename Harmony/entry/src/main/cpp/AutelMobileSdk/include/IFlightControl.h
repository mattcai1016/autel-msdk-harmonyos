#ifndef IFLIGHT_CONTROL_H
#define IFLIGHT_CONTROL_H

#include <memory>
#include "ErrorCode.h"
#include "CompletionListener.h"
#include "FlightControlKeyDataType.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IFlightControl
{
public:
    // 指南针校准
    virtual ErrorCode CalibrateCompass(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 起飞
    virtual ErrorCode TakeOffAirCraft(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 自动降落开关
    virtual ErrorCode SetAutoLanding(uint32_t deviceId, int32_t autoLanding, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 启停电机开关
    virtual ErrorCode SetMotorState(uint32_t deviceId, bool working, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 自动返航开关
    virtual ErrorCode SetAutoBackState(uint32_t deviceId, const DroneAutoBack& autoBack, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 设置Home点为返航点
    virtual ErrorCode SetHomeAsBackLocation(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 自定义返航点设置
    virtual ErrorCode SetBackLocation(uint32_t deviceId, const SetHomeLocation& setHomeLocation, std::shared_ptr<CompletionListener<SetHomeLocation>> listener, int retryCount = 0) = 0;

    // 检查是否需要上传禁飞区文件
    virtual ErrorCode CheckNFZUploadOrNot(uint32_t deviceId, const NoFlyQzone& noFlyQzone, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;

    // 禁飞区使能(弃用)
    virtual ErrorCode SetNFZState(uint32_t deviceId, bool enable, std::shared_ptr<CompletionListener<bool>> listener, int retryCount = 0) = 0;

    // 姿态模式允许起飞
    virtual ErrorCode SetAttiTakeOff(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // IMU校准
    virtual ErrorCode CalibrateIMU(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取当前任务GUID
    virtual ErrorCode GetMissionGuid(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;

    // 取消低电返航
    virtual ErrorCode CancelLowPowerBack(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 设置磁力计异常允许起飞
    virtual ErrorCode AllowTakeOffWithMagnetometerAbnormal(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 设置第4轴云台竖屏模式
    virtual ErrorCode SetPortraitMode(uint32_t deviceId, bool enable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取飞控参数集合
    virtual ErrorCode GetFlightParam(uint32_t deviceId, std::shared_ptr<CompletionListener<DroneFlightParam>> listener, int retryCount = 0) = 0;

    // 收桨控制
    virtual ErrorCode RetractNestPaddleControl(uint32_t deviceId, std::shared_ptr<CompletionListener<NestWait>> listener, int retryCount = 0) = 0;

    // 一键起飞(非蜂群)
    virtual ErrorCode TakeoffToPoint(uint32_t deviceId, const DroneFlyToPoint &param, std::shared_ptr<CompletionListenerWithoutData>listener, int retryCount = 0) = 0;

    // 飞向目标点
    virtual ErrorCode FlyToPoint(uint32_t deviceId, const DroneFlyToPoint &param, std::shared_ptr<CompletionListenerWithoutData>listener, int retryCount = 0) = 0;

    // 飞向目标点停止
    virtual ErrorCode FlyToPointStop(uint32_t deviceId,  std::shared_ptr<CompletionListenerWithoutData>listener, int retryCount = 0) = 0;

    // 飞机急停
    virtual ErrorCode DroneEmergencyStop(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;

    // 控制云台角速度
    virtual ErrorCode SetGimbalAngleSpeed(uint32_t deviceId, const GimbalAngleSpeed &param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount) = 0;

};
}  // namespace AutelMobileSdk

#endif
