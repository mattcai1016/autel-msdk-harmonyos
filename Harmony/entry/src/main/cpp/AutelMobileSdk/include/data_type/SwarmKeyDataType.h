#ifndef SWARM_KEY_DATA_TYPE_H
#define SWARM_KEY_DATA_TYPE_H

#include <vector>
#include <list>
#include <any>
#include <cstdint>
#include <string>
#include "Common.h"

namespace AutelMobileSdk
{

/**
 * @brief 蜂群任务类型
 */
enum class SwarmTaskTypeEnum
{
    TASKOFF = 1,    //起飞
    RALLY = 2,      //集结到某个点   飞行过程中会边飞边编队，如果当前已经是对应编队就直接编队飞行到指定点)
    PATROL = 3,     //巡航飞行到低电量后返航
    SEARCH = 4,     //区域搜索
    LAND = 5,       //返航降落
};

/**
 * @brief 编队类型
 */
enum class ManualFormationTypeEnum
{
    FORMATION_TYPE_NONE = 0,  // 不编队
    FORMATION_TYPE_1 = 1,     // 一字编队
    FORMATION_TYPE_C = 2,     // C字编队
    FORMATION_TYPE_U = 3,     // U字编队
    FORMATION_TYPE_1V = 4,    // 人字编队
};

/**
 * @brief 选择的打击目标类型
 */
enum class AttackTargetType
{
    STATIC_TARGET = 0, //选择静态目标
    DYNAMIC_TARGET,    //选择动态目标
    BOTH_TARGET,       //同时选择
};

/**
 * @brief 蜂群进入长机控制模式请求参数
 */
struct AUTELSDK_API SwarmEnterLeaderCtrlModeReq
{
    int missionType; //任务类型  1: none  2: 伴飞保护
    int targetLock; //目标锁定策略   0:发现目标后由地面端确认后锁定目标   1:发现目标后自动锁定目标

    std::string ToString() const;
};

/**
 * @brief 锁定目标进行打击请求参数
 */
struct AUTELSDK_API SwarmAttackLockedObjectReq
{
    int action;  //动作  0:取消打击   1:打击
    int objectId;  //打击的目标ID

    std::string ToString() const;
};

/**
 * @brief 蜂群锁定目标请求参数
 */
struct AUTELSDK_API SwarmLockObjectReq
{
    int objectId;    //目标ID
    int latitude;     //目标纬度  浮点型的纬度乘以 1e7）
    int longitude;    //目标经度   浮点型的经度乘以 1e7）
    int altitude;     //目标海拔高度   浮点型的高度乘以 1e3）

    std::string ToString() const;
};

/**
 * @brief 目标损毁评估请求参数
 */
struct AUTELSDK_API SwarmObjectDamageAssessmentReq
{
    int objId;  //被打击目标id
    int assessmentResult;  //评估结果  0:没有损毁  1:已经损毁  其它:待扩展（例如：轻微损伤、重度损伤等）

    std::string ToString() const;
};

/**
 * @brief 区域搜索点
 */
struct AUTELSDK_API SwarmAreaSearchPoint
{
    int latitude;     //坐标点纬度  浮点型的纬度乘以 1e7）
    int longitude;    //坐标点经度   浮点型的经度乘以 1e7）
    int altitude;     //坐标点海拔高度   浮点型的高度乘以 1e3）

    //重载=
    void operator =(const SwarmAreaSearchPoint& other)
    {
        latitude = other.latitude;
        longitude = other.longitude;
        altitude = other.longitude;
    }

    std::string ToString() const;
};

/**
 * @brief 蜂群任务区域搜索
 */
struct AUTELSDK_API SwarmAreaSearchAreaInfo
{
    int areaType = 0;  //区域类型  0:2D平面(支持)  1:3D立面(已弃用)   2:树林
    int areaAlt;  //如果区域是3D立面，由这个字段表示立面高度，非3D高度忽略该字段，单位：mm
    int times;  //遍历次数
    int overlapRate;  //重叠率
    int speed;  //航线速度  speed * 1e2  单位: cm/s (平面)
    std::vector<SwarmAreaSearchPoint> areaPointList;  //组成区域的点列表

    std::string ToString() const;
};

/**
 * @brief 蜂群搜索任务参数设置
 */
struct AUTELSDK_API SwarmAreaSearchTaskParamSetReq
{
    int uavId;  //飞机节点id
    int type;  //类型  0:发送任务参数给长机   1:长机/地面指控系统发送任务参数给各任务飞机
    int altType;  //高度类型  0:相对高度   1:海拔高度
    int targetAction;  //发现目标的动作   0:继续搜索任务   1:悬停并自动锁定目标
    int finishAction;  //任务完成的动作  0:返航   1:悬停
    int rcLostAction;  //失联动作  0:返航  1:继续任务  2:悬停
    std::vector<SwarmAreaSearchAreaInfo> areaList;  //搜索区域的区域列表

