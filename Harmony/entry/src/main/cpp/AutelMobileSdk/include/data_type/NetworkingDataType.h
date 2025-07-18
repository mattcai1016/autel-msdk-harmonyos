#ifndef NETWORKING_DATA_TYPE_H
#define NETWORKING_DATA_TYPE_H

#include <vector>
#include <string>
#include <list>
#include <cstdint>
#include "KeyValueBaseType.h"
#include "Common.h"

namespace AutelMobileSdk
{
enum class DeviceNetNodeType
{
    NET_WORK_NODE_LEAF,
    NET_WORK_NODE_CENTER
};

enum class DeviceAircraftNodeType
{
    AIRCRAFT_NODE_NOT_CONTROL,
    AIRCRAFT_NODE_CONTROL,
};

enum class DeviceProductType
{
    DEVICE_PRODUCT_INVALID,
    DEVICE_PRODUCT_AIRCRAFT,
    DEVICE_PRODUCT_RC,
};
//组网配对状态
enum class DeviceNetworkStatusType
{
    UNKNOW = 0,
    STARTED,//已开始
    SUCCESSED,//已完成
    TIMEOUT,//组网配对超时
    DISMISS,//解散（主遥控解散组网）
    OUT_GROUP,//不在组网内（主遥控剔除其他设备，或从遥控主动退出组网）
};

enum class JoystickControlMode
{
    UNKNOW = -1,
    SINGLE_CONTROL = 0,        // 单控
    MULTI_CONTROL = 1          // 多控
};

// 组网飞机类别
enum class DroneType
{
    ALL = 0,
    ONLINE,     // 在线飞机
    OFFLINE,    // 离线飞机
    ACTIVE,     // 可打杆飞机
    WATCHING,   // 码流播放飞机
    CONTROLLED, // 受控飞机
};

enum class DeviceChangeType
{
    UNKNOW = 0,                // 未知
    ALL_DEVICE = 1,            // 所有对频列表
    ONLINE_DEVICES = 2,        // 飞行任务管理
    IN_MESH = 3,               // 在网
    OUT_MESH = 4,              // 不在网
    DISMISS = 5,               // 解散
    CONTROL_MODE = 6           // 控制模式
};

enum class CPLogOperType
{
    CLOSE_LOG,
    OPEN_LOG,
    CLEAR_LOG,
};

struct AUTELSDK_API DeviceNetworkInfo
{
    int64_t groupId = 0; // 组网ID,由客户端生成，唯一规则：主体规则为毫秒时间戳
    std::string groupName; // 组网名称.

    std::string ToString() const;
};

struct AUTELSDK_API CreateDeviceNetworkReq
{
    int timeout = 300; //组网配对超时时长（秒），需要大于0
    int isContinue = 0; //0初次创建非续时 1非初次创建需续时
    DeviceNetworkInfo info;
    int maxDroneNum = 16; //设定组网支持最大飞机数量
    int maxRcNum = 4; //设定组网支持最大遥控器数量

    std::string ToString() const;
};

struct AUTELSDK_API CreateDeviceNetworkResp
{
    int result = 0;
    DeviceNetworkInfo info;

    std::string ToString() const;
};

struct AUTELSDK_API JoinDeviceNetworkReq
{
    int64_t groupId = 0;
    int inviteCode = 0;

    std::string ToString() const;
};

struct AUTELSDK_API EditDeviceNameReq
{
    uint32_t deviceId = 0;
    std::string deviceName;

    std::string ToString() const;
};

struct AUTELSDK_API SwitchDroneDeviceBean
{
    JoystickControlMode mode = JoystickControlMode::SINGLE_CONTROL;
    std::vector<uint32_t> deviceList;

    std::string ToString() const;
};

struct AUTELSDK_API CameraStreamInfo
{
    std::string deviceID;
    int gimbalID = 0;
    int cameraID = 0;

    std::string ToString() const;
};

struct AUTELSDK_API CPLogSettingBean
{
    CPLogOperType operType = CPLogOperType::OPEN_LOG;
    std::vector<uint32_t> deviceList;

    std::string ToString() const;
};

struct AUTELSDK_API ReportDroneGpsBean
{
    std::string uavId;
    double latitude = 0;
    double longitude = 0;
    float height = 0;
    float distance = 0;
    DroneFlightMode mode = DroneFlightMode::Unknown;

