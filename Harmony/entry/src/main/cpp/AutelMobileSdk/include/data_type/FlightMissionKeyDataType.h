#ifndef FLIGHT_MISSION_KEY_DATA_TYPE_H
#define FLIGHT_MISSION_KEY_DATA_TYPE_H

#include <string>
#include "Common.h"
#include <cstdint>

namespace AutelMobileSdk
{
enum class MissionQueryStatusEnum
{
    UNKNOWN = 0,
    NONE_EXISTENT,
    NONE_BREAKPOINT,
    HAVE_BREAKPOINT,
};
//任务当前状态
enum class MissionCurrentStateEnum
{
    UNKNOWN = 0,
    PAUSE = 1,//任务暂停
    RUN = 2,//任务执行中
    FINISH = 3,//任务执行完成
    UNUSUAL_STOP = 4,//任务异常停止
    FINISH_2,
};

//任务类型
enum class MissionTypeEnum
{
    UNKNOWN = 0,
    WAYPOINT = 1,   //航点飞行
    RECTANGLE = 2,  //矩形飞行
    POLYGON = 3,    //多边形飞行
    QBLIQUE = 4,    //倾斜摄影飞行
    RECORDING = 5,  //任务录制
    DELAYSUR = 6,   //航带飞行
    ORBIT = 7,   //单体环绕飞行
    INTEREST_POINT = 8,   //兴趣点飞行
};


//兴趣点任务类型
enum class MissionInterestPointEnum
{
    UNKNOWN = 0,
    TOWPARDS,//无人机朝向兴趣点，不动
    LOCK,//无人机锁定兴趣点，打杆保持锁定
    FLY_TO,//⻜向兴趣点位置后，朝向兴趣点
    ORBIT,//到达兴趣点位置后执行兴趣点环绕，朝向兴趣点
    CENTER //设置NED位置居中
};

// 航线的类型
enum class MissionLineTypeEnum {
    BIN = 0,    // 原有的.bin的航线任务类型
    KML = 1,    // kml航线
};

enum class MissionResultEnum
{
    FAILED = 0,
    SUCCESE = 1,
};

enum class SwarmMissionTypeEnum
{
    UNKNOWN = 0,
    FORMATION,//编队
    COLLABORATIVE_SEARCH,//协同搜索
};

//任务停止原因类型
enum class MissionStopReasonTypeEnum {
    UNKNOWN = 0,
    LOW_BATTERY = 10001,                      //低电
    EMER_BATTERY = 10002,                     //严重低电
    IN_NOFLYZONE = 10003,                     //进入禁飞区
    RC_LOSS = 10004,                          //rc失联
    MISSION_FINISH = 10005,                   //任务完成
    MAIN_CTRL_CMD  = 10006,                   //用户输入指令
    ALREADY_SAME_MISSION = 10007,             //相同的任务正在执行
    GEOFENCE_ACTION = 10008,                  //触发电子围栏
    UAV_ON_GROUND = 10009,                    //飞机未起飞
    PAUSE_BUTTON = 10010,                     //暂停按钮
    HOME_RETURN_BUTTON = 10011,               //返航按钮
    TIME_NOT_SYNC = 10012,                    //时间未同步
    INTEL_LOW_BATTERY = 10013,                //智能低电
    FCS_ATTITUDE = 10014,                     //飞控姿态模式
    PLANNER_OVERTIME = 10015,                 //planner的心跳超时
    MISSION_ERROR = 10016,                    //任务中间出错
    NET_LOSS = 10017,                         //4G断联
    RTK_FLOAT = 10018,                        //rtk 浮点解
    VISION_POINTCLOUD = 10019,                //视觉点云异常
    AIR_REPLACEMENT_RETURN = 10020,           //空中替换任务替换机靠近时返航
    MISSION_DIS_FAR_AWAY = 10021,             //航线距离太远
    MISSION_PLANNER_STUCK = 10022,            //航线卡住
    LAND_FAILED = 10023,                      //下降失败
    MISSION_MANAGER_CRUSH_RESTART = 10024,    //mm挂死重启返航
    MISSION_ACTION_GIMBAL_ILLEGAL = 10025,    //航线任务角度非法
    MISSION_POINTS_IN_NOFLY = 10026,          //整个航线有穿过禁飞区
    MISSION_OUTSIDE_LIMITED = 10027,          //单航点超出起飞点很远
    EXIT_MISSION_NO_ODOM = 10028,             //启动时没有飞控位置
    EXIT_MISSION_NO_GPS = 10029,              //启动时没有gps,或者转换出错
    MISSION_DIS_TOO_LONG = 10030,             //航线总路程太远
    MISSION_START_FAIL_RTK_FLOAT = 10031,     //启动是rtk浮点
    MISSION_NO_FILE = 10032,                  //没有对应的航线任务文件,或者读取文件出错
    MISSION_CMD_NO_ID = 10033,                //开始指令非法，没有带id
    FCS_NOT_TAKEOFF =10034,                   //飞控没有起飞
};

struct AUTELSDK_API WaypointMissionInfo
{
    int guid = 0;
    int startTime = 0;
    int offsetTime = 0;

