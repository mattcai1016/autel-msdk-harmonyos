#ifndef ISWARM_MANAGER_H
#define ISWARM_MANAGER_H

#include <memory>

#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "SwarmKeyDataType.h"
#include "IControllCompletionListener.h"

namespace AutelMobileSdk
{

/**
 * @brief 蜂群组网业务 - 长机模式
 */
class AUTELSDK_API ISwarmManager
{
public:
    ISwarmManager(){}
    virtual ~ISwarmManager(){}

public:

    /**
     * @brief 蜂群任务坐标信息
     */
    struct Coord
    {
        int latitude; //纬度 浮点型的纬度乘以 1e7
        int longitude; //经度 浮点型的纬度乘以 1e7
        int altitude; //海拔高度 (单位是毫米)
    };

    /**
     * @brief 蜂群任务区域搜索信息
     */
    struct Area
    {
        int type; //区域类型  0:2D平面（支持）  1:3D立面(弃用)   2:树林
        int alt; //如果区域是3D立面，由这个字段表示立面高度，非3D高度忽略该字段，单位：mm
        int times; //遍历次数
        int overlapRate;  //重叠率
        int speed; //航线速度单位: cm/s
        std::vector<Coord> pointList; //组成区域的点列表
    };

    /**
     * @brief 搜索任务参数
     */
    struct SearchTaskParam
    {
        int uavId; //长机节点id
        int type;  //类型  0:发送任务参数给长机   1:长机/地面指控系统发送任务参数给各任务飞机
        int altType;  //高度类型  0:相对高度   1:海拔高度
        int targetAction;  //发现目标的动作   0:继续搜索任务   1:悬停并自动锁定目标
        int finishAction;  //任务完成的动作  0:返航   1:悬停
        int lostAction;  //失联动作  0:返航  1:继续任务  2:悬停
        std::vector<Area> areaList;  //搜索区域的区域列表

        int buildingExtranctionThresh = 10*1e3; // 建筑物提取高度阈值 * e3
        int buildingCnt = 1;               // 区域内建筑物数量
        uint32_t surroundSpeed; //立面环绕速度 (mm/s) (A1默认3m/s)
        bool needWellSearch;

        bool enableTargetReachingNear;  //是否需要抵近
        uint32_t loopSearch;    //是否需要循环搜索：0-关闭，1-开启
        uint32_t moveTargetSearchMode;  //移动目标搜索模式
        uint32_t moveTargetType; // 动目标类型 0:人 1:车 2:人或车 3:先车后人
    };

    /**
     * @brief AI检测目标类型
     */
    enum class TargetType
    {
        TARGET_TYPE_UNKNOWN = 0, //未知
        TARGET_TYPE_BOAT              = 2,  // 船         支持可见光、红外
        TARGET_TYPE_CAR               = 3,   // 小车       支持可见光、红外
        TARGET_TYPE_PERSON            = 4,   // 行人       支持红外
        TARGET_TYPE_VEHICLE           = 6,   // 大车       支持可见光、红外
        TARGET_TYPE_CIVILIAN          = 30,  // 平民       支持可见光
        TARGET_TYPE_SOLDIER           = 31,  // 士兵       支持可见光
        TARGET_TYPE_ARMORED_VEHICLE   = 32,  // 装甲车     支持可见光、红外
        TARGET_TYPE_EQUIPMENT         = 33,  // 设备物资   支持可见光、红外
        TARGET_TYPE_AERIAL_VEHICLE    = 34,  // 飞行器     支持可见光、红外
        TARGET_TYPE_SMOKE             = 35,  // 烟雾       支持可见光
        TARGET_TYPE_FIRE              = 36,  // 火         支持可见光、红外
    };

    /**
     * @brief 识别跟踪框图信息
     */
    struct TraceFrame
    {
        float startX;  // 目标的像素坐标x
        float startY;  // 目标的像素坐标y
        float width;  // 目标框宽度
        float height;  // 目标框的高度
        uint32_t  object_id;  // 目标ID
    };

