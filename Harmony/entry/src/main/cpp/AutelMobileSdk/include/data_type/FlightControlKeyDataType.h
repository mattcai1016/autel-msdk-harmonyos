#ifndef FLIGHT_CONTROL_KEY_DATA_TYPE_H
#define FLIGHT_CONTROL_KEY_DATA_TYPE_H

#include <string>
#include "KeyValueBaseType.h"
#include "FlightPropertyKeyDataType.h"
#include "Common.h"

namespace AutelMobileSdk
{
enum class LevelEnum
{
    UNKNOWN = 0,
    SMOOTH = 1,
    NORMAL = 2,
    SPORT = 3,
};

enum class LocationTypeEnum
{
    UNKNOWN = 0,
    TAKE_OFF = 1,
    RC = 2,
    DRONE_CURRENT = 3,
    DIVERSION_POINT = 4,
};

enum class AutoBackType
{
    HOMEPOINT = 0,               // home点
    ALTERNATE_LANDING_POINT = 1, // AI识别  备降点
};

enum class DroneGpsMode
{
    GPS_MODE_UNKNOWN = 0,
    GPS_MODE_BDS = 1,
    GPS_MODE_GPS = 2,
    GPS_MODE_BDS_GPS = 3,
    GPS_MODE_BDS_GLO = 5,
    GPS_MODE_GPS_GAL = 10,
    GPS_MODE_BDS_GPS_GLO = 7,
    GPS_MODE_BDS_GPS_GAL = 11,
    GPS_MODE_GPS_GLO_GAL = 14,
    GPS_MODE_BDS_GPS_GAL_GLO = 15
};

// 获取飞控参数集合
struct AUTELSDK_API DroneFlightParam
{
    bool supportRTK = true;
    bool beginMode = true;//是否新手模式
    GearLevel gearLevel = GearLevel::UNKNOWN;
    DroneLostActionEnum lostAction = DroneLostActionEnum::UNKNOWN;
    float maxHeight = 0; // 最大高度
    float maxRange = 0; //最远距离
    float backHeight = 0; //返航高度
    int batLowWarningValue = 0; // 低电量告警
    int batSeriousWarningValue = 0; // 严重低电量告警
    bool attiAllowFly = true; // 是否运行起飞
    bool magErrorAllowFly = true; //磁力计异常是否运行起飞

    std::string ToString() const;
};

struct AUTELSDK_API NoFlyQzone
{
    std::string countryCode;
    std::string fileMd5;

    std::string ToString() const;
};

struct AUTELSDK_API NestWait
{
    int waitTime = 0;

    std::string ToString() const;
};

struct AUTELSDK_API SetHomeLocation
{
    int64_t latitude = 0;
    int64_t longitude = 0;
    int64_t height = 0;
    LocationTypeEnum type;

    std::string ToString() const;
};

struct AUTELSDK_API DroneFlyToPoint
{
    int32_t latitude = 0; //目标点 纬度 * 1e7
    int32_t longitude = 0; //目标点 经度 * 1e7
    int32_t altitude = 0; //目标点 海拔高度 * 1e3
    int32_t flyAltitude = 0; //飞行高度（相对高度） * 1e3
    int32_t maxSpeed = 10; //飞行过程中能达到的最大速度(m/s)
    bool lockPoint = false; //0:云台不锁定目标点，1:云台锁定目标点

    std::string ToString() const;
};

struct AUTELSDK_API DroneAutoBack
{
    int32_t autoBack = 0;
    int32_t autoBackType = 0;

    std::string ToString() const;
};

struct AUTELSDK_API GimbalAngleSpeed {
    float pitchSpeed = 0.0f;   //俯仰角速度
    float rollSpeed = 0.0f;    //横滚角速度
    float yawSpeed = 0.0f;     //偏航角速度
    uint64_t timeStamp = 0;  //时间戳

    std::string ToString() const;
};

} // namespace AutelMobileSdk

#endif
