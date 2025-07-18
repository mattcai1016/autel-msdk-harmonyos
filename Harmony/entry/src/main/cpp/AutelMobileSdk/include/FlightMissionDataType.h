
#ifndef FLIGHT_MISSION_DATA_TYPE_H
#define FLIGHT_MISSION_DATA_TYPE_H

#include <string>
#include <list>
#include <vector>
#include <math.h>
#include "FlightMissionBaseType.h"

namespace AutelMobileSdk
{

struct Coordinate3D
{
    double latitude = 0;
    double longitude = 0;
    double altitude = 0;

    std::string ToString() const;
};

struct GeoFenceModel
{
    long id = 0;
    std::string userId;
    std::string name;
    std::string areaColor;
    GeoFenceAreaType areaType = GeoFenceAreaType::Unknown;
    GeoFenceAreaShape areaShape = GeoFenceAreaShape::Unknown;
    int areaLevel = 0;                           // 地图层级（暂时未用到 预留）
    int polygonNum = 0;                          // 多边形顶点数量（多边形属性）
    double latitude = 0;                         // 中心点维度（圆形属性）
    double longitude = 0;                        // 中心点经度（圆形属性）
    float radius = 0;                            // 半径（圆形属性）
    float height = 0;                            // 高度
    bool isHeightValid = 0;                      // 高度是否有效（如果无效，表示height无限大）
    std::vector<Coordinate3D> latLngs;           // 多边形顶点列表（多边形属性）
    long effectiveTimeStart = 0;                 // 有效时间的起始时间（UTC时间）
    long effectiveTimeEnd = 0;                   // 有效时间的结束时间（UTC时间）
    long createTime = 0;                         // 数据生成的时间（UTC时间）
    long latestUpdateTime = 0;                   // 最后一次更新的时间（UTC时间）
    std::string uuid;                            // 唯一标识
    DataState updateStatus = DataState::LocalData; // 数据状态，用于告知服务器数据状态: 0:本地数据（未上传过服务器）;1：未更新，不需要操作。2：数据发生更新；3：数据已被删除。

    std::string ToString() const;
};

struct AutelLatLng
{
    inline static const float MIN_LATITUDE = -90;
    inline static const float MAX_LATITUDE = 90;
    inline static const float MIN_LONGITUDE = -180;
    inline static const float MAX_LONGTITUDE = 180;

    double latitude = 0;
    double longitude = 0;
    double altitude = 0;

    AutelLatLng(double latitude, double longitude, double altitude = 0);

    bool operator==(const AutelLatLng& other) const;

    bool IsLatitudeValid() const;
    bool IsLongitudeValid() const;
    bool IsNonZero() const;
    static bool IsLegalityValid(double latitude, double longitude);

    std::string ToString() const;
};

struct DirectionLatLng
{
    double latitude = 0;       // 纬度
    double longitude = 0;      // 经度
    double degree = 0;         // 航向（弧度）：与正东方向的夹角

    bool operator==(const DirectionLatLng& other) const;

    std::string ToString() const;
};

struct AuthArea
{
    std::string uniqId;
    std::string name;
    float longitude = 0;
    float latitude = 0;
    float radius = 0;
    float height = 0;
    int beginAt = 0;
    int endAt = 0;

    std::string ToString() const;
};

struct NoFlyArea
{
    std::string color;
    int height = 0;
    int level = 0;
    double latitude = 0;
    double longitude = 0;
    int radius = 0;
    int shape = 0;
    std::list<std::vector<double>> polygonPoints;

    std::string ToString() const;
};

struct NoFlyAreaBase
{
    std::list<NoFlyArea> areas;

    std::string ToString() const;
};

struct CameraAction
{
    int actionType = 0;                // 动作类型
    float gimbalPitch = 0;             // 云台Pitch角
    float gimbalRoll = 0;              // 云台Roll角
    float actionYawRef = 0;            // 偏航角度
    int shootTimeInterval = 0;         // 定时拍照间隔(s)
    float shootDisInterval = 0;        // 定距拍照距离间隔(mm)
    int actionTime = 0;                // 动作执行时长(s) 
    int zoomRate = 0;                  // 变焦倍数 
    uint32_t reserved[2] = { 0 };               // 预留 