    int buildingExtranctionThresh; // 建筑物提取高度阈值 * e3
    int buildingCnt;               // 区域内建筑物数量

    uint32_t surroundSpeed = 3 * 1e3; //立面环绕速度 (mm/s) (A1默认3m/s)

    bool needWellSearch;

    bool enableTargetReachingNear;  //是否需要抵近
    uint32_t loopSearch;    //是否需要循环搜索：0-关闭，1-开启
    uint32_t moveTargetSearchMode;  //移动目标搜索模式
    uint32_t moveTargetType; //动目标搜索类型 0：人 1：车 2：人或车 3: 先车后人

    std::string ToString() const;
};

/**
 * @brief AI识别目标信息
 */
struct AUTELSDK_API AITarget
{
    uint64_t timestamp;  //识别到该目标的时间戳 (UTC时间戳,单位毫秒)
    int uavId;  //发出该消息的飞机节点ID
    int id;  //目标id（机内唯一）
    int type;  //目标类型 TargetType
    int dangerLevel;  //目标的危险程度，仅适用于人，取值为1-5，危险等级从高到低

    int latitude;  //目标的纬度, 浮点型的纬度乘以 1e7
    int longitude;  //目标的经度   浮点型的经度乘以 1e7
    int altitude;  //目标的海拔高度   浮点型的高度(m)乘以 1e3

    std::string imageUrl;  //图片下载url
    int imageWidth;  //图片宽，单位：像素
    int imageHeight;  //图片高，单位：像素

    int isMoveTarget; // 是否为移动目标
    int assessmentResult; // 打击评估结果

    std::string ToString() const;
};

/**
 * @brief 蜂群AI识别结果通知
 */
struct AUTELSDK_API SwarmUavAIDetectInfo
{
    uint64_t timestamp;  //识别到该目标的时间戳
    int srcId;  //发出该消息的飞机节点ID
    int destId;  //该消息需要发往的设备节点ID， 0:发给APP  >0:其它飞机的节点ID

    int targetId;  //目标id（机内唯一）
    int targetType;  //目标类型
    int dangerLevel;  //目标的危险程度，仅适用于人，取值为1-5，危险等级从高到低
    float startX;  //目标框左上点x轴上的相对值，0~1   (1.0 * left)/width
    float startY;  //目标框左上点y轴上的相对值，0~1   (1.8 * top)/height
    float width;  //目标框宽度和图片宽的比值
    float height;  //目标框高度和图片高的比值
    int targetLat;  //目标的纬度, 浮点型的纬度乘以 1e7
    int targetLon;  //目标的经度   浮点型的经度乘以 1e7
    int targetAlt;  //目标的海拔高度   浮点型的高度(m)乘以 1e3
    int cameraZoomFactor;  //发现该目标时相机变焦倍数

    std::string imageUrl;  //图片下载url
    int imageWidth;  //图片宽，单位：像素
    int imageHeight;  //图片高，单位：像素

    std::string reidFeatrue;  //目标reid 特征，把浮点型的特征信息转成string
    int32_t isMoveTarget;     //APP用于区分目标属性| 0: 静目标 | 1: 动目标 | 2: 建筑物目标 |
    int32_t assessmentResult; // 打击评估结果

    std::string ToString() const;
};

/**
 * @brief 蜂群下各任务阶段设置请求参数
 */
struct AUTELSDK_API SwarmTaskInfoSetMsgReq
{
    int uavId;  //飞机节点id
    int taskType;  //任务类型
        //1:起飞
        //2:集结到某个点   飞行过程中会边飞边编队，如果当前已经是对应编队就直接编队飞行到指定点)
        //3:巡航飞行到低电量后返航
        //4:区域搜索(预留值，当前使用SwarmAreaSearchTaskParamSet传递区域搜索任务)
        //5:返航降落
    int taskId;  //任务序号，序号越小的任务越先执行
    int autoExec;  //是否自动执行该任务，0:不自动执行  1:自动执行
    int action;  //针对该任务执行的动作  1:设置任务   2:删除任务   3:清空当前任务列表并设置新任务
    int formationType;  //编队类型  0:不编队  1:一字编队  2:C字编队  3:U字编队  4:V字编队
    std::vector<int> formationParamList;  //编队参数，不同编队参数个数和含义不一样，所以使用一个数组来表示
        //一字编队  参数1:相邻飞机间距，单位：m   参数2:展开方式（0-左右展开  1-前后展开）
        //C字编队   参数1:半径，单位：m
        //U字编队   参数1:圆弧部分半径，单位：m   参数2:直线部分相邻飞机间距，单位：m
        //人字编队  参数1:相邻飞机间距，单位：m   参数2:张开的角度取值0~180
    int altType;  //高度类型  0:相对高度   1:海拔高度
    int areaId;  //改任务关联的区域id
    int speed;  //任务中飞机飞行速度，单位: cm/s
    std::any param; //该任务的一些其他参数
    std::vector<SwarmAreaSearchPoint> areaPointList;  //组成区域的点列表
    unsigned int guid;
    unsigned int curLeaderAlt;

