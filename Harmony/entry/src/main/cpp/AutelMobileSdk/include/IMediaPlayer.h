#ifndef IMEDIA_PLAYER_H
#define IMEDIA_PLAYER_H

#include <string>
#include "BaseType.h"
#include "IUserRenderer.h"
#include "Common.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IMediaPlayer
{
public:
    IMediaPlayer(int playerId) : m_playerId(playerId) {}
    virtual ~IMediaPlayer() {}

public:
    // ==========参数设置类接口==========
    // 设置文件播放的视频源，即视频文件路径
    virtual void SetMediaSource(const std::string& path) = 0;

    // 设置网络视频源（支持RTSP、RTMP、HTTP、UDP协议视频源）
    virtual void SetMediaSource(MediaSourceType mediaSourceType, const std::string& ip, int port, TransmitProtoType protoType = TransmitProtoType::Udp) = 0;

    // 设置播放无人机设备实时回传视频
    virtual void SetMediaSource(uint32_t deviceId, VideoType videoType) = 0;

    // 设置播放窗口句柄，播放器将视频渲染在指定的窗口上
    // 注意：此接口与SetUserRenderer接口互斥，且需要在StartPlaying之前调用
    virtual void SetDisplayWinHandle(DisplayWinHandle wndHandle) = 0;

    // 设置用户自定义的渲染器，用于QML程序下面的视频渲染，或者其他需要定制渲染器的场景，
    // 注意：此接口与SetDisplayWinHandle互斥，且需要在StartPlaying之前调用
    virtual void SetUserRenderer(IUserRenderer* renderer) = 0;

    // 设置播放无人机回传的视频类型
    virtual void SetVideoType(VideoType videoType) = 0;

    // 设置视频显示模式
    virtual void SetDisplayMode(VideoDisplayMode mode) = 0;

    // ==========播放操作类接口==========
    virtual bool StartPlaying() = 0;
    virtual void StopPlaying() = 0;
    virtual void PausePlaying() = 0;
    virtual void ResumePlaying() = 0;
    virtual bool RequestKeyFrame() = 0;
    virtual void Close() = 0;

    virtual PlayState GetPlayerState() = 0;

    // 视频窗口变化时调用
    virtual void OnWindowResize(int x, int y, int width, int height) = 0;

    // 以下接口暂不支持
    virtual void SeekProgress(int64_t value) = 0;
    virtual void SetVolume(int value) = 0;
    virtual int GetVolume() = 0;
    virtual int64_t GetCurrentTime() = 0;

    int GetPlayerId() const
    {
        return m_playerId;
    }

protected:
    int m_playerId = 0;
};
}

#endif // !_AUTEL_IPLAYER_H_
