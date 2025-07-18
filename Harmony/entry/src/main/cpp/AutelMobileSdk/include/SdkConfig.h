#ifndef SDK_CONFIG_H
#define SDK_CONFIG_H

// 自动生成的信息，请勿手动修改
#include <string>

#define MSDK_NAME_SPACE AutelMobileSdk

#define MSDK_VERSION_MAJOR 1
#define MSDK_VERSION_MINOR 0
#define MSDK_VERSION_PATCH 6
#define MSDK_VERSION_BUILD 167

#define MSDK_VERSION_STRING "1.0.6"
#define MSDK_VERSION_FULL_STRING "1.0.6.167"

#define MSDK_FFMPEG_ENABLE 0
#define MSDK_NEST_DEVICE 1

namespace AutelMobileSdk
{

class SdkConfig
{
public:
    static bool isSingle() {                                            // 是否单机
    	if (isJoytickMultiMode())
        {
            return false;
        }
    	return false;
    }
    static bool isRunOnDrone(){ return false;}                          // 是否在飞机上运行
    static bool isDragonFishRC97(){ return false;}                      // 是否龙鱼97遥控器
    static bool isGwNestDock(){ return false;}                          // 是否国网工控机盒子
    static const std::string GetVersion(){ return MSDK_VERSION_STRING;} // 版本号
    static const std::string GetFullVersion(){ return MSDK_VERSION_FULL_STRING;} // 构建版本号
    static int GetLocalDeviceType();                                    //  本地设备类型 

private:
    static bool isJoytickMultiMode();
};


} // namespace AutelMobileSdk

#endif // SDK_CONFIG_H