    std::string ToString() const;
};

struct AUTELSDK_API WaypointMissionBreakRspBean
{
    int missionId = 0;
    int executeIndex = 0;
    int missionType = 0;
    int lat = 0;
    int lon = 0;
    int alt = 0;
    MissionQueryStatusEnum status = MissionQueryStatusEnum::HAVE_BREAKPOINT;
    MissionCurrentStateEnum executeStatus = MissionCurrentStateEnum::FINISH;

    std::string ToString() const;
};

struct AUTELSDK_API WaypointMissionStatusReportNtfyBean
{
    uint64_t timestamp = 0;// 系统时间戳, uint: ms
    int missionId = 0;// 任务ID
    int wqSeq = 0;// 航点序号
    int remainDistance = 0;// 剩余距离
    MissionTypeEnum missionType = MissionTypeEnum::DELAYSUR;
    int photoNum = 0;// 当前拍照张数
    int remainTime = 0;// 剩余时间, uint:s
    MissionCurrentStateEnum status = MissionCurrentStateEnum::FINISH;// 当前任务状态
    int guid = 0;// 任务guid
    int actionSeq = 0;// 当前动作序号
    int arrived = 0;// 航点抵达状态, 0 - arrived, 1 - Not arrived
    int speedSet = 0;// 任务设置速度, Uint: 10E-3 m/s
    int percent = 0;// 任务进度百分比
    uint32_t missionLineType = 0;// 航线的类型见MissionLineTypeEnum
    uint32_t stopReason = 0;// 停止的原因见MissionStopReasonTypeEnum

    //重载==
    bool operator ==(const WaypointMissionStatusReportNtfyBean& other) const
    {
        return timestamp == other.timestamp
               && missionId == other.missionId
               && wqSeq == other.wqSeq
               && remainDistance == other.remainDistance
               && missionType == other.missionType
               && photoNum == other.photoNum
               && remainTime == other.remainTime
               && status == other.status
               && guid == other.guid
               && actionSeq == other.actionSeq
               && arrived == other.arrived
               && speedSet == other.speedSet
               && percent == other.percent
               && missionLineType == other.missionLineType
               && stopReason == other.stopReason;
    }

    std::string ToString() const;
};

struct AUTELSDK_API InterestingPointMissionInfo
{
    int latitude = 0;
    int longitude = 0;
    int altitude = 0;
    MissionInterestPointEnum missionType = MissionInterestPointEnum::CENTER;
    int speed = 0;
    int radius = 0;
    int reqId = 0;

    std::string ToString() const;
};

struct AUTELSDK_API InterestPointMissionStatusReportNtfyBean
{
    int64_t timestamp = 0;//系统时间戳; uint: ms
    int missionId = 0;//任务ID
    int remainDistance = 0;//剩余距离mm
    int remainTime = 0; //剩余时间s
    MissionInterestPointEnum missionType = MissionInterestPointEnum::CENTER;
    int percent = 0;//任务进度百分比
    MissionCurrentStateEnum status = MissionCurrentStateEnum::FINISH;//当前任务状态

    //重载==
    bool operator ==(const InterestPointMissionStatusReportNtfyBean& other) const
    {
        return timestamp == other.timestamp
               && missionId == other.missionId
               && remainDistance == other.remainDistance
               && missionType == other.missionType
               && percent == other.percent
               && status == other.status;
    }