    std::string ToString() const;
};

struct MissionConfig
{
    int id = 0;            // 任务id,由调用方自行定义，任务续飞会根据此信息来
    int altitudeType = 0;  // 相对高度or海拔高度(m) 1海拔高，2相对高
    int type = 0;          // 任务类型 0航点， 1矩形， 2多边形， 3倾斜， 4任务录制，5航带，6多边形仿地，7单体环绕
    int finishAction = 0;  // 任务完成后执行动作
    int lossAction = 0;    // 图传断联后执行动作
    int obstacleMode = 0;  // 避障模式
    int sideObstacle = 0;  // 侧向避障:0:关；1：开
    bool doubleGrid = true;   // 是否开启双网格
    bool altOptim = true;     // 高程优化
    int poiNum = 0;        // 兴趣点数量
    int minOaDist = 0;     // 最小绕障距离 单位cm
    float vFov = 0;        // 相机视场角
    float yawRef = 0;      // 云台角度
    float gimbalPitch = 0; // 俯仰角single 云台角度，范围：-30~90（单位：度）
    float courseRate = 0;  // 航向重叠率
    int defaultAction = 0; // 默认相机动作

    std::string ToString() const;
};

struct PathResultCameraAction
{
    float actionType = 0;                         // 动作类型
    float gimbalPitch = 0;                        // 云台Pitch角
    float gimbalRoll = 0;                         // 云台Roll角
    float actionYawRef = 0;                       // 偏航角指令
    float shootTimeInterval = 0;                  // 定时拍照间隔
    float shootDisInterval = 0;                   // 定距拍照距离间隔
    float actionTime = 0;                         // 动作执行时长
    float zoomRate = 0;                           // 变焦倍数
    float reserved[2];                            // 预留

    std::string ToString() const;
};

struct PathResultLine
{
    short wpTypeExe = 0;                                   // 航点类型 1代表停下的点，2代表协调转弯
    double wpPrevLLAExe[COORDINATE_TYPE_NUM];              // 起点坐标，经纬高        
    double wpCurrLLAExe[COORDINATE_TYPE_NUM];              // 终点坐标，经纬高    
    double wpCentLLAExe[COORDINATE_TYPE_NUM];              // 圆心坐标，经纬高
    double velRefFP = 0;                                   // 航点速度
    double velRefNxtFP = 0;                                // 下个航点速度
    short altPrioFP = 0;                                   // 航点高度优先级 1 代表当前最高，0 代表等优先级，-1 代表当前最低
    double fpLength = 0;                                   // 航线长度
    double estimatedTime = 0;                              // 航线预计飞行时间
    short headingModeFP = 0;                               // 此航点中动作朝向模式 1表示协调转弯，2表示手动，3表示自定义
    short poiValidFP = 0;                                  // 兴趣点是否有效 -1 表示无兴趣点， 1 表示有兴趣点
    double poiFP[COORDINATE_TYPE_NUM];                     // 对应兴趣点的坐标，经纬高
    short fpActionNum = 0;                                 // 此航点动作总数
    short emgActFP = 0;                                    // 每个航段的首航点的应急动作类型。0 为无动作，1 为悬停，2 为降落，3 为返航
    float fpShootNum = 0;                                  // 照片总张数
    short actExist = 0;                                    // 是否有航段动作
    std::vector<PathResultCameraAction> msnActionInfo;     // 航点动作（11个）实际ActionNum_FP+1个，最后一个是下一个航点的第一个动作

