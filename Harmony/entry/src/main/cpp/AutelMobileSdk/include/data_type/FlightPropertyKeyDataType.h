#ifndef FLIGHT_PROPERTY_KEY_DATATYPE_H
#define FLIGHT_PROPERTY_KEY_DATATYPE_H

namespace AutelMobileSdk
{
enum class OperatorModeEnum
{
    PROFESSIONAL = 0,
    NEW_HAND = 1,
    UNKNOWN = 0xff,
};

enum class DroneLostActionEnum
{
    UNKNOWN = 0,    // 未知
    BACK = 1,       // 失联返航
    HOVER = 2,      // 失联悬停
    LANDING = 3,    // 失联降落
};

enum class GearLevelEnum
{
    UNKNOWN = 0,    // 未知
    SMOOTH = 1,     // 平稳档
    NORMAL = 2,     // 普通档
    SPORT = 3,      // 运动档
};

enum class DroneGpsEnum
{
    // 以下枚举为飞控支持GPS模式，
    // 中国的北斗卫星导航系统（BDS）、
    // 美国的全球定位系统（GPS）、
    // 俄罗斯的格洛纳斯卫星导航系统（GLONASS）
    // 欧盟的伽利略卫星导航系统（GALILEO）
    UNKNOWN = 0,
    BDS = 1,
    GPS = 2,
    BDS_GPS = 3,
    BDS_GLO = 5,
    GPS_GAL = 10,
    BDS_GPS_GLO = 7,
    BDS_GPS_GAL = 11,
    GLO_GAL = 14,
    BDS_GPS_GAL_GLO = 15,
};

struct DroneGpsSwitch
{
    int enable = 0;
};

} // namespace AutelMobileSdk

#endif // FLIGHTPROPERTYKEYDATATYPE_H
