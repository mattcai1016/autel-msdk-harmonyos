#ifndef IGIMBAL_H
#define IGIMBAL_H

#include <memory>

#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "GimbalKeyDataType.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IGimbal
{
public:
    // ==========参数查询、设置，执行操作类接口==========
    // 云台ROLL轴微调角度
    virtual ErrorCode GetRollAdjustAngle(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRollAdjustAngle(uint32_t deviceId, int rollAdjustAngle, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 云台PITCH轴微调角度
    virtual ErrorCode GetPitchAdjustAngle(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPitchAdjustAngle(uint32_t deviceId, int pitchAngleRange, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 云台YAW轴微调角度
    virtual ErrorCode GetYawAdjustAngle(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetYawAdjustAngle(uint32_t deviceId, int yawAdjustAngle, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 云台俯仰限位开关
    virtual ErrorCode GetPitchLimitState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPitchLimitState(uint32_t deviceId, int pitchAngelRange, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 云台俯仰速度
    virtual ErrorCode GetPitchSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPitchSpeed(uint32_t deviceId, int pitchSpeed, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 云台激光测距开关
    virtual ErrorCode GetLaserRangingState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetLaserRangingState(uint32_t deviceId, int s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 开启云台IMU校准
    virtual ErrorCode StartIMUCalibration(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 开启云台校准
    virtual ErrorCode StartCalibration(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 旋转四轴云台
    virtual ErrorCode RotateFourAxisAngle(uint32_t deviceId, const RotateFourAxisParams& rotateParams, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 云台角度控制
    virtual ErrorCode SetAngleValue(uint32_t deviceId, float angle, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 云台方向控制（朝下控制，云台归中）
    virtual ErrorCode SetOrientationValue(uint32_t deviceId, float orientation, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==========消息监听类接口==========
    // 云台上报参数
    virtual ErrorCode ListenGimbalState(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<GimbalState>>& listener) = 0;
    virtual void CancelListenGimbalState(uint32_t deviceId, ObjectId objectId) = 0;
};
}  // namespace AutelMobileSdk

#endif
