#ifndef IFLIGHT_MISSION_H
#define IFLIGHT_MISSION_H

#include <memory>

#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "FlightMissionKeyDataType.h"
#include "FlightMissionDataType.h"
#include "AITrackKeyDataType.h"
#include "IControllCompletionListener.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IFlightMission
{
public:
    // ==========任务规划算法类接口==========
    // 获取航点算法规划结果
    virtual ErrorCode GetWaypointPath(const PathMission& mission, PathResultMission& result) = 0;

    // 获取矩形多边形算法规划结果
    virtual ErrorCode GetMappingMissionPath(const PolygonMission& mission, PathPlanningResult& result) = 0;

    // 获取倾斜摄影算法规划结果
    virtual ErrorCode GetObliqueMappingPath(const ObliqueMission& mission, ObliquePathPlanningResult& result) = 0;

    // 获取航带算法规划结果
    virtual ErrorCode GetPolyLineMissionPath(const PolyLineMission& mission, PolyLineResult& result) = 0;

    // 获取飞机编队（C）
    virtual ErrorCode  GetDroneFormation(const std::vector<DroneCoordinate> & dronesPos, const DroneFormationCoordinateType &aircraftFormationCoordinateType, std::vector<DroneMissionFastNightSlamParam> &result) = 0;

    // ==========任务文件操作类接口==========
    // 生成任务文件，不传递listener时，为同步操作接口，否则为异步操作接口。返回值：0:正常;-1:路径不能为空;-2:创建文件目录失败;-3:创建文件目录异常;-4:任务航线不能为空
    virtual ErrorCode WriteMissionFile(const MissionInfo& missionInfo, const std::string& filePath = "", std::shared_ptr<CompletionListener<std::string>> listener = nullptr) = 0;

    // 生成禁飞区文件
    virtual ErrorCode WriteNoFlyZoneFile(const std::string& countryCode, const std::string& filePath, const NoFlyAreaBase& noFlyAreaBase) = 0;

    // 生成授权区文件
    virtual ErrorCode WriteAuthFlyZoneFile(const std::string& filePath, const std::string& fileName, const std::vector<AuthArea>& zones) = 0;

    // ==========航点任务接口==========
    // 上传航点任务文件
    virtual ErrorCode UploadWaypointMissionFile(uint32_t deviceId, const MissionInfo& missionInfo, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;

    // 下载航点任务文件
    virtual ErrorCode DownloadWaypointMissionFile(uint32_t deviceId, const std::string& srcPath, const std::string& dstPath, FilePathType type, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;

    // 进入航点任务状态
    virtual ErrorCode EnterWaypointMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出航点任务状态
    virtual ErrorCode ExitWaypointMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 执行航点任务
    virtual ErrorCode StartWaypointMission(uint32_t deviceId, const WaypointMissionInfo& missionInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 暂停航点任务
    virtual ErrorCode PauseWaypointMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 恢复航点任务
    virtual ErrorCode ResumeWaypointMission(uint32_t deviceId, const WaypointMissionInfo& missionInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止航点任务
    virtual ErrorCode StopWaypointMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 查询航点任务断点信息
    virtual ErrorCode QueryWaypointMissionBreakPointInfo(uint32_t deviceId, const WaypointMissionInfo& missionInfo, std::shared_ptr<CompletionListener<WaypointMissionBreakRspBean>> listener, int retryCount = 0) = 0;

    // 监听航点任务执行状态上报
    virtual ErrorCode ListenWaypointMissionStatusReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<WaypointMissionStatusReportNtfyBean>>& listener) = 0;
    virtual void CancelListenWaypointMissionStatusReport(uint32_t deviceId, ObjectId objectId) = 0;

    // ==========兴趣点任务接口==========
    // 创建兴趣点任务
    virtual ErrorCode CreateInterestingPoint(uint32_t deviceId, const InterestingPoint& interestingPoint, std::shared_ptr<CompletionListener<InterestPointMissionCreatePointRspBean>> listener, int retryCount = 0) = 0;

    // 进入兴趣点任务状态
    virtual ErrorCode EnterInterestingPointMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出兴趣点任务状态
    virtual ErrorCode ExitInterestingPointMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 启动兴趣点任务
    virtual ErrorCode StartInterestingPointMission(uint32_t deviceId, const InterestingPointMissionInfo& missionInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止兴趣点任务
    virtual ErrorCode StopInterestingPointMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 监听兴趣点任务状态上报
    virtual ErrorCode ListenInterestingPointMissionStatusReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<InterestPointMissionStatusReportNtfyBean>>& listener) = 0;
    virtual void CancelListenInterestingPointMissionStatusReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 监听兴趣点任务信息上报
    virtual ErrorCode ListenInterestingPointMissionInfoReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<InterestPointMissionInfoNtfyBean>>& listener) = 0;
    virtual void CancelListenInterestingPointMissionInfoReport(uint32_t deviceId, ObjectId objectId) = 0;

    // ==========跟踪任务接口==========
    // 进入跟踪任务状态
    virtual ErrorCode EnterTrackingMission(uint32_t deviceId, TrackType type, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出跟踪任务状态
    virtual ErrorCode ExitTrackingMission(uint32_t deviceId, TrackType type, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 选择跟踪目标区域
    virtual ErrorCode SetTrackingTargetRectangle(uint32_t deviceId, TrackType type, const TrackTargetRectangle& target, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 执行自由跟随任务
    virtual ErrorCode ExecFreeFollowTrackingMission(uint32_t deviceId, TrackType type, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 执行自由跟随任务
    virtual ErrorCode ExecHoverFollowTrackingMission(uint32_t deviceId, TrackType type, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 执行智能八方跟随任务
    virtual ErrorCode ExecDynamicFollowTrackingMission(uint32_t deviceId, TrackType type, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 执行平行跟随跟踪任务
    virtual ErrorCode ExecParallelFollowTrackingMission(uint32_t deviceId, TrackType type, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止跟踪任务
    virtual ErrorCode StopTrackingMission(uint32_t deviceId, TrackType type, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==========机群任务接口==========
    // 进入机群任务
    virtual ErrorCode EnterSwarmMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出机群任务
    virtual ErrorCode ExitSwarmMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 根据任务配置信息，生成任务文件、上传任务文件，并启动任务
    virtual ErrorCode StartSwarmMission(uint32_t deviceId, const MissionInfo& missionInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 已经上传了任务文件，启动指定任务
    virtual ErrorCode StartSwarmMission(uint32_t deviceId, const SwarmMissionInfo& missionInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 暂停机群任务
    virtual ErrorCode PauseSwarmMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 恢复机群任务
    virtual ErrorCode ResumeSwarmMission(uint32_t deviceId, const SwarmMissionInfo& missionInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止机群任务
    virtual ErrorCode StopSwarmMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 执行机群动作
    virtual ErrorCode ExecuteSwarmAction(uint32_t deviceId, int actionType, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 监听机群任务状态上报
    virtual ErrorCode ListenSwarmStatusReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<SwarmMissionStatusNtfyBean>>& listener) = 0;
    virtual void CancelListenSwarmStatusReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 鉴别机群任务上传报告
    virtual ErrorCode ListenSwarmUploadReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<SwarmMissionUploadFileNtfyBean>>& listener) = 0;
    virtual void CancelListenSwarmUploadReport(uint32_t deviceId, ObjectId objectId) = 0;

    // ==========快速任务==========
    // 进入快速任务
    virtual ErrorCode EnterFastMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出快速任务
    virtual ErrorCode ExitFastMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 多机修改编队参数改变队形
    virtual void UpdateDroneFormationTypeCoordinate(const std::vector<DroneCoordinate> & dronesPos,
                                                    const DroneFormationCoordinateType &aircraftFormationCoordinateType,
                                                    std::shared_ptr<IControllCompletionListener> listener, int retryCount = 0) = 0;

    // 修改编队参数改变队形
    virtual ErrorCode UpdateDroneFormationTypeCoordinate(DeviceId deviceId, const MissionFastNightSlamParam &missionFastNightSlamParam, std::shared_ptr<CompletionListenerListItemSwitchState<void>> listener, int32_t retry = 0) = 0;

    // ==========公共接口==========
    // 上传任务文件
    virtual ErrorCode UploadMissionFile(uint32_t deviceId, const std::string& filePath, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;

    // 进入KML任务
    virtual ErrorCode EnterKmlMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出KML任务
    virtual ErrorCode ExitKmlMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 开始KML任务
    virtual ErrorCode StartKmlMission(uint32_t deviceId, const MissionKmlGuid & param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 暂停KML任务
    virtual ErrorCode PauseKmlMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 继续KML任务
    virtual ErrorCode ContinueKmlMission(uint32_t deviceId, const MissionKmlGuid & param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止KML任务
    virtual ErrorCode StopKmlMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 一键停止任务
    virtual ErrorCode OneClickStopMission(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
};
}  // namespace AutelMobileSdk

#endif
