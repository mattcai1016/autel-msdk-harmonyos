#ifndef IMAP_BUILDING_H
#define IMAP_BUILDING_H
#include <string>
#include <vector>
#include "BaseType.h"
#include "ErrorCode.h"

namespace AutelMobileSdk
{
//建图功能接口
class IMapBuilding
{
public:

    //建图接口返回值
    enum class ResultCode
    {
        OK = 11000,           //成功
        Cancel = 11001,       //用户中途取消
        FailedInit = 18001,   //初始化实时管理类错误
        FailedCreate = 18002, //无法创建实时2维map对象错误
        FailedFind = 18003,   //找不到实时2维对象错误
    };

    //app回调接口
    class Callback
    {
    public:
        Callback(){}
        virtual ~Callback(){}

        //建图输出日志
        //virtual void OnMapBuildingLog(const std::string& log_json_str) = 0;

        //实时新增瓦块图路径
        virtual void OnMapBuildingNewRealImage(const std::string& path) = 0;

        //建图结束
        virtual void OnMapBuildingEnd(IMapBuilding::ResultCode code, const std::string& result) = 0;

    };

public:
    IMapBuilding(){}
    virtual ~IMapBuilding(){}

public:

    //启动建图
    virtual bool Start(const std::string& outPath, IMapBuilding::Callback* callback) = 0;

    //取消建图
    virtual void Cancel() = 0;

    //添加图片
    virtual void AddImage(const std::string& imagePath) = 0;

    //结束图片输入
    virtual void EndImage() = 0;
};


}

#endif // IMAPBUILDING_H
