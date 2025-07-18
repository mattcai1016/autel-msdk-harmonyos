#ifndef ERROR_CODE_H
#define ERROR_CODE_H

namespace AutelMobileSdk
{

enum class ErrorCode
{
    OK = 0,
    Error = 1,
    FailedToConnectNetwork,
    FailedToSendUdpDatagram,
    FailedToSendTcpData,
    MsgQueEmpty,
    NoMsgObject,
    ErrorMsgFormat,
    DeviceOffline, //设备不在线
};

enum class UpgradeErrorType
{
    CodeUnknown = -100,             // 未知错误
    RepeatRequest = -6,             // 重复请求
    DeviceDisconnected = -5,        // 设备未连接
    ResponseCodeError = -4,         // 响应码错误
    ProtoResponseTimeout = -3,      // 响应超时
    ProtoResponseEmptyData = -2,    // 返回数据为空
    ProtoResponseParseError = -1,   // 解析失败
    UpgradeErrNone = 0,             // No Error
    UpgradeErrFly = 1,              // In Flight
    UpgradeErrBusy = 2,             // In Upgrading
    UpgradeErrMd5 = 3,              // Md5 Error
    UpgradeErrExist = 4,            // File Not Exist
    UpgradeErrLobat = 5,            // Low Battery
    UpgradeErrModel = 6,            // Model Not Match
    UpgradeErrSpace = 7,            // No Enough Space To Upgrade
    UpgradeErrHead = 8,             // Error Header Of Pkg, Like Crc Error
    UpgradeErrSign = 9,             // Error Signature, Untrusted Firmware
    UpgradeErrSize = 10,            // Error Firmware Size, Not Match Header
    UpgradeErrPackage = 11,         // Package Error
    UpgradeErrVersion = 12,         // Error Major Version, Not Match Firmware
    UpgradeErrLversion = 13,        // Lower Than The Current Version, Need Force Flag
    UpgradeErrRefuse = 14,          // Refuse Upgrade Request, Errdesc For More Details
    UpgradeErrSpecial = 15,         // Special Error Of Every Pkg, Use Errdesc For Details
};

enum class AutelStatusCode
{
    Unknown = 0,                           // 未知
    ProtoResponseSuccess = 1,              // 成功
    RosError = 2,                          // Ros服务反馈失败
    RosTimeout = 3,                        // Ros接口调用超时
    RosInterfaceCallError = 4,             // Ros接口调用失败
    GatewayUnrealizedMsg = 5,              // 网关未实现该消息
    GatewayReportTimeout = 6,              // 网关响应超时
    UnregisteredMsg = 7,                   // 未注册消息
    IllegalMsg = 8,                        // 当前模式下该消息不合法

    // 自定义的错误码
    ProtoResponseParseError = -1,          // 解析失败
    ProtoResponseEmptyData = -2,           // 返回数据为空
    ProtoResponseTimeout = -3,             // 响应超时
    ResponseCodeError = -4,                // 响应码错误
    DeviceDisconnected = -5,               // 设备未连接
    RepeatRequest = -6,                    // 重复请求
    CheckSuccess = -101,                   // 数据校验成功
    OutOfRange = -102,                     // 数据越界

    // 文件服务错误码
    FileDataLost = 300,                    // 数据丢失
    NetWorkException = 502,                // 链路异常
    DownloadFileFailed = 302,              // 文件下载失败
    DataTransformException = 303,          // 数据解析错误
    ResponseNull = 304,                    // 响应数据为空

    // 文件上传状态
    FileUploadUnknown = 3100,              // 文件上传状态未知
    FileUploadSuccess = 3101,              // 文件上传成功
    FileUploadUploading = 3102,            // 文件上传中
    FileUploadFailed = 3103,               // 文件上传失败

    // 文件下载状态
    FileDownloadUnknown = 3104,            // 文件下载状态未知
    FileDownloadSuccess = 3105,            // 文件下载成功
    FileDownloadUploading = 3106,          // 文件下载中
    FileDownloadFailed = 3107,             // 文件下载失败
    FileDownloadUrlEmpty = 3108,           // 文件下载路径或者保存路径为空

    // 文件基础功能操作状态
    SystemError = 3109,                    // 系统错误
    NoParams = 3110,                       // 未传递参数
    InvalidFileParams = 3111,              // 传递的文件参数错误
    InvalidFileDiretoryParams = 3112,      // 传递的文件夹参数错误
    InternalError = 3113,                  // 系统内部错误，例如oom, 需要检查服务端日志进一步确认
    MagicMessageError = 3114,              // 消息透传错误
    Md5CheckError = 3115,                  // Md5校验错误
    FileDeleteUnknown = 3116,              // 文件删除未知
    FileOperationSuccess = 3117,           // 文件删除成功
    ServiceConnectFailed = 3118,           // 服务器连接异常
    FileBadRequest = 3119,                 // 请求参数错误
    FileNotFound = 3120,                   // 资源没找到
    FileMethodNotAllowed = 3121,           // 请求的资源的内容特性无法满⾜请求头中的条件
    FileConflict = 3122,                   // 资源冲突
    InternalServerError = 3123,            // 服务器异常
    FileGenUnknown = 3124,                 // 文件生成状态未知
    FileGenSuccess = 3125,                 // 文件生成成功
    FileGenFailedPathEmpty = 3126,         // 文件生成失败：路径不能为空
    FileGenFailedCreateDirFailed = 3127,   // 文件生成失败：创建文件目录失败
    FileGenFailedCreateDirError = 3128,    // 文件生成失败：创建文件目录异常
    FileGenFailedWaypointEmpty = 3129,     // 文件生成失败：任务航线不能为空

