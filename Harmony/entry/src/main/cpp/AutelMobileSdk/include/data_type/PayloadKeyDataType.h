#ifndef PAYLOADKEYDATATYPE_H
#define PAYLOADKEYDATATYPE_H
#include <string>
#include <vector>
#include <cstdint>
#include "KeyValueBaseType.h"
#include "BaseType.h"
#include "Common.h"

namespace AutelMobileSdk
{

struct AUTELSDK_API TracerWorkModeControlMessage {
    int32_t seq; // 序列号
    /**
     *  0表示为关闭侦测模式下处理
     *  1或者2表示打开遥控；
     *  131表示打开遥控旋转解模糊处理
     *  11或者12表示打开图传侦测/定向模式下处理
     *  101或者102表示测试模式下处理-用于现场观测数据-遥控
     *  111或者112表示测试模式下处理-用于现场观测数据-图传
     *  8001或者8002表示测试模式下处理-用于现场观测数据
     **/
    int32_t workMode; // 工作状态控制
    int32_t dxNum; // 定向目标编号
    int32_t dxFreq; // 定向频率
    int32_t airType; // 飞机的类型
    /**
     * 飞手上报置信度门限（等级：1(极低)、2(低)、3(中)）
     */
    int32_t confidenceThr; // 置信度门限

    std::string ToString() const;
};

struct AUTELSDK_API TracerWorkModeControlRspMessage {
    int32_t seq; // 序列号,与请求消息相对应
    int32_t rlt; // 应答结果 0:成功 1:失败

    std::string ToString() const;
};

struct AUTELSDK_API ThrowActionMessage {
    std::vector<bool> channelIndexActive; // 通道索引激活状态

    std::string ToString() const;
};

struct AUTELSDK_API LightSpeakerMessage {
    int32_t seq;
    int32_t moduleID;
    int32_t action;
    int32_t value;
    std::string strValue;
    std::string strValueEx;

    std::string ToString() const;
};

struct AUTELSDK_API LightSpeakerControlRspMessage {
    int32_t seq;
    int32_t rlt;

    std::string ToString() const;
};

struct AUTELSDK_API LoudspeakerRealTimeMsg {
    int32_t seq;
    std::string value;

    std::string ToString() const;
};

struct AUTELSDK_API LightSpeakerRspMessage {
    int32_t seq;
    int32_t rlt;

    std::string ToString() const;
};

struct AUTELSDK_API LightSpeakerQueryMessage {
    int32_t seq;
    int32_t moduleID;
    int32_t query;
    int32_t pageIndex;

    std::string ToString() const;
};

struct AUTELSDK_API LightSpeakerPageContent {
    std::string strValue;
    std::string ToString() const;
};

struct AUTELSDK_API LightSpeakerQueryRspMessage {
    int32_t seq;
    int32_t value;
    std::string strValue;
    std::vector<LightSpeakerPageContent> pageContent;
    int32_t pageIndex;

    std::string ToString() const;
};

struct AUTELSDK_API PayloadInfo {
    int32_t payloadId;    //payload_id 由agent分配
    int32_t payloadType;  //payload类型
    int32_t isOnline;     // 0 不在线; 1 在线
    uint64_t lastActiveTime; // 当isOnline为0时有效
    int32_t payloadPosition; // 0 未知; 1 前; 2 后; 3 左; 4 右; 5 上; 6 下
    std::string psdklibVersion;
    std::string payloadVersion;

    std::string ToString() const;
};

struct AUTELSDK_API PayloadList {
    std::vector<PayloadInfo> payloadList;
    std::string ToString() const;
};

struct AUTELSDK_API SingleTargetInfoBean {
    int32_t tNum;           // 目标编号
    int32_t tType;          // 目标类型
    int32_t tCalCnt;        // 目标累计点数
    int32_t tWorkStatus;    // 目标工作状态
    int32_t tTimeCreate;    // 目标建立时间
    int32_t tTimeTest;      // 目标最近测试时间
    int32_t tSigBand;       // 目标信号频段
    int32_t tDistance;      // 目标距离
    int32_t tFreq;          // 目标频率
    int32_t tAmp;           // 目标幅度
    int32_t tmFw;           // 目标测量系方位角,0.1°
    int32_t tmFy;           // 目标测量系俯仰角,0.1°
    int32_t tfFw;           // 目标固定系方位角,0.1°
    int32_t tfFy;         // 目标固定系俯仰角,0.1°
    int32_t tConfidenceLevel;   // 置信度（等级：1(极低)、2(低)、3(中)、4(高)）
    int32_t tTimeOffset;        // 10ms周期内时间偏移量
    std::string tName;      // 目标数据库名称

    std::string ToString() const;
};

struct AUTELSDK_API TracerMeasureInfoMessage {
    int32_t frameNum;
    int32_t workStatus;
    int32_t tarNum;
    std::vector<SingleTargetInfoBean> tarInfo;
    int32_t workMode;

    std::string ToString() const;
};

struct AUTELSDK_API TracerSystemInfoMessage {
    std::string sn;             // 序列号
    std::string version;        // 版本号
    std::string ssid;           // wifi名称
    std::string ipAddress;      // IP地址
    int32_t workStatus;        // 工作状态
    int32_t faultStatus;       // 故障状态
    int32_t netStatus;         // 网络状态
    int32_t upTime;            // 开机时间
    int32_t cpu;               // cpu占用率
    int32_t memory;            // 内存占用率
    std::vector<int32_t> disk; // 磁盘占用率列表
    int32_t temperature;       // 芯片温度

    std::string ToString() const;
};

struct AUTELSDK_API ThrowerMessage {
    std::string type; //thrower型号
    int32_t multiChannelNum; //支持几路,2,4,6,8,10.....
    std::vector<bool> channelValidState; //第几路,bit0~bit31,bit0表示第1路，bit1表示第2路，以此类推,对应bit位为1表示valid，0表示unvalid
    std::vector<bool> currentChannelState; //第几路,bit0~bit31,bit0表示第1路，bit1表示第2路，以此类推,对应bit位为1表示throwed，0表示unthrowed
    uint64_t timestamp; //时间戳

    std::string ToString() const;
};

struct AUTELSDK_API ChannelCommonMessage {
    int32_t seq;
    int32_t value;
    std::string strValue;

    std::string ToString() const;
};

} // namespace AutelMobileSdk
#endif // PAYLOADKEYDATATYPE_H
