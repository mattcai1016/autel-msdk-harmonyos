#ifndef GIMBAL_KEY_DATATYPE_H
#define GIMBAL_KEY_DATATYPE_H

#include <string>
#include <cmath>
#include "Common.h"

namespace AutelMobileSdk
{

enum class GimbalWorkModeEnum
{
    GIMBAL_WORK_MODE_ATTITUDE = 0,                              // 锁定模式
    GIMBAL_WORK_MODE_FOLLOW = 1,                                // YAW跟踪
    GIMBAL_WORK_MODE_FPV = 2,                                   // FPV
    GIMBAL_WORK_MODE_PANORAMA = 3,                              // 全景
    UNKNOWN=0xff,
};

enum class GimbalMotorStatus
{
    NONE = 0,                                                   // 正常
    CLOSE = 2,                                                  // 关闭
};

struct GimbalOrientation
{
    const float DOWN = -1.5707963267948966f;
    const float DOWN_45 = DOWN / 2;
    const float FORWARD = .0f;
    std::string ToString() const;

};

struct AUTELSDK_API GimbalState
{
    bool isAttitudeValid = false;                               // 云台姿态是否初始化
    GimbalWorkModeEnum workMode = GimbalWorkModeEnum::UNKNOWN;  // 云台工作模式
    bool isCalibrating = false;                                 // 云台当前是否在校准
    GimbalMotorStatus motorStatus = GimbalMotorStatus::NONE;    // 电机状态
    bool isRollReachMax = false;                                // 云台 Roll 轴是否撞限位
    bool isOverheat = false;
    bool isIMUNeedCalibrate = false;                            // IMU是否需要校准
    float rotateAngle = .0f;
    float rotateAngleRange = .0f;
    bool isHardwareFail = false;
    bool isSleepForNoAttitude = false;
    bool isSleepForRollReachMax = false;
    int gimbalCalibrateStatus = 0;                               // 云台当前的角度校准状态
    int gimbalCalibratePercent = 0;                              // 云台当前的角度校准百分比（0-100）

    float pitchAngle = .0f;                                      // 云台的pitch角，高频上报中
    std::string ToString() const;
};

struct AUTELSDK_API RotateFourAxisParams
{
    int rotateSpeed = 0;
    int rotateDirection = 0;                                     // 旋转方向，+: clockwise; -:anti-clockwise
    int rotate = 0;                                              // 旋转，Each time set to 1; will be set to 0 after 0.05s

    std::string ToString() const;
};

}
#endif // GIMBALKEYDATATYPE_H