    std::string ToString() const;
};
//设备信息
struct AUTELSDK_API DeviceInfoBean
{
    uint32_t deviceId = 0;
    std::string deviceIdStr;
    std::string ipAddress;
    DeviceNetNodeType networkNodeType = DeviceNetNodeType::NET_WORK_NODE_CENTER;
    DeviceAircraftNodeType bizNodeType = DeviceAircraftNodeType::AIRCRAFT_NODE_NOT_CONTROL;
    DeviceProductType deviceType = DeviceProductType::DEVICE_PRODUCT_INVALID;
    int bLocal = 0;
    int activeAircraft = 0;
    int deviceNodeId = 0;
    int bOnline = 0;
    std::string deviceName;
    int deviceImgIndex = 0;
    int64_t groupID = 0;
    int bWatched = 0;
    int bLeader = 0;

    std::string ToString() const;

    // 当前设备是否为本地遥控器（手上拿的这个遥控器）
    bool IsLocalRc() const
    {
        return (bLocal == 1 && deviceType == DeviceProductType::DEVICE_PRODUCT_RC);
    }

    // 是否为主遥控
    bool IsMainRc() const
    {
        return (bizNodeType == DeviceAircraftNodeType::AIRCRAFT_NODE_CONTROL);
    }

    bool IsLocalMainRc() const
    {
        return (IsLocalRc() && IsMainRc());
    }

    // 是否是中继飞机
    bool IsCenterDrone() const
    {
        return (networkNodeType == DeviceNetNodeType::NET_WORK_NODE_CENTER && IsDrone());
    }

    // 是否为飞机
    bool IsDrone() const
    {
        return (deviceType == DeviceProductType::DEVICE_PRODUCT_AIRCRAFT);
    }

    // 是否为遥控器
    bool IsRC() const
    {
        return (deviceType == DeviceProductType::DEVICE_PRODUCT_RC);
    }

    // 是否为可打杆飞机
    bool IsActiveAircraft() const
    {
        return (IsDrone() && activeAircraft == 1);
    }

    // 当前飞机码流是否推到遥控器,遥控器也会被watch，需要特别注意
    bool IsWatchedAircraft() const
    {
        return (IsDrone() && bWatched == 1);
    }

    //是否长机
    bool IsLeader() const
    {
        return bLeader == 1;
    }

    //是否在线
    bool IsOnline() const
    {
        return bOnline == 1;
    }

    //重载==
    bool operator ==(const DeviceInfoBean& other) const
    {
        return deviceId == other.deviceId
               && deviceIdStr == other.deviceIdStr
               && deviceName == other.deviceName
               && deviceType == other.deviceType
               && deviceImgIndex == other.deviceImgIndex
               && ipAddress == other.ipAddress
               && networkNodeType == other.networkNodeType
               && bizNodeType == other.bizNodeType
               && bLocal == other.bLocal
               && activeAircraft == other.activeAircraft
               && deviceNodeId == other.deviceNodeId
               && bOnline == other.bOnline
               && groupID == other.groupID
               && bWatched == other.bWatched
               && bLeader == other.bLeader;
    }
};
//组网配对状态上报
struct AUTELSDK_API DeviceNetworkBeanStatus
{
    DeviceInfoBean device;//配对的设备信息
    DeviceNetworkStatusType status;//组网配对状态

    //重载==
    bool operator ==(const DeviceNetworkBeanStatus& other) const
    {
        return device == other.device
               && status == other.status;
    }

    std::string ToString() const;
};

struct AUTELSDK_API DeviceNetworkCenterNodeStatus
{
    DeviceInfoBean device;

    std::string ToString() const;
};

struct AUTELSDK_API DeviceNetworkingReportItem
{
    std::string deviceIdStr;
    std::string deviceName;
    int deviceType = 0;
    int networkNodeType = 0;
    uint32_t deviceId = 0;
    int deviceNodeId;

    std::string ToString() const;
};

struct AUTELSDK_API DeviceNetworkingBean
{
    int totalCnt = 0;
    int index = 0;
    int uploadCnt = 0;
    std::vector<DeviceNetworkingReportItem> dataList;

    std::string ToString() const;
};

struct AUTELSDK_API ControlDronesBean
{
    JoystickControlMode controlMode = JoystickControlMode::SINGLE_CONTROL;
    std::vector<uint32_t> deviceIdList;

    std::string ToString() const;
};

struct AUTELSDK_API DeviceListErrorUitl
{
    int size = 0;
    bool isError = false;

    std::string ToString() const;
};

//群组
struct AUTELSDK_API GroupInfoBean
{
    int id;
    std::string name;
    int active; //群组受控状态
    std::vector<int> deviceNodeIds; //设备ID数组

    std::string ToString() const;
};

// watched 设备选择信息
struct AUTELSDK_API SelectedDeviceInfo
{
    std::vector<int32_t> deviceId;    // 选中的设备（飞机）ID list
    int32_t     closeFlowFlag = 0;   // 是否关闭图传流标记，0:不关闭，1:关闭
    std::string ToString() const;
};

}

#endif