    std::string ToString() const;
};

/**
 * @brief 飞机起飞任务参数
 */
struct AUTELSDK_API SwarmTakeOffParam
{
    int type;  //0:同步起飞  1:异步起飞   2:根据飞机间距自行决定起飞方式
    int hoverType;  //起飞后悬停模式，  0:以基准高度上下一定范围内错开分层悬停  1:起飞后飞机自动散开，所有飞机在基准高度悬停
    int baseHeight;  //基准高度，单位：mm
    int heightRange;  //高度范围(当悬停模式为分层悬停时，定义相对于基准高度，飞机各分布的高度范围)，单位：mm

    std::string ToString() const;
};

/**
* @brief 飞机集结参数
*/
struct AUTELSDK_API ConcentrateParam
{
    int areaType; //集结区域类型 0 - 点 1 - 多边形区域  2 - 圆形区域降落
    int radius;   //圆形区域半径 当area_type = 2时使用

    std::string ToString() const;
};

/**
 * @brief 飞机巡航飞行参数
 */
struct AUTELSDK_API SwarmPatrolParam
{
    int type;  //0:在航点处悬停  1:以航点为圆心的同心圆飞行  2:相向飞行，检验避障  3:按一系列航点循环飞行  4:若干航点形成区域，在区域内飞行
    int radius;  //如果巡航类型为同心圆飞行，需要设置圆的半径
    int horizontalSpacing;  //同心圆飞行，水平方向上间隔（m）
    int vertiacalSpacing;  //同心圆飞行，垂直方向上间隔（m）

    std::string ToString() const;
};

/**
 * @brief 飞机返航降落参数
 */
struct AUTELSDK_API SwarmLandParam
{
    int type;           //0:在当前位置直接降落  1:返回起飞点降落  2:指定降落点/区域
    int32_t landAction; //0: 执行此任务时立刻降落, 1: 暂不降落, 等待低电或指令
    int32_t areaType;   //0:点 1:多边形区域 1: 圆形区域
    int32_t radius;     // 半径(m)

    std::string ToString() const;
};

/**
 * @brief 区域搜索参数
 */
struct AUTELSDK_API SwarmSearchObject
{
    int parallelMapperCnt = 3; // 初始建图飞机数量，默认3架
    std::string ToString() const;
};

/**
 * @brief 蜂群任务动作消息请求参数
 */
struct AUTELSDK_API SwarmTaskActionMsgReq
{
    int action;  //0:开始下一个任务  1:暂停当前任务   2:继续当前任务  3:开始当前任务
                 //4:开始任一任务   5:  清空任务并重置飞机至初始状态   6: 立刻强制执行返航任务
    int taskId;  //当action为3时，指定要执行的任务序号

    std::string ToString() const;
};

/**
 * @brief 蜂群任务识别目标查询
 */
struct AUTELSDK_API SwarmUavAIDetectsInfo
{
    std::vector<SwarmUavAIDetectInfo> targetList; //检测到的目标列表

    std::string ToString() const;
};

/**
 * @brief 蜂群任务下发打击目标列表
 */
struct AUTELSDK_API SwarmUavDJObjects
{
    std::vector<SwarmUavAIDetectInfo> objectList; //打击目标id列表
    uint32_t actionType = 0;     //0: 静态目标, 1: 动态目标, 2: 同时选择
    uint32_t attackOrder = 0;    //0: 跟踪, 1: 释放 2: 确认打击
    uint32_t attackSpeed = 900;    // 打击速度cm/s