    std::string ToString() const;
};

struct PathResultMission
{
    float totalFlyTime = 0;                     // 总飞行时间
    float totalFlyLength = 0;                   // 总飞行路程
    int photoNum = 0;                           // 总照片张数
    double area = 0;                            // 面积,航点任务没有
    short flyPathNum = 0;                       // 航线个数
    int pts4PlotNum = 0;                        // 绘图点个数
    float uavHeading = 0;                       // 无人机机头朝向
    std::vector<double> pts4PlotLLA;            // 所有绘图点坐标展开（Pts4PlotNum个经度，Pts4PlotNum个维度，Pts4PlotNum个高度，剩下的为0 有效数值为前3*Pts4PlotNum个
    int arrowNum = 0;                           // 箭头个数
    std::vector<double> arrowPosDirLLA;         // 箭头纬经高和方向(以正东为x轴，正南为y，向下为z)。所有箭头点坐标展开（ArrowNum个纬度，ArrowNum个经度，ArrowNum个高度，ArrowNum个箭头方向,有效数值为前4*ArrowNum个

    std::vector<float> radiusMax;               // 航点处可设置的最大半径    
    std::vector<PathResultLine> fpInfoStrc;     // 航线信息（1000个）有效点为FPNum个
    short errorCode = 0;                        // 算法调用返回的航线错误码, 0-normal；1-相邻航点间距离超过10公里，2-相邻航点间高度差超过1公里，3-包含1和2的错误总和

    std::vector<double> ToLatlng() const;
    std::string ToString() const;
};

struct ObliqueResultMission
{
    PathResultMission missInfo;
    PathResultMission missInfo1;
    PathResultMission missInfo2;
    PathResultMission missInfo3;
    PathResultMission missInfo4;

    int GetLineSize() const;
    double GetTotalTime() const;
    double GetTotalPhotoNum() const;
    double GetTotalLen() const;
    double GetTotalArea() const;

    std::string ToString() const;
};

struct PathPoint
{
    short wpTypeUsr = 0;                          // 航点类型: 1-代表停下的点，2-代表协调转弯
    float wp2ArcDistUsr = 0;                      // 表示WPType=3的时候，自动协调拐弯的弧线距离相应航点的最远距离 范围大于0，小于100 值默认为2，单位
    double wpLLAUsr[COORDINATE_TYPE_NUM];         // 用户设置的航点，经纬高
    double radUsr = 0;                            // 用户设置转弯半径
    double velRefUsr = 0;                         // 速度
    short altPrioUsr = 0;                         // 航点高度优先级    1表示优先级比前一个点高，-1表示比前一个点低，0表示无优先级
    short headingMode = 0;                        // 此航点中 动作朝向模式    1表示协调转弯，2表示手动，3表示自定义
    short poiValid = 0;                           // 兴趣点是否有效    -1 表示无兴趣点，1 表示有兴趣点
    double poiUsr[COORDINATE_TYPE_NUM];           // 对应兴趣点的坐标，经纬高    
    short emgActUsr = 0;                          // 航点的应急动作类型：0 为无动作，1 为悬停，2 为降落，3 为返航
    std::vector<CameraAction> msnActionInfo;      // 航点动作（10个）实际Action_Num个，最大为10

    std::string ToString() const;
};

struct PathMission
{
    short wpNum = 0;           // TODO: 是否必要，与wpInfoStrc.size()是否相同？
    short defaultRadiusFlag = 0;
    double homeLLA[COORDINATE_TYPE_NUM];
    std::vector<PathPoint> wpInfoStrc;

    std::string ToString() const;
};

struct SubPolyLine
{
    double wpPrevLLA[COORDINATE_TYPE_NUM];                 // 该航段起始点经纬高
    double wpCurrLLA[COORDINATE_TYPE_NUM];                 // 该航段结束点经纬高
    double wpCentLLA[COORDINATE_TYPE_NUM];                 // 因不支持协调拐弯，故数值与 WPCurrLLA 相同
    float fpLength = 0;                                    // 该航段长度
    float fpShootNum = 0;                                  // 该航段拍照张数
    float totalFlyTime = 0;                                // 该航段飞行时间
    float pitch = 0;                                       // 该航段云台角度（单位：度）

    std::string ToString() const;
};

struct SubPolyLineInfo
{
    static const int SUB_POLYLINE_NUM = 250;
    static const int POLY_POINT_NUM = 750;

