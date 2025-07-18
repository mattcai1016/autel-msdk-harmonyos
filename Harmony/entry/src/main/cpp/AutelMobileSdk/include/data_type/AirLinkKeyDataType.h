#ifndef AIR_LINK_KEY_DATA_TYPE_H
#define AIR_LINK_KEY_DATA_TYPE_H

#include <vector>
#include <string>

#include "Common.h"

namespace AutelMobileSdk
{
enum class AirLinkBandModeEnum
{
    BAND_MODE_UNKNOWN = 0,      // 未获取到位置
    BAND_MODE_24G = 1,          // 2.4G
    BAND_MODE_52G = 2,          // 5.2G
    BAND_MODE_24_52G = 3,       // 2.4与5.2自动切换
    BAND_MODE_58G = 4,          // 5.8G
    BAND_MODE_24_58G = 5,       // 2.4与5.8自动切换
    BAND_MODE_52_58G = 6,       // 5.2与5.8自动切换
    BAND_MODE_24_52_58G = 7,    // 2.4、5.2与5.8自动切换
};

enum class VideoTransMissionModeEnum
{
    LOW_LATENCY = 1,        // 流畅 Low Latency
    HIGH_QUALITY = 2,       // 高清 High Quality
    SUPER = 3,              // 2.7K 超高清 Super
    UNKNOWN = 255,          // Unknown
};

enum class FccCeModeEnum
{
    CE = 0,     // CE（自适应模式）
    FCC = 1,    // FCC（全频段模式）
};

enum class AirLinkMatchStatusEnum
{
    STATUS_UNKNOWN = 0,     // Unknown
    STATUS_PAIRING = 1,     // 开始对频，对频中
    STATUS_SUC = 2,         // 对频成功
    STATUS_FAILED = 3,      // 对频超时或对频启动失败
};

enum class AirLinkDeviceTypeEnum
{
    UNKNOWN = 0,
    REMOTE = 1,     // 遥控器
    DRONE = 2,      // 飞机
};

enum class HighSpeedEnum
{
    NORMAL = 0,         // 普通模式
    HIGH_UPLOAD = 1,    // 高速上传文件（上传任务文件）
    HIGH_DOWNLOAD = 2,  // 2-高速下载模式（下载照片或视频）
    EXCLUSIVE = 3,      // 独占模式
    EXIT = 4,           // 退出
};

enum class DynamicAdjustEnum
{
    FIX = 0,            // 固定频段
    COMPLIANCE = 1,     // 合规频段自适应
    ALL = 2,            // 全频段自适应
};

struct AUTELSDK_API AirlinkMatchCostTimeBean
{
    AirLinkDeviceTypeEnum deviceType = AirLinkDeviceTypeEnum::UNKNOWN;
    int costTime = 0;

    std::string ToString() const;
};
//图传信号强度上报
struct AUTELSDK_API AirLinkSignalStrengthBean
{
    int interferenceSignalStrength = 0;//图传干扰信号强度
    int realSignalStrength = 0;//图传真实信号强度

    //重载==
    bool operator ==(const AirLinkSignalStrengthBean& other) const
    {
        return interferenceSignalStrength == other.interferenceSignalStrength
               && realSignalStrength == other.realSignalStrength;
    }

    std::string ToString() const;
};

struct AUTELSDK_API GimbalTransmissionBean
{
    std::string label;
    int cameraId = 0;

    std::string ToString() const;
};

struct AUTELSDK_API GimbalTransmission
{
    std::vector<GimbalTransmissionBean> gimbalTransmissionBean;

    std::string ToString() const;
};
} // namespace AutelMobileSdk

#endif
