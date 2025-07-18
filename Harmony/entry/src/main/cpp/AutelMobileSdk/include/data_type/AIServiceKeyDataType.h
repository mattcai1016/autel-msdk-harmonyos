#ifndef AI_SERVICE_KEY_DATATYPE_H
#define AI_SERVICE_KEY_DATATYPE_H

#include <string>
#include <vector>

#include "Common.h"

namespace AutelMobileSdk
{
enum class DetectTargetEnum
{
    BACKGROUND = 0,                 // 背景
    ANIMAL = 1,                     // 动物
    BOAT = 2,                       // 船
    CAR = 3,                        // 小车
    PERSON = 4,                     // 行人
    RIDER = 5,                      // 骑行者
    VEHICLE = 6,                    // 大车
    INSULATOR = 10,                 // 绝缘端子
    CROSSARMPOINT = 11,             // 横担端挂点——Cross arm end hanging point
    WIREPOINT = 12,                 // 导线端挂点——Wire end hanging point
    EARTHWIREPOINT = 13,            // 导地线挂点——Ground wire hanging point
    DAMPER = 14,                    // 导地线挂点——Vibration hammer
    POLE = 15,                      // 导地线挂点——Electric pole
    TOWER = 16,                     // 导地线挂点——Tower body
    TOWER_HEAD = 17,                // 导地线挂点——Tower head
    TOWER_FOOT = 18,                // 导地线挂点——"Taki"
    SECURITY_CIVILIAN = 30,         // 平民
    SECURITY_SOLDIER = 31,          // 士兵
    SECURITY_ARMORED_VEHICLE = 32,  // 装甲车
    SECURITY_EQUIPMENT = 33,        // 武器装备
    SECURITY_AERIAL_VEHICLE = 34,   // 无人机
    SECURITY_SMOKE = 35,            // 烟雾
    SECURITY_FIRE = 36,             // 火
    UNKNOWN = 99,                   // 未检测到目标，需要清除屏幕上的目标点
};

enum class AiDeTectSceneTypeEnum
{
    SCENE_TYPE_UNIVERSAL = 0,   // 通用
    SCENE_TYPE_SECURITY = 1,    // 安防
    SCENE_TYPE_GRID = 2,        // 电网场景/电力巡检场景
    UNRECOGNIZED = -1,          // 无法识别
};

enum class AiLensTypeEnum
{
    NONE = -1,      // 未知
    Visible = 0,    // 可见光
    INFRARED = 1,   // 红外
    Night = 2,      // 夜视
};

struct AUTELSDK_API DetectObjectInfo
{
    float startX = 0;                                   // 目标的像素坐标x
    float startY = 0;                                   // 目标的像素坐标y
    float width = 0;                                    // 目标框宽度
    float height = 0;                                   // 目标框的高度
    DetectTargetEnum type = DetectTargetEnum::UNKNOWN;  // 目标的类型
    int status = 0;                                     // 目标跟踪类型
    int objectID = 0;                                   // 目标id
    int dangerLevel = 0;
    double latitude = 0.0;
    double longtitude = 0.0;
    double altitude = 0.0;

    std::string ToString() const;
};

struct AUTELSDK_API DetectTrackAreaNotify
{
    int resolutionWidth = 0;                     // 分辨率宽度
    int resolutionHeight = 0;                    // 分辨率高度
    int objNum = 0;                              // 数量
    std::vector<DetectObjectInfo> infoList;      // 跟踪框数组

    std::string ToString() const;
};

struct AUTELSDK_API ObjectInfo
{
    float startX = 0;                                       // 目标的像素坐标x
    float startY = 0;                                       // 目标的像素坐标y
    float width = 0;                                        // 目标框宽度
    float height = 0;                                       // 目标框的高度
    DetectTargetEnum type = DetectTargetEnum::UNKNOWN;      // 目标的类型
    int objectId = 0;                                       // 目标ID
    int status = 0;                                         // 目标跟踪类型
    float confidence = 0;                                   // 目标置信度
    int camouflage = 0;                                     // 仅对目标为人  迷彩
    int gun = 0;                                            // 仅对目标为人  枪支
    int tacticalBackpack = 0;                               // 仅对目标为人  战术背包
    int pose = 0;                                           // 目标姿态：person only, 0 stand 1 sit 2 lie 3 ride
    int action = 0;                                         // 仅对目标为人  动作
    int dummpSoldier = 0;                                   // 仅对目标为人  假人
    int dangerLevel = 0;                                    // 仅对目标为人 危险等级 1,2,3,4,5 1-最高 5-最低
    std::string info;                                       // 附加信息：info of targets

    std::string ToString() const;
};

struct AUTELSDK_API TrackAreaNotify
{
    int64_t timestamp = 0;            // 时间戳
    int frameId = 0;                  // id
    int resolutionWidth = 0;          // 分辨率宽度
    int resolutionHeight = 0;         // 分辨率高度
    int objNum = 0;                   // 数量
    std::vector<ObjectInfo> infoList;   // 跟踪框数组

    std::string ToString() const;
};

struct AUTELSDK_API AIDetectConfig
{
    AiDeTectSceneTypeEnum sceneType = AiDeTectSceneTypeEnum::UNRECOGNIZED;  // 当前的场景类型，取值参考：AI_DETECT_SCENE_TYPE
    std::vector<DetectTargetEnum> targetTypeList;                           // 当前用户选择的检测类型列表,取值参考：TARGET_TYPE，列表为空时代表使用场景类型
    AiLensTypeEnum aiLensType = AiLensTypeEnum::Visible;                    // 镜头类型

    std::string ToString() const;
};

struct AUTELSDK_API DetectPhotoInfo
{
    int64_t timeStamp = 0;
    std::string photoPath;
    std::vector<DetectObjectInfo> objectList;

    std::string ToString() const;
};
}

#endif // AISERVICEKEYDATATYPE_H