    std::vector<SubPolyLine> subPolyLineInfoData;                  // 250x1 结构体，存储该子航带各航段信息
    int pts4PlotNum = 0;                                           // 该子航带的航点数量
    int vertexPtsNum = 0;                                          // 该子航带的顶点数量
    std::vector<double> pts4PlotOut;                               // 该子航带的航点经纬高，顺序为所有点纬度+经度+高
    std::vector<double> subAreaVertexPts;                          // 该子航带的顶点经纬高，顺序为所有点纬度+经度+高
    float subPolyLineLength = 0;                                   // 该子航带的航程
    float subPolyLineTime = 0;                                     // 该子航带的航时
    float shootNum = 0;                                            // 该子航带的拍照张数

    std::list<AutelLatLng> ParsePts4Slot() const;                  // 获取航带路径
    std::list<AutelLatLng> ParseVertexPts() const;                 // 获取航带区域

    std::string ToString() const;
};

struct CorridorInfo
{
    static const int SUB_POLYLINE_NUM = 100;
    std::vector<SubPolyLineInfo> corridorData;
    int subpolylineNum = 0;                                   // 子航带数量
    float shootDisInterval = 0;                               // 定距拍照间隔
    float totalShootNum = 0;                                  // 总拍照张数
    float totalLength = 0;                                    // 总航程
    float totalTime = 0;                                      // 总航时

    std::string ToString() const;
};

struct PoiPoint
{
    long latitude = 0;     // 兴趣点经度 * 1E-7
    long longitude = 0;    // 兴趣点纬度* 1E-7
    int altitude = 0;      // 兴趣点海拔高度 mm

    std::string ToString() const;
};

struct WaypointInfo
{
    int waypointType = 0;                   // 航点类型，1 代表停下的点，2 代表协调转弯
    int lineType = 0;                       // 航线类型，1 直线，2 圆弧
    long prevLatitude = 0;                  // 起点经度 * 1E-7 因Java Int类型为有符号，所以此值会超出范围，改用long，c层再转成无符号整形
    long prevLongitude = 0;                 // 起点纬度* 1E-7
    int prevAltitude = 0;                   // 起点海拔高度 mm
    long curLatitude = 0;                   // 终点经度 * 1E-7
    long curLongitude = 0;                  // 终点纬度* 1E-7
    int curAltitude = 0;                    // 终点海拔高度 mm
    long centerLatitude = 0;                // 圆心经度 * 1E-7
    long centerLongitude = 0;               // 圆心纬度* 1E-7
    int centerAltitude = 0;                 // 圆心海拔高度
    float velocityRef = 0;                  // 速度参考 m/s
    float velocityRefNext = 0;              // 下一条航线的速度参考 m/s
    int altitudePriority = 0;               // 航点高度优先级
    int headingMode = 0;                    // 此航点中 动作朝向模式
    int actionNum = 0;                      // 此航点动作总数 （最大10个）
    int poiValid = 0;                       // 关联的兴趣点ID
    int fpTime = 0;                         // 航线预计时长 0.01s
    int fpLength = 0;                       // 航线长度 0.01m
    int reserved[2];                        // 对应兴趣点的信息
    PoiPoint poi;                           // 对应兴趣点的信息
    std::vector<CameraAction> actions;      // 对应动作信息 （12个，最后一个为下一航点第一个动作）

    std::string ToString() const;
};

struct MissionInfo
{
    int missionId = 0;                       // 任务ID
    int altitudeType = 0;                    // 相对高度or海拔高度(m)
    int missionType = 0;                     // 任务类型
    int finishAction = 0;                    // 任务完成后执行动作 1悬停    2返航 3降落
    int rcLostAction = 0;                    // 图传断联后执行动作
    int poiNum = 0;                          // 兴趣点数量 不再使用
    int minOADist = 0;                       // 最小绕障距离 单位cm
    int obstacleMode = 0;                    // 避障模式
    int grideEnableMapping = 0;              // 测绘是否开启双网格
    float vfovMapping = 0;                   // 相机视场角 degree
    float yawRefMapping = 0;                 // 测绘航向角度 degree
    int overlapMapping = 0;                  // 航向重叠率
    float gimbalPitchMapping = 0;            // 测绘云台俯仰角度 degree
    int missionTime = 0;                     // 任务总时长(0.01s)
    int missionLength = 0;                   // 任务总路程(0.01m)
    std::vector<WaypointInfo> waypoints;     // 对应航点信息 * 500
    uint32_t reserved[2] = {0};              //  预留:0:高程优化标志位;1:和航向垂直于航线参数
    CameraAction actionDefault;              // 航线相机动作
    int64_t guid = 0;