    std::string ToString() const;
};


/**
 * @brief 蜂群任务中单个飞机执行任务的进度情况
 */
struct AUTELSDK_API SwarmSingleUavProgress
{
    uint32_t uavId;     //飞机id
    uint32_t progress;  // 0~100
    uint32_t status;    //1:空闲 2:执行中 3:暂停 4:状态异常 5:完成

    std::string ToString() const;
};

/**
 * @brief 蜂群任务进度通知
 */
struct AUTELSDK_API SwarmTaskScheduleNtfy
{
    uint32_t    srcId;                  // The msg is from which device
    uint32_t    destId;                 // The msg is to which device  | 0: APP | others: UAV |
    uint32_t    totalMissionCnt;          // 总任务数
    uint32_t    currentMission;            // 已完成的任务数量 + 1 (任务类别由smart_mode_status表示)
    std::vector<SwarmSingleUavProgress> detailedProgress;       // 各个飞机详细进度百分比 0~100
    uint32_t action;   // current action

    std::string ToString() const;
};

/**
 * @brief A1项目单个飞机坐标信息
 */
struct AUTELSDK_API SwarmA1UavPosInfo
{
    int32_t uavId;  //飞机节点id
    int32_t latitude;     //坐标点纬度  浮点型的纬度乘以 1e7
    int32_t longitude;    //坐标点经度   浮点型的经度乘以 1e7
    int32_t altitude;     //坐标点海拔高度   浮点型的高度(m)乘以 1e3
    int32_t cruiseSpeed;  //飞行速度/巡航速度  实际浮点型速度(m/s)乘以 1e3
    int32_t yaw;  //飞机偏航角/机头朝向  实际浮点型弧度值乘以 1e3
    int32_t startReferenceTime;  //所有无人机起飞的参考基准时间
    int32_t offsetTime;  //当前飞机的偏移时间(相较于基准时间的偏移时间)
    int32_t hoverHeight; //悬停高度

    std::string ToString() const;
};

/**
 * @brief A1项目集群任务飞机坐标更改通知
 */
struct AUTELSDK_API SwarmA1UavPosChangeNtfy
{
    uint64_t timestamp;  //发出该消息的时间戳
    int32_t latitude;  //蜂群模式下被锁定目标的纬度(兼容老业务)  浮点型的纬度乘以 1e7）
    int32_t longitude;  //蜂群模式下被锁定目标的经度(兼容老业务)   浮点型的经度乘以 1e7）
    int32_t altitude;  //蜂群模式下被锁定目标的高度(兼容老业务)   浮点型的高度乘以 1e3）
    std::vector<SwarmA1UavPosInfo> uavPosInfo;  //各无人机要飞向的目标位置

    std::string ToString() const;
};

/**
 * @brief 遥感控制
 */
struct AUTELSDK_API NestVirtualPoleStateNtfy
{
    int leftHorizontalValue = 1024;
    int leftVerticalValue = 1024;
    int rightHorizontalValue = 1024;
    int rightVerticalValue = 1024;
    int gimbalPitch = 1024;
    int generalKey = 359;
    int combinedKey = 329;


    std::string ToString() const;
};

/**
 * @brief 摇杆模式切换
 */
struct AUTELSDK_API SwitchRockerModeData
{
    int value = 0;


    std::string ToString() const;
};

/**
 * @brief 切换单机多机数据
 */
struct AUTELSDK_API SwitchGroupOrSingleData
{
    int32_t type;
    int32_t id;
    int32_t device_id;

    std::string ToString() const;
};

struct AUTELSDK_API SwarmStrikeAssessmentInfo
{
    uint32_t srcId;                  //  DJ（发送）飞机id
    uint32_t destId;                 //  接收i2
    uint32_t targetId;               //  DJ目标ID
    std::string photo;                //  目标评估图片地址
    uint32_t assessmentResult;       //  评估结果 0:未成功击中  1:成功击中
    uint32_t targetType;             //  0:静目标 1:动目标
    std::string ToString() const;
};

struct AUTELSDK_API  SwarmGroundCotrolStatus
{
    uint32_t enduranceMode;        // 0x00-返航降落，0x01-返航不降落
    uint32_t gameMode;             // 比赛模式，0x00-测试模式，0x01-比赛模式。测试模式对应测试模式低电量参数值； 比赛模式对应比赛模式低电量参数值;
    uint32_t predefineParam1 = 0;  // 预留字段1开关量
    uint32_t predefineParam2 = 0;  // 预留字段2开关量
    uint32_t predefineParam3 = 0;  // 预留字段3开关量
    uint32_t predefineParam4 = 0;  // 预留字段4开关量
    std::string ToString() const;
};

} // namespace AutelMobileSdk
#endif