    /**
     * @brief AI识别跟踪对象信息
     */
    struct AITraceTarget
    {
        uint64_t timestamp;  //时间戳
        uint32_t frameId;  //id
        uint32_t resolutionWidth;  //分辨率宽度
        uint32_t resolutionHeight;  //分辨率高度
        std::vector<TraceFrame> infoList;  //跟踪框数组
    };




    /**
     * @brief AI识别目标监听器
     */
    class UavAIDetectListener
    {
    public:
        virtual ~UavAIDetectListener(){}

        //AI识别的目标，可用于打击操作
        virtual void OnAIDetectTarget(const AITarget& target) = 0;

        //AI识别跟踪对象, 用于图传上界面画框
        virtual void OnAITraceTarget(const AITraceTarget& target) = 0;
    };

    /**
     * @brief 蜂群任务类型
     */
    enum class TaskType
    {
        TAKEOFF = 1, //1:起飞
        RALLY = 2,   //2:集结到某个点   飞行过程中会边飞边编队，如果当前已经是对应编队就直接编队飞行到指定点)
        PATROL = 3,  //3:巡航飞行到低电量后返航
        SEARCH = 4,  //4:区域搜索
        LAND = 5,    //5:返航降落
    };


    /**
     * @brief 蜂群任务请求参数
     */
    struct Request
    {
        int32_t type;  //子任务类型
            //1:起飞
            //2:集结到某个点   飞行过程中会边飞边编队，如果当前已经是对应编队就直接编队飞行到指定点)
            //3:巡航飞行到低电量后返航
            //4:区域搜索
            //5:返航降落
        int32_t id;  //子任务序号，序号越小的任务越先执行
        int32_t autoExec;  //是否自动执行该任务，0:不自动执行  1:自动执行
        int32_t action; //针对该任务执行的动作  1:设置任务   2:删除任务   3:清空当前任务列表并设置新任务
        int32_t formationType;  //编队类型  0:不编队  1:一字编队  2:C字编队  3:U字编队  4:V字编队
        std::vector<int32_t> formationParam;  //编队参数，不同编队参数个数和含义不一样，所以使用一个数组来表示
            //一字编队  参数1:相邻飞机间距，单位：m   参数2:展开方式（0-左右展开  1-前后展开）
            //C字编队   参数1:半径，单位：m
            //U字编队   参数1:圆弧部分半径，单位：m   参数2:直线部分相邻飞机间距，单位：m
            //人字编队  参数1:相邻飞机间距，单位：m   参数2:张开的角度取值0~180
        int32_t altType;  //高度类型  0:相对高度   1:海拔高度
        int32_t areaId;  //任务关联的区域id
        int32_t speed = 0;  //任务中飞机飞行速度，单位: cm/s
        std::vector<Coord> areaPointList;  //组成区域的点列表
        //下面为子任务的特有参数
        SwarmTakeOffParam takeOff;// 起飞子任务参数    - type=1 有效
        ConcentrateParam rally;   // 结集参数         - type=2 有效
        SwarmPatrolParam patrol;  // 巡航子飞行任务参数 - type=3 有效
        SwarmSearchObject search; // 区域搜索参数      - type=4 有效
        SwarmLandParam land;      // 返航降落子任务参数 - type=5 有效

        uint32_t curLeaderAlt; // 当前长机高度 50*e3 mm
    };

    /**
     * @brief 蜂群任务监听器
     */
    class SwarmListener
    {
    public:
        virtual ~SwarmListener(){}

        //AI识别的目标，可用于打击操作
        virtual void OnSwarmDetectTarget(const AITarget& target) = 0;

        //蜂群任务进度
        virtual void OnSwarmProgressUpdate(const SwarmTaskScheduleNtfy& notify) = 0;
    };

    class RequestId;
public:

    /**
    * @brief  开启伴飞模式
    *
    * @param  targetLock 目标ID   目标锁定策略：0发现目标后由地面端确认后锁定目标,1发现目标后自动锁定目标
    *         aiListener AI识别目标监听器
    *         listener 任务监听
    * @return 返回错误码
    */
    virtual ErrorCode StartAccompanyingFlight(int targetLock,
                                              std::shared_ptr<UavAIDetectListener> aiListener,
                                              std::shared_ptr<CompletionListener<void>> listener) = 0;

