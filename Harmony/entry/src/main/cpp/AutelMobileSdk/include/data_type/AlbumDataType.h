#ifndef ALBUM_DATA_TYPE_H
#define ALBUM_DATA_TYPE_H

#include <string>
#include <vector>

#ifdef _WIN32
#include "Formatter.h"
#else
#include <autelsdk-support/simple-logger/Formatter.h>
#endif
#include "Common.h"

namespace AutelMobileSdk
{

enum class MediaFileType
{
    UNKNOWN = -1,       // 未知文件
    MEDIA_ALL = 0,      // 全部文件
    MEDIA_VIDEO = 1,    // 视频
    MEDIA_PHOTO = 2,    // 照片
};

enum class OrderType
{
    NORMAL = 0,     // 顺序
    REVERSE = 1,    // 倒叙
};

enum class MediaFileSuffix
{
    UNKNOW = -1,
    JPG = 0,
    MOV = 1,
    MP4 = 2,
    M4A = 3,
    DNG = 4
};

struct AUTELSDK_API AutelMediaInfo
{
    int indexId = 0;                         // 序列号
    std::string path;                   // 原图路径  图片和视频存在
    int64_t size = 0;                       // 文件大小原图  图片和视频存在
    std::string name;                       // 文件名  Package表示照片包
    std::string thumbnail;                  // 缩略图路径
    std::string screennail;                 // 预览图路径
    MediaFileSuffix mediaSuffix = MediaFileSuffix::UNKNOW;        // 媒体类型 0 jpg, 1 mov, 2 mp4, 3 m4a, 4 dng 图片和视频存在
    int64_t timestamp = 0;                  // 文件生成UTC时间戳
    int width = 0;                          // 媒体文件宽度  图片和视频存在
    int height = 0;                         // 媒体文件高度  图片和视频存在
    int fps = 0;                            // 如果是视频，则表示帧率视频存在
    std::string codingType;                 // 编码类型 视频存在
    int duration = 0;                       // 视频时长 单位s 视频存在
    int fileType = 0;                       // 文件类型: 0: 无效类型; 1: 渐远短片; 2: 自由延时, 3: 球形全景;
    int encrypted = 0;                      // 0: 未加密; 1: 已加密, 图片和视频存在
    std::vector<AutelMediaInfo> filelist;   // 文件子集合，package
    std::string preview;                    // 视频预览地址
    int cameraType = 0;                     // 0:广角；1:长焦；2:红外；图片和视频存在
    std::string cacheKey;                   // 缓存key

    std::string ToString() const;
};

struct AUTELSDK_API AlbumQueryResult
{
    int result = 0;
    int totalCnt = 0;
    std::vector<AutelMediaInfo> mediaInfoList;

    std::string ToString() const;
};

struct AUTELSDK_API AutelAlbum
{
    int index = 0;
    std::string name;
    std::string thumbnail;
    int count = 0;

    std::string ToString() const;
};

struct AUTELSDK_API AlbumFolderQueryResult
{
    int result = 0;
    std::vector<AutelAlbum> folderList;

    std::string ToString() const;
};


// 定义图像格式枚举
enum class AUTELSDK_API ImageFormat {
    RGB888,    // 3 bytes per pixel
    RGBA8888,  // 4 bytes per pixel
    Grayscale8 // 1 byte per pixel
};


class AUTELSDK_API ImageData {
public:
    ImageData(int width, int height, int bytesPerLine, ImageFormat format, const uint8_t* data);
    // 获取图像基本信息
    int getWidth() const;
    int getHeight() const;
    int getBytesPerLine() const;
    ImageFormat getFormat() const;
    // 获取图像数据
    const uint8_t* getData() const;

    std::string ToString() const;

private:
    int width;           // 图像宽度
    int height;          // 图像高度
    int bytesPerLine;    // 每行字节数
    ImageFormat format;  // 图像格式
    std::vector<uint8_t> data; // 存储图像数据
};

struct AUTELSDK_API AlbumImage
{
    std::string localPath;
    ImageData imageData;
    std::string ToString() const;
};


}  // namespace AutelMobileSdk

#endif