    std::string ToString() const;
};

struct PolyLineResult
{
    CorridorInfo corridorDispInfo;             // 航带信息
    std::vector<float> totalDotList;           // 所有航点的 XY
    std::vector<int> dotNumList;               // 各子航带内航点数
    int subPolyLineNum = 0;                    // 子航带数量
    int errorCode = 0;                         // 错误码

    bool IsSuccess() const;
    std::vector<SubPolyLineInfo> GetSubPolyLineInfo() const;

    std::string ToString() const;
};

struct PathPlanningResult
{
    std::vector<double> whiteLineList;       // 轨迹线坐标 la,lo,al
    std::vector<double> directionList;       // 箭头坐标位置角度
    std::vector<double> timeLengthList;      // 每个航点上的预估时间和距离, [长度,时间]

    double optCourseAngle = 0;               // 算法库给出的最优航向角度（只针对测绘）
    double flyLength = 0;
    double flyTime = 0;
    double pictNum = 0;                      // 照片数
    double ignorePoints = 0;                 // 区域内忽略的小于 5 米的航点个数，暂时用不到
    double area = 0;                         // 面积
    int errorCode = 0;                       // 0:成功， 1:失败(点数太多)

    std::list<AutelLatLng> whiteLatLngList;
    std::list<DirectionLatLng> directionLatLngList;

    PathResultMission mission;           // 新算法接口返回的数据
        
    std::list<AutelLatLng> GetWhiteLatLngList();
    std::list<DirectionLatLng> GetDirectionLatLngList();
    std::vector<double> GetPointLengthList();
    std::vector<double> GetPointTimeList();

    std::string ToString() const;
};

struct ObliquePathPlanningResult
{
    std::vector<double> whiteLineList;
    std::vector<double> whiteLineList1;
    std::vector<double> whiteLineList2;
    std::vector<double> whiteLineList3;
    std::vector<double> whiteLineList4;

    std::vector<double> directionList;
    std::vector<double> directionList1;
    std::vector<double> directionList2;
    std::vector<double> directionList3;
    std::vector<double> directionList4;

    std::vector<double> timeLengthList;     //每个航点上的预估时间和距离
    std::vector<double> timeLengthList1;
    std::vector<double> timeLengthList2;
    std::vector<double> timeLengthList3;
    std::vector<double> timeLengthList4;

    double optCourseAngle = 0;             //算法库给出的最优航向角度（只针对测绘）
    double optCourseAngle1 = 0;
    double optCourseAngle2 = 0;
    double optCourseAngle3 = 0;
    double optCourseAngle4 = 0;

    double flyLength = 0;
    double flyLength1 = 0;
    double flyLength2 = 0;
    double flyLength3 = 0;
    double flyLength4 = 0;

    double flyTime = 0;
    double flyTime1 = 0;
    double flyTime2 = 0;
    double flyTime3 = 0;
    double flyTime4 = 0;

    double pictNum = 0;
    double pictNum1 = 0;
    double pictNum2 = 0;
    double pictNum3 = 0;
    double pictNum4 = 0;

    double ignorePoints = 0;    //区域内忽略的小于 5 米的航点个数，暂时用不到
    double ignorePoints1 = 0;
    double ignorePoints2 = 0;
    double ignorePoints3 = 0;
    double ignorePoints4 = 0;

    double area = 0;            //面积
    double area1 = 0;
    double area2 = 0;
    double area3 = 0;
    double area4 = 0;

