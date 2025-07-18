#ifndef IFILE_SERVICE_H
#define IFILE_SERVICE_H

#include <memory>
#include "ErrorCode.h"
#include "CompletionListener.h"

namespace AutelMobileSdk
{
using SessionId = size_t;

class AUTELSDK_API IFileService
{
public:
    // ==========本地文件、目录操作操作类接口==========
    virtual ErrorCode CreateDirectory(const std::string& dir) = 0;
    virtual void DeleteFile(const std::string& fileName) = 0;
    virtual void DeleteDirectory(const std::string& dir) = 0;
    virtual bool IsFileExists(const std::string& filePath) = 0;
    virtual bool IsDirectoryExists(const std::string& dir) = 0;
    virtual size_t GetFileSize(const std::string& filePath) = 0;
    virtual size_t GetDirectorySize(const std::string& dir) = 0;

    // ==========飞机端文件操作操作类接口==========
    // 上传任务文件，返回上传任务的会话ID，可以用于取消上传。若成功，回调接口返回文件路径
    virtual SessionId UploadMissionFile(uint32_t deviceId, const std::string& filePath, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 上传禁飞区文件，返回上传任务的会话ID，可以用于取消上传。若成功，回调接口返回文件路径
    virtual SessionId UploadNoFlyZoneFile(uint32_t deviceId, const std::string& filePath, FileType fileType, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 上传OTA文件，返回上传任务的会话ID，可以用于取消上传。若成功，回调接口返回文件路径
    virtual SessionId UploadOTAFile(uint32_t deviceId, const std::string& filePath, const std::string& dstFilePath, FileType fileType, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 文件上传，返回上传任务的会话ID，可以用于取消上传。若成功，回调接口返回文件路径
    virtual SessionId UploadFTPFile(uint32_t deviceId, const std::string& filePath, const std::string& dstFilePath, FileType fileType, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 查询上传进度，返回查询任务的会话ID，可以用于取消查询。若成功，回调接口返回进度信息
    virtual SessionId QueryUploadProgress(uint32_t deviceId, const std::string& filePath, const std::string& dstFilePath, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 取消上传
    virtual void CancelUpload(uint32_t deviceId, SessionId sessionId) = 0;

    // 下载文件，返回下载任务的会话ID，可以用于取消下载。若成功，回调接口返回文件路径
    virtual SessionId DownloadFile(uint32_t deviceId, const std::string& srcFilePath, const std::string& dstFilePath, FilePathType pathType, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 下载文件，支持断点续传
    virtual SessionId DownloadFileResumable(uint32_t deviceId, const std::string& srcFilePath, const std::string& dstFilePath, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 下载媒体文件。若成功，回调接口返回文件路径
    virtual SessionId DownloadMediaFile(uint32_t deviceId, const std::string& srcFilePath, const std::string& dstFilePath, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 取消下载
    virtual void CancelDownload(uint32_t deviceId, SessionId sessionId) = 0;

    // 查询远端文件目录，若成功，回调接口返回目录下面的文件信息（JSON格式）
    virtual SessionId QueryRemoteFolder(uint32_t deviceId, const std::string& dstFilePath, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 检查数据链路健康度（目标设备是否可达）
    virtual SessionId CheckDataLinkHealth(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 删除远程媒体文件，参数为文件索引（通过查询远端文件目录接口获得）
    virtual SessionId DeleteRemoteMediaFile(uint32_t deviceId, int indexId, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 删除远端文件，参数为文件路径
    virtual SessionId DeleteRemoteFile(uint32_t deviceId, const std::string& url, std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    // 取消文件操作会话
    virtual void AbortFileOperationSession(uint32_t deviceId, SessionId sessionId) = 0;
};
}  // namespace AutelMobileSdk

#endif