    std::string ToString() const;
};
//兴趣点图传打点结果通知
struct AUTELSDK_API InterestPointMissionInfoNtfyBean
{
    int req_id = 0;//请求id，和用户打点时传入的请求id保持一致
    MissionResultEnum status = MissionResultEnum::SUCCESE;//打点结果   0:失败   1:成功    当结果为成功时，会携带点的gps坐标
    double latitude = 0; //目标纬度
    double longitude = 0;//目标经度
    double altitude = 0;//目标相对高度(mm)或NED坐标z

    //重载==
    bool operator ==(const InterestPointMissionInfoNtfyBean& other) const
    {
        return req_id == other.req_id
               && status == other.status
               && latitude == other.latitude
               && latitude == other.latitude
               && longitude == other.longitude
               && altitude == other.altitude;
    }


    std::string ToString() const;
};

struct AUTELSDK_API InterestingPoint
{
    float startX = 0;
    float startY = 0;
    float width = 0;
    float height = 0;

    std::string ToString() const;
};

struct AUTELSDK_API InterestPointMissionCreatePointRspBean
{
    int latitude = 0;
    int longitude = 0;
    int altitude = 0;

    std::string ToString() const;
};

struct AUTELSDK_API SwarmMissionInfo
{
    int missionId = 0;
    int startTime = 0;

    std::string ToString() const;
};

struct AUTELSDK_API SwarmMissionStatusNtfyBean
{
    int missionId = 0;//当前任务的mission_id号
    int taskPointIndex = 0;//当前执行任务的航点序号
    MissionCurrentStateEnum status = MissionCurrentStateEnum::FINISH;//当前执行的状态 0:unknown ,1:任务暂停，2：任务执行中，3：任务完成，4：任务异常停止
    SwarmMissionTypeEnum runTaskType = SwarmMissionTypeEnum::COLLABORATIVE_SEARCH;//当前执行的任务类型，0:unknown，1：编队，2：协同搜索
    int taskStageIndex = 0;//当前的任务阶段

    //重载==
    bool operator ==(const SwarmMissionStatusNtfyBean& other) const
    {
        return missionId == other.missionId
               && taskPointIndex == other.taskPointIndex
               && status == other.status
               && runTaskType == other.runTaskType
               && taskStageIndex == other.taskStageIndex;
    }

    std::string ToString() const;
};
//蜂群任务文件上传状态反馈
struct AUTELSDK_API SwarmMissionUploadFileNtfyBean
{
    int missionId = 0;//收到的文件id号
    int fileTyp = 0;//收到的文件类型
    int resultCode = 0;//收到的文件结果 0：nuknown 1:success, 2:failure

    //重载==
    bool operator ==(const SwarmMissionUploadFileNtfyBean& other) const
    {
        return missionId == other.missionId
               && fileTyp == other.fileTyp
               && resultCode == other.resultCode;
    }

    std::string ToString() const;
};

struct AUTELSDK_API FileInfo
{
    int fileType = 0;
    std::string fileName = "";

    std::string ToString() const;
};

struct AUTELSDK_API MissionFastNightSlamParam {
    int lat = 0;  //集结点 纬度 * 1e7
    int lon = 0;  //集结点 经度 * 1e7
    int alt = 0;  //集结点 相对高度 * 1e3
    //重载==
    bool operator ==(const MissionFastNightSlamParam& other) const
    {
        return lat == other.lat
               && lon == other.lon
               && alt == other.alt;
    }
    std::string ToString() const;
};


struct AUTELSDK_API DroneMissionFastNightSlamParam{
    MissionFastNightSlamParam stParam;
    uint32_t u32Device; // droneid

    //重载==
    bool operator ==(const DroneMissionFastNightSlamParam& other) const
    {
        return u32Device == other.u32Device
               && stParam == other.stParam;
    }
    std::string ToString() const;
};


struct AUTELSDK_API MissionKmlGuid {
    int32_t kmlMissionId;        //全局唯一任务id
    int32_t startTime;            //任务开始基准时间
    std::string mediaAddress;     //媒体文件地址
    int32_t rtkEnable;            //是否使用rtk 0-不使用 1-使用

    std::string ToString() const;
};

} // namespace AutelMobileSdk

#endif