    double direction = 0;
    double direction1 = 0;
    double direction2 = 0;
    double direction3 = 0;
    double direction4 = 0;

    int errorCode = 0;  //0:成功， 1:失败(点数太多)

    std::vector<double> pointLengthList;
    std::vector<double> pointLengthList1;
    std::vector<double> pointLengthList2;
    std::vector<double> pointLengthList3;
    std::vector<double> pointLengthList4;

    std::vector<double> pointTimeList;
    std::vector<double> pointTimeList1;
    std::vector<double> pointTimeList2;
    std::vector<double> pointTimeList3;
    std::vector<double> pointTimeList4;

    std::vector<PathPlanningResult> pathPlanningResultList;

    ObliqueResultMission mission;


    void Init();
    std::vector<double> GetAllPointLengthList() const;
    std::vector<double> GetAllPointTimeList() const;

    // 照片数，时间，距离是要累加的，但是面积用一个就好了，5个的面积是一样的
    double GetTotalFlyTime() const;
    double GetTotalFlyLength() const;
    double GetTotalPictNum() const;
    void FormatPointLengthAndTime();
    std::pair<double, std::vector<double>> FormatPointAndLength(std::vector<double> timeLengthList, double valueOffset, int positionOffset);

    std::string ToString() const;
};

struct CameraProjectionResult
{
    std::list<double> centerLla;
    std::list<double> ulLla;
    std::list<double> urLla;
    std::list<double> dlLla;
    std::list<double> drLla;

    short errorCode = 0;          // 为0时表示没有错误

    std::string ToString() const;
};

struct PolygonMission
{
    double homeLLA[COORDINATE_TYPE_NUM];     // Home点坐标,经纬高
    double droneLLA[COORDINATE_TYPE_NUM];    // Drone点坐标,经纬高
    double vertexes[COORDINATE_TYPE_NUM];    // 顶点坐标,经纬高经纬高
    int finishAction = 0;                    // 任务结束动作
    int userDefineAngle = 0;                 // 是否有航向角 0:自动，1：用户自定义航向
    float courseAngle = 0;                   // 主航线角度
    float courseRate = 0;                    // 航向重叠率
    float sideRate = 0;                      // 旁向重叠率
    float speed = 0;                         // 飞行速度
    float height = 0;                        // 飞行高度,相对(起始点)航高
    float relativeH = 0;                     // 相对飞行高度起飞点高度-任务测区高度,如果测区高度比起飞点高则为负值 (单位：m)
    int doubleGrid = 0;                      // 双向网格: 0:关闭;1:打开;
    int altOptim = 0;                        // 高程优化: 0:关闭;1:打开;
    int roundEnable = 0;                     // 协调转弯: 0:关闭;1:打开;
    int photoAngle = 0;                      // 拍照角度;
    float gimbalPitch = 0;                   // 云台俯仰角
    float hFov = 0;                          // 云台水平角度
    float vFov = 0;                          // 云台垂直角度
    float userEnlargeLength = 0;             // 航线外扩的距离

    bool IsDoubleGrid() const;
    bool IsAltOptim() const;
    bool IsUserDefineAngle() const;
    bool IsRoundEnable() const;

    bool IsDroneLlaValueNaN() const;
    bool IsHomeLlaValueNaN() const;

    std::string ToString() const;
};

struct ObliqueMission : public PolygonMission
{
    float tiltCourseRate = 0;     // 斜射航向重叠率
    float tiltSideRate = 0;       // 斜射旁向重叠率
    float tiltSpeed = 0;          // 斜射飞行速度
    float tiltHeight = 0;         // 斜射飞行高度,相对(起始点)航高
    float tiltGimbalPitch = 0;    // 斜射云台俯仰角

    std::string ToString() const;
};

struct AutelCoordinate3D
{
    double latitude = -1000.0;
    double longitude = -1000.0;
    double altitude = 0.0;

