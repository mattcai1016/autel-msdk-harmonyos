#ifndef I_ALBUM_H
#define I_ALBUM_H

#include <string>
#include <memory>
#include "AlbumDataType.h"
#include "CameraBaseType.h"
#include "CompletionListener.h"

namespace AutelMobileSdk
{

using ImgKey = std::string;

class AUTELSDK_API IAlbum
{
public:
    //获取本地目录(程序所在目录)
    virtual std::string GetLocalPath() = 0;

    //通过key得到本地缩略图路径
    virtual std::string GetLocalThumbnailPath(const std::string& key) = 0;

    //获取设备媒体文件列表
    virtual void GetMediaFileList(uint32_t deviceId,
                                  MediaFileType mediaType,
                                  StorageType storageType,
                                  const std::string& folder, //文件夹名，可以不传或者传空，没有时表示查询整个相册文件列表
                                  int count,
                                  std::shared_ptr<CompletionListener<AlbumQueryResult>> listener,
                                  OrderType order = OrderType::REVERSE,
                                  int offest = 0) = 0;

    //获取设备目录列表
    virtual void GetMediaFolderList(uint32_t deviceId,
                                    StorageType storageType,
                                    std::shared_ptr<CompletionListener<AlbumFolderQueryResult>> listener,
                                    OrderType order = OrderType::REVERSE) = 0;

    //下载设备媒体文件
    virtual void DownloadMediaFile(uint32_t deviceId,
                                   const AutelMediaInfo& mediaInfo,
                                   const std::string& dstFilePath,
                                   std::shared_ptr<ICompletionListener> listener) = 0;

    //删除设备媒体文件
    virtual void DeleteMediaFile(uint32_t deviceId,
                                 const AutelMediaInfo& mediaInfo,
                                 std::shared_ptr<ICompletionListener> listener) = 0;

    //设备健康检测
    virtual void CheckHealth(uint32_t deviceId, std::shared_ptr<ICompletionListener> listener) = 0;

    //加载媒体文件缩略图
    virtual void LoadMediaFileThumbnail(uint32_t deviceId,
                                        const AutelMediaInfo& imgInfo,
                                        std::shared_ptr<CompletionListener<std::string>> listener) = 0;

    //获取设备照片文件的缩略图路径
    virtual std::string GetThumbnaiImageHttpUrl(uint32_t deviceId, const AutelMediaInfo& imgInfo) = 0;

    //获取设备照片文件的预览图路径
    virtual std::string GetPreviewImageHttpUrl(uint32_t deviceId, const AutelMediaInfo& imgInfo) = 0;

    //获取设备视频文件的预览路径
    virtual std::string GetPreviewVideoUrl(uint32_t deviceId, const AutelMediaInfo& mediaInfo) = 0;     // 获取预览视频的http链接

    // 下载目标识别照片
    virtual void DownloadTargetPhoto(uint32_t deviceNodeId, std::string url, std::string dst, std::shared_ptr<ICompletionListener> listener) = 0;
};

} // namesapce AutelMobileSdk

#endif
