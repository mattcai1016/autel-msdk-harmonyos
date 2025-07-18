#ifndef UPGRADEKEYDATATYPE_H
#define UPGRADEKEYDATATYPE_H

#include <vector>
#include <string>

#include "Common.h"


namespace AutelMobileSdk
{

enum class CLIENT_TYPE_E
{
    CLIENT_TYPE_GND = 0, // 客户端是GND, 文件传输需要切换上下行
    CLIENT_TYPE_SKY = 1, // // 客户端是SKY, 文件传输不需要切换上下行
};

enum class RESULT_TYPE_E {
    UPGRADE_FINISH = 0,        ///< 升级结束
    UPGRADE_SUCCESS = 1,       ///< 升级成功
    UPGRADE_FAILURE = 2,       ///< 升级失败
    UPGRADE_UNKNOWN = 3,
};

enum class ERROR_TYPE_E {
    UPGRADE_ERR_NONE = 0,
    UPGRADE_ERR_FLY = 1,
    UPGRADE_ERR_BUSY = 2,
    UPGRADE_ERR_MD5 = 3,
    UPGRADE_ERR_EXIST = 4,
    UPGRADE_ERR_LOBAT = 5,
    UPGRADE_ERR_MODEL = 6,
    UPGRADE_ERR_SPACE = 7,
    UPGRADE_ERR_HEAD = 8,
    UPGRADE_ERR_SIGN = 9,
    UPGRADE_ERR_SIZE = 10,
    UPGRADE_ERR_PACKAGE = 11,
    UPGRADE_ERR_VERSION = 12,
    UPGRADE_ERR_LVERSION = 13,
    UPGRADE_ERR_REFUSE = 14,
    UPGRADE_ERR_SPECIAL = 15,
    UPGRADE_ERR_NON_SDCRAD = 16,
};

enum class UpdateStatusCode {
    UNKNOWN = 0,  //未知的无效码
    SUCCESS = 1,  //成功，条件具备，可以升级
    ERROR   = 2,  //条件不具备，不可以升级 见UpgradeErorrCode(result_code)
};

enum class UpgradeErorrCode { // result_code
    UPGRADE_ERR_FLY   = 1,   // 飞行中
    UPGRADE_ERR_BUSY  = 2,   // 低电量
    UPGRADE_ERR_LOBAT = 5,   // 正在升级中
};

struct AUTELSDK_API UpgradeQuery
{
    int32_t clientType = 0; //  客户端类型 CLIENT_TYPE_E

    std::string ToString() const;
};

struct AUTELSDK_API UpgradeEnterMsg
{
    int32_t clientType = 0; //  客户端类型 CLIENT_TYPE_E

    std::string ToString() const;
};

struct AUTELSDK_API UpgradeTransfer
{
    int32_t progress = 0; //  文件传输进度上报, 升级服务用于判断是否退出升级

    std::string ToString() const;
};

struct AUTELSDK_API UpgradeCheckMsg
{
    std::string md5;            // 产品包文件MD5校验
    std::string filename;       // 产品包文件名, 含完整路径

    std::string ToString() const;
};

struct AUTELSDK_API UpgradeExecuteReq
{
    bool force;                // 强制升级标志
    std::string filename;      // 产品包文件名, 含完整路径

    std::string ToString() const;
};

struct AUTELSDK_API UpgradeResult
{
    int32_t result;          // 升级结果, 参见 RESULT_TYPE_E 枚举
    int32_t errCode;         // 升级错误, 参见 ERROR_TYPE_E 枚举
    std::string errDesc;     // 错误描述

    std::string ToString() const;
};


struct AUTELSDK_API DroneVersionItem
{
    int32_t componentId;            // 飞机能力集建立后，该字段将由飞机上设备注册顺序决定，Modelx飞机当前为固定ID,(例如：前视雷达ID，后视雷达ID)
    std::string componentSn;        // SN
    std::string hardwareVersion;    // 硬件版本
    std::string softwareVersion;    // 软件版本
    int32_t componentModel;         //整型枚举值,组件设备型号
    std::string strComponentModel;  //字符型组件设备型号，（例如：相机设备型号XM802）
    std::string label;              //飞机能力集预留字段，描述当前组件的信息（例如：前相机，后相机)
    int32_t componentType;          //描述当前组件类型（例如：相机，云台，飞控）
    std::string bootloaderVersion;  //mcu的bootloader版本信息

    std::string ToString() const;
};

struct AUTELSDK_API DroneVersionInfo
{
    std::vector<DroneVersionItem> versionInfoList;

    std::string ToString() const;
};

struct AUTELSDK_API UpgradeState
{
    int32_t state = 0;

    std::string ToString() const;
};




} // namespace AutelMobileSdk

#endif // UPGRADEKEYDATATYPE_H