    std::string ToString() const;
};

struct PolyLineMission
{
    double anchorLLAIn[COORDINATE_TYPE_NUM];    // 锚点坐标(单位：度，度，米),排列顺序[all 纬度；all 经度；all 高]
    double homeLLA[COORDINATE_TYPE_NUM];        // 返航点坐标(单位：度，度，米)
    float uavFlyAlt = 0;                        // 相对起飞点的高度(单位：m)
    float uavFlyVel = 0;                        // 执行任务时的最大速度(单位：m/s)
    int anchorNumInput = 0;                     // 锚点数量 用户设置的生成航带的标定点个数 最大 100 个
    int scanMode = 0;                           // 航线模式 1 纵向，2 横向，3 沿边缘
    float cutInterval = 0;                      // 分段长度 切割航带的长度(单位：m)
    float widthLeft = 0;                        // 左扩距离  沿中线往左扩的距离(单位：m)
    float widthRight = 0;                       // 右扩距离 single 沿中线往右扩的距离(单位：m)
    float widthSide = 0;                        // 旁向拍照距离 single 相机沿旁向的拍照范围(单位：m)
    float overlapSide = 0;                      // 旁向重叠率 single 垂直飞行方向的重叠率(0~1)
    int coverEdge = 0;                          // 全覆盖 single 1 全覆盖，2 高效（不覆盖） 默认：1
    int edgeImgImprove = 0;                     // 边缘优化 single 1 不优化，2 优化 默认：1
    int leftSameRight = 0;                      // 左右等距外扩 single 1 非等距外扩，2 按大距离外扩
    float widthHead = 0;                        // 航向拍照距离 single 相机沿航向的拍照范围(单位：m)
    float overlapHead = 0;                      // 航向重叠率 single 沿飞行方向的重叠率(0~1)
    float centerLine = 0;                       // 是否包含中心线 1 不优化，2 优化 默认：1
    float altOptim = 0;                         // 高程优化: 0:关闭;1:打开;
    float userEnlargeLength = 0;                // 航线外扩的距离

    std::string ToString() const;
};

struct Geo2Pixel
{
    double px = 0;                                                // 输出兴趣点在图像宽度上的比例坐标
    double py = 0;                                                // 输出兴趣点在图像高度上的比例坐标
    int show = 0;                                                 // 该点是否可见 0 不可见 1可见
    double distance[SPACE_DIST_TYPE_NUM];                         // 目标距离当前位置的垂直距离与水平距离

    std::string ToString() const;
};

// 云台pitch与yea值
struct CalCenterAttitudeResult
{
    double x = 0;
    double y = 0;
    double z = 0;

    std::string ToString() const;
};

struct GPSFromScreenPosition
{
    double x = 0;
    double y = 0;
    double z = 0;
    int type = 0;

    std::string ToString() const;
};

struct TargetFromSrceen
{
    double latitude = 0;          // 输出中心点地址坐标的纬度
    double longitude = 0;         // 输出中心点坐标地址的经度
    double altitude = 0;          // 输出中心点地理坐标高度

    std::string ToString() const;
};

/**
 * @brief 快速夜航任务参数
 */
struct MissionFastNightSlam {
    int32_t lat;  //集结点 纬度 * 1e7
    int32_t lon;  //集结点 经度 * 1e7
    int32_t alt;  //集结点 相对高度 * 1e3

    std::string ToString() const;
};

/**
 * @brief 编队坐标参数设置
 */
struct DroneFormationCoordinateType
{
    double start_angle = -PI/2.0;  // 起始角度
    double end_angle = PI/2.0;    // 结束角度
    double radius = 50.0;       // C形编队的半径m
    double lat = 0.0;          // 集结点 纬度
    double lon = 0.0;          // 集结点 经度
    int32_t alt = 200000;     //集结点 相对高度 * 1e3
    int32_t height_spacing = 5000;  // 高度间距* 1e3

    std::string ToString() const;
};

/**
 * @brief 飞机编队坐标项
 */
struct DroneCoordinate
{
    uint32_t deviceId;
    double lat;  //集结点 纬度
    double lon;  //集结点 经度
};

} // namespace AutelMobileSdk

#endif  
