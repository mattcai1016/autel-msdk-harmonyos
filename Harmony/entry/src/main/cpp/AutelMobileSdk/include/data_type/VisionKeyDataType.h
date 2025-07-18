#ifndef VISION_KEY_DATATYPE_H
#define VISION_KEY_DATATYPE_H

#include <vector>
#include <string>

#include "Common.h"

namespace AutelMobileSdk
{
enum class VisionSensorPositionEnum
{
    FRONT = 0,
    REAR = 1,
    BOTTOM = 2,
    RIGHT = 3,
    LEFT = 4,
    TOP = 5,
    ALL = 255,
};

enum class VisionDistanceEnum
{
    INVALID = 0,        //视觉传感器与障碍物的距离无法确定
    SAFE = 1,           //视觉传感器与障碍物的距离大于2米
    DANGEROUS = 2,      //视觉传感器与障碍物的距离小于2米
};

enum class VisionBottomLedStatusEnum
{
    CLOSE = 0,          //关闭下视LED
    OPEN = 1,           //打开下视LED
    AUTO = 2,           //自动控制
    TWINKLE1 = 3,       //闪烁模式1
    TWINKLE2 = 4,       //闪烁模式2
};

struct AUTELSDK_API VisionRadarInfo
{
    int64_t timeStamp = 0;                 // 时间戳
    VisionSensorPositionEnum position;     // 传感器位置
    std::vector<float> distancesVector;    // 传感器与障碍物的多个距离

    std::string ToString() const;
};
}

#endif // VISIONKEYDATATYPE_H
