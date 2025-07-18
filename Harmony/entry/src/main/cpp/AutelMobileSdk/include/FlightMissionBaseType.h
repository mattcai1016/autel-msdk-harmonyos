
#ifndef FLIGHT_MISSION_BASE_TYPE_H
#define FLIGHT_MISSION_BASE_TYPE_H

#include <limits>
#include <cstdint>

namespace AutelMobileSdk
{
enum class TrackType
{
    AUTO_TRACK = 0,
    INFRARED_TRACK = 1
};

enum class DroneHeadingControl
{    
    FOLLOW_ROUTE_DIRECTION = 1,          // 沿航线方向
    MANUAL_CONTROL = 2,                  // 手动控制
    CUSTOM = 3,                          // 自定义
    FOLLOW_INTEREST_POINT = 4,           // 朝兴趣点方向
    UNKNOWN = -1,                        // 未知
};

enum class AltitudeType
{
    RELATIVE = 0,   // 相对高度
    ABSOLUTE,       // 绝对高度
};

enum class CoordinateType
{
    Latitude = 0,    // 纬度
    Longitude,       // 经度
    Altitude,        // 高度

    TypeNum,
};

enum class RectangleParamType
{
    Length = 0,
    Width,

    TypeNum,
};

enum class GeoFenceAreaShape
{
    Unknown = -1,
    Circle = 0,          // 圆形
    Polygon = 1,         // 多边形
    ForcedLanding = 2,   // 迫降点
};

enum class GeoFenceAreaType
{
    Unknown = -1,
    GeoFence = 0,     // 电子围栏
    NoFly = 1,        // 禁飞区，临时禁飞区
    ForceFly = 2,     // 强制可飞区(授权区)
};

enum class DataState
{
    LocalData = 0,    // 本地数据（未上传过服务器）
    Unchange = 1,     // 未更新，不需要操作
    Changed = 2,      // 数据发生更新
    Deleted = 3,      // 数据已被删除
};

enum class CameraActionType
{
    TakePhoto = 1,           // 航线动作-拍照
    Record = 2,              // 航线动作-录像
    TimeLapse = 3,           // 航线动作-定时拍
    Distance = 4,            // 航线动作-定距拍照
    DistanceScan = 5,        // 航线动作-定距扫拍
    StopRecord = 6,          // 航线动作-结束录像
    StopPhoto = 7,           // 航线动作-停止拍照
    None = 10,               // 航线动作-无
    PointTakePhoto = 11,     // 航点动作-拍照
    PointRecord = 12,        // 航点动作-录像
    PointTimeLapse = 13,     // 航点动作-定时拍照, 2022年5月10日 更改value 3 -> 13 ,区分航点动作,航线动作
    PointNone = 14,          // 航点动作-无   
    Unknown = -1,
};

enum class MissionType
{
    WAYPOINT = 0,                       // 航点任务
    RECTANGLE = 1,                      // 矩形任务
    POLYGON = 2,                        // 多边形任务
    OBLIQUE_PHOTOGRAPHY = 3,            // 倾斜摄影
    TASK_RECORD = 4,                    // 测绘任务，任务录制
    BELT_FLIGHT = 5,                    // 航带飞行
    POLYGON_GROUND = 6,                 // 多边形仿地
    SINGLE_SURROUND = 7,                // 单体环绕
    HOME_POINT = 8,                     // 自定义home点
    UNKNOWN = -1,
};

enum class ObstacleAvoidanceType
{
    INVALID = 0,        // 无效模式
    HOVER = 1,          // 遇到障碍物悬停
    LEFT_RIGHT = 2,     // 遇到障碍物左右避让，避让失败时悬停（如果装置有顶部避障系统则尝试爬升避障，再次失败时悬停）
    CLIMB = 3,          // 遇到障碍物爬升避让，避让失败时尝试左右避让，再次失败时悬停
    UNKNOWN = -1,
};

enum class MissionFinishActionType
{
    Unknown = -1,
    GoHome = 0,     // 返航 
    Hover = 1,      // 悬停
    Land = 2,       // 降落
    Last = 3,       // 停在最一个航点位置
};

enum class MissionLostConnectActionType
{
    UNKNOWN = -1,
    INVALID = 0,             // 返航 
    RETURN_HOME = 1,         // 悬停
    GO_ON_MISSION = 2,       // 降落    
};

enum class SpaceDistanceType
{
    VerticalDistance = 0,
    HorizontalDistance = 1,

    TypeNum,
};

constexpr int RECT_PARAM_TYPE_NUM = static_cast<int>(RectangleParamType::TypeNum);
constexpr int COORDINATE_TYPE_NUM = static_cast<int>(CoordinateType::TypeNum);
constexpr int SPACE_DIST_TYPE_NUM = static_cast<int>(SpaceDistanceType::TypeNum);
constexpr double PI = 3.141592653589793;

constexpr double DOUBLE_NAN = std::numeric_limits<double>::quiet_NaN();
constexpr float FLOAT_NAN = std::numeric_limits<float>::quiet_NaN();

} // namespace AutelMobileSdk


#endif  // REMOTE_CONTROLLER_RDEVICE_H