    // 主控定义的错误码 
    UNKNOWN = 0,                                            // 未知
    PROTO_RESPONSE_SUCCESS = 1,                             // 成功
    ROS_ERROR = 2,                                          // ROS服务反馈失败
    ROS_TIMEOUT = 3,                                        // ros接口调用超时
    ROS_INTERFACE_CALL_ERROR = 4,                           // ros接口调用失败
    GATEWAY_UNREALIZED_MSG = 5,                             // 网关未实现该消息
    GATEWAY_REPORT_TIMEOUT = 6,                             // 网关响应超时
    UNREGISTERED_MSG = 7,                                   // 未注册消息
    ILLEGAL_MSG = 8,                                        // 当前模式下该消息不合法

    // 自定义的错误码
    PROTO_RESPONSE_PARSE_ERROR = -1,                        // 解析失败
    PROTO_RESPONSE_EMPTY_DATA = -2,                         // 返回数据为空
    PROTO_RESPONSE_TIMEOUT = -3,                            // 响应超时
    RESPONSE_CODE_ERROR = -4,                               // 响应码错误
    DEVICE_DISCONNECTED = -5,                               // 设备未连接
    REPEAT_REQUEST = -6,                                    // 重复请求

    CHECK_SUCCESS = -101,                                   // 数据校验成功
    OUT_OF_RANGE = -102,                                    // 数据越界

    // 文件服务错误码
    FILE_DATA_LOST = 300,                                   // 数据丢失
    NET_WORK_EXCEPTION = 502,                               // 链路异常
    DOWNLOAD_FILE_FAILED = 302,                             // 文件下载失败
    DATA_TRANSFORM_EXCEPTION = 303,                         // 数据解析错误
    RESPONSE_NULL = 304,                                    // 响应数据为空

    // 文件上传状态3_2_1_3
    FILE_UPLOAD_UNKNOWN = 310200000,                        // 文件上传状态未知
    FILE_UPLOAD_SUCCESS = 310202000,                        // 文件上传成功
    FILE_UPLOAD_UPLOADING = 310203000,                      // 文件上传中
    FILE_UPLOAD_FAILED = 310204000,                         // 文件上传失败

    // 文件下载状态
    FILE_DOWNLOAD_UNKNOWN = 310210000,                      // 文件下载状态未知    
    FILE_DOWNLOAD_SUCCESS = 310212000,                      // 文件下载成功    
    FILE_DOWNLOAD_UPLOADING = 310213000,                    // 文件下载中    
    FILE_DOWNLOAD_FAILED = 310214000,                       // 文件下载失败    
    FILE_DOWNLOAD_URL_EMPTY = 310215000,                    // 文件下载路径或者保存路径为空

    // 文件基础功能操作状态
    SYSTEM_ERROR = 310222001,                               // 系统错误
    NO_PARAMS = 310222002,                                  // 未传递参数
    INVALID_FILE_PARAMS = 310222003,                        // 传递的文件参数错误
    INVALID_FILE_DIRETORY_PARAMS = 310222004,               // 传递的文件夹参数错误
    INTERNAL_ERROR = 310222005,                             // 系统内部错误,例如OOM, 需要检查服务端日志进一步确认
    MAGIC_MESSAGE_ERROR = 310222006,                        // 消息透传错误
    MD5_CHECK_ERROR = 310222007,                            // MD5校验错误
    FILE_DELETE_UNKNOWN = 310224000,                        // 文件删除未知
    FILE_OPERATION_SUCCESS = 310222200,                     // 文件删除成功
    SERVICE_CONNECT_FAILED = 310222301,                     // 服务器连接异常
    FILE_BAD_REQUEST = 310224400,                           // 请求参数错误
    FILE_NOT_FOUND = 310224404,                             // 资源没找到
    FILE_METHOD_NOT_ALLOWED = 310224405,                    // 请求的资源的内容特性无法满足请求头中的条件
    FILE_CONFLICT = 310224409,                              // 资源冲突
    INTERNAL_SERVER_ERROR = 310224500,                      // 服务器异常
        
    FILE_GEN_UNKNOWN = 310250000,                           // 文件生成状态未知    
    FILE_GEN_SUCCESS = 310252000,                           // 生成成功    
    FILE_GEN_FAILED_PATH_EMPTY = 310254001,                 // 文件生成失败：路径不能为空    
    FILE_GEN_FAILED_CREATE_DIR_FAILED = 310254002,          // 文件生成失败：创建文件目录失败    
    FILE_GEN_FAILED_CREATE_DIR_ERROR = 310254003,           // 文件生成失败：创建文件目录异常    
    FILE_GEN_FAILED_WAYPOINT_EMPTY = 310254004,             // 文件生成失败：任务航线不能为空

    UPLOAD_MISSION_NOTIFY_FAILED, 
    UPLOAD_MISSION_SET_SPEED_FAILED,
    UPLOAD_MISSION_HEALTH_CHECK_FAILED,
};

}

#endif