    /**
    * @brief  结束伴飞模式
    *
    * @param  listener 任务监听
    * @return 返回错误码
    */
    virtual ErrorCode EndAccompanyingFlight(std::shared_ptr<CompletionListener<void>> listener) = 0;

    /**
    * @brief  获取AI识别目标列表
    *
    * @return 返回AI识别目标列表
    */
    virtual std::shared_ptr<std::vector<AITarget>> GetAIDetectList() = 0;

    /**
    * @brief  锁定目标
    *
    * @param  objectId 目标ID
    *         latitude 目标纬度 浮点型的纬度乘以 1e7
    *         longitude 目标经度 浮点型的纬度乘以 1e7
    *         altitude 目标海拔高度(单位是毫米)
    *         listener 任务监听
    * @return 返回错误码
    */
    virtual ErrorCode LockObject(int objectId,
                                 int latitude,
                                 int longitude,
                                 int altitude,
                                 std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  对锁定目标进行打击
    *
    * @param  action 动作 0：取消打击   1：打击
    *         listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode AttackLockedObject(int action, std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  目标损毁评估
    *
    * @param  objectId 目标ID
    *         result 评估结果 0:没有损毁  1:已经损毁  其它:待扩展（例如：轻微损伤、重度损伤等）
    *         listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode ObjectDamageAssessment(int objectId, int result, std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  执行搜索任务
    *
    * @param  param 搜索任务参数
    *         aiListener AI识别目标监听器
    *         listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode StartSearchTask(SearchTaskParam param,
                                      std::shared_ptr<UavAIDetectListener> aiListener,
                                      std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  结束搜索任务
    *
    * @param  listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode EndSearchTask(std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  蜂群任务 - 开始蜂群任务
    *
    * @param  swarmListener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode StartSwarmTask(std::shared_ptr<SwarmListener> swarmListener) = 0;

    /**
    * @brief  蜂群任务 - 蜂群任务初始化情况任务及状态
    *
    * @param  swarmListener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode SwarmManagerInit(std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  蜂群任务 - 设置子任务
    *
    * @param  req 子任务参数
    *         listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode SetSwarmTask(Request req,
                                   std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  蜂群任务 - 结束蜂群任务
    *
    * @param  listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode EndSwarmTask(std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  蜂群任务 - 子任务控制
    *
    * @param  code 控制码 0:开始下一个任务  1:暂停当前任务   2:继续当前任务  3:开始当前任务
    *              4:开始任一任务   5:  清空任务并重置飞机至初始状态   6: 立刻强制执行返航任务
    *         subId 子任务ID, code=3有效
    *         listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode ControlSwarmTask(int code, int subId = 0, std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  蜂群任务 - 获取搜索侦察任务所发现的目标列表
    *
    * @param  listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode GetSwarmTaskTarget(std::shared_ptr<CompletionListener<SwarmUavAIDetectsInfo>> listener) = 0;

    /**
    * @brief  蜂群任务 - 设置打击任务的目标列表
    *
    * @param  targets 打击目标列表
    *         type 选择打击目标的类型 0: 静态目标, 1: 动态目标, 2: 同时选择
    *         assessmentUAV 是否启用评估
    *         listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode SetSwarmTaskHitTarget(const SwarmUavDJObjects &targetObjects,
                                            bool assessmentUAV = false,
                                            std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;

    /**
    * @brief  蜂群任务 - 打击动态任务的目标
    *
    * @param  targets 打击目标列表
    *         type 选择打击目标的类型 0: 静态目标, 1: 动态目标, 2: 同时选择
    *         assessmentUAV 是否启用评估
    *         listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode SetSwarmTaskMoveTargetHit(const SwarmUavDJObjects &targetObjects,
                                                  bool assessmentUAV = false,
                                                  std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;
    /**
    * @brief  蜂群任务 - 蜂群任务下发终止打击动作
    *
    * @param  listener 任务反馈
    * @return 返回错误码
    */
    virtual ErrorCode SwarmManagerEndAttack(std::shared_ptr<CompletionListener<void>> listener = nullptr) = 0;


    /**
     * @brief 切换摇杆模式：0-真实摇杆，1-虚拟摇杆，2-虚拟+真实
     * @param status
     */
    virtual void SwitchRockerMode(int status) = 0;

    /**
     * @brief 遥感数据
     * @param raiseOrDown
     * @param turnLeftOrRightValue
     * @param forwardOrBackwardValue
     * @param goLeftOrRightValue
     */
    virtual void UpdateVisualPoleStateData(int raiseOrDown, int turnLeftOrRightValue, int forwardOrBackwardValue, int goLeftOrRightValue) = 0;


    /**
     * @brief 硬件按钮：0-无效，1-起飞，2-返航，3-悬停
     * @param key
     */
    virtual void HardwareKey(int key) = 0;


    /**
     * @brief 切换单机或多机
     * @param switchGroupOrSingleData
     */
    virtual void SwitchGroupOrSingle(SwitchGroupOrSingleData switchGroupOrSingleData, std::shared_ptr<CompletionListener<void>> listener) = 0;


    /**
     * @brief 设置长机高度
     * @param SetLeaderAlt
     */
    virtual ErrorCode SetLeaderAlt(int32_t alt, std::shared_ptr<CompletionListener<void>> listener) = 0;


    /**
     * @brief 增加蜂群任务进度监听(进度及目标监听)
     * @param swarmListener
     */
    virtual ErrorCode AddSwarmStartListener(std::shared_ptr<SwarmListener> swarmListener,
                                            std::shared_ptr<ISwarmManager::UavAIDetectListener> aiListener) = 0;

    /**
     * @brief 删除蜂群任务进度监听
     */
    virtual ErrorCode RemoveSwarmStartListener() = 0;

    /**
     *  @brief 地面遥控心跳信息发布
     *  @param SwarmGroundCotrolStatus
     */
    virtual ErrorCode HeartbeatInfoReport(const SwarmGroundCotrolStatus &param) = 0;
    /**
     * @brief 蜂群任务打击评估结果监听
     * @param swarmListener
     */
    virtual ErrorCode AddStrikeAssessmentInfoListener(uint32_t deviceId, std::shared_ptr<KeyListener<SwarmStrikeAssessmentInfo>> & swarmListener) = 0;

    /**
     * @brief 删除蜂群任务打击评估结果监听
     */
    virtual ErrorCode RemoveStrikeAssessmentInfoListener(uint32_t deviceId) = 0;

    /**
     * @brief 动目标监听
     * @param deviceId (子机id)
     * @param AiDetectListener
     * @return ErrorCode
     */
    virtual ErrorCode AddSwarmMoveTargetListener(uint32_t deviceId, std::shared_ptr<KeyListener<SwarmUavAIDetectInfo>> AiDetectListener) = 0;

    /**
     * @brief 取消动目标监听
     * @param deviceId (子机id)
     * @return
     */
    virtual void RemoveSwarmMoveTargetListener(uint32_t deviceId) = 0;
};

/**
* @brief 蜂群任务请求ID
*/
class AUTELSDK_API ISwarmManager::RequestId {
public:
static RequestId &GetInstance() {
    static RequestId instance;
    return instance;
}
int32_t Get(){
    int32_t id = m_i32Id;
    ++m_i32Id;
    return id;
}
void Reset() {
    m_i32Id = 0;
}
private:
	RequestId() = default;
	RequestId(const RequestId &) = delete;
	RequestId & operator = (const RequestId &) = delete;
	RequestId(RequestId &&) = delete;
	RequestId & operator = (RequestId &&) = delete;
	~RequestId() = default;
private:
	int32_t m_i32Id = 0;
};

}  // namespace AutelMobileSdk

#endif
