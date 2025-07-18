#ifndef RTK_KEY_DATA_TYPE_H
#define RTK_KEY_DATA_TYPE_H

#include <string>
#include <cstdint>
#include "KeyValueBaseType.h"
#include "BaseType.h"
#include "Common.h"

namespace AutelMobileSdk
{

struct AUTELSDK_API RtkWorkModeCommand
{
   uint32_t workMode;   //工作模式 0.自定位模式，1.设定坐标模式,(参数经度、纬度、高度)，2.移动模式，3.流动站模式
   double latitude; //经度
   double longitude; //纬度
   double altitude; //高度

   std::string ToString() const;
};


struct AUTELSDK_API RtkRtcmData
{
    int32_t rtcmSource;  //RTCM数据来源，取值参见： 23.16 RTK数据源类型
    int32_t rtcmPackageSerial;  //rtcm数据包的序号（一个rtcm包可能被拆分成多个子包进行网络传输，多个子包的序号相同）
    int32_t rtcmPackageCnt;  //rtcm数据的拆包数量
    int32_t rtcmPackageIdx;  //rtcm数据子包id
    std::string rtcmData;  //RTCM数据，RTCM数据最大长度1029字节，单个子包最大长度500字节

    std::string ToString() const;
};

struct AUTELSDK_API RtkReportInfo
{
   int32_t solState;        //解状态，参见FlightControlDefine->RTK_SOLUTION_TYPE
   int32_t posType;         //位置类型， ,参见FlightControlDefine->RTK_POSITION_TYPE
   double lat;            //纬度，deg
   double lon;            //经度，deg
   double hgt;            //海拔高，m
   float latSigma;        //纬度标准差
   float lonSigma;        //经度标准差
   float hgtSigma;        // 高度标准差 
   int32_t svCnt;           //跟踪的卫星数
   int32_t solnSVs;        // 在解中使用的卫星数
   int32_t gpsCnt;         // GPS卫星数
   int32_t beidouCnt;      // 北斗卫星数
   int32_t glonassCnt;     //glonass卫星数
   int32_t galileoCnt;     //galileo卫星数
   int32_t inPos;           //RTK是否在位 0 -- 不在位， 1 -- 在位
   int32_t rtkUsed;        // 是否使用RTK定位 0 -- 不使用， 1 -- 使用
   int32_t fixSta;         // fix状态 0 -- 未fix， 1 -- 已fix
   int32_t locationType;   // 定位方式 0 -- GNSS， 1 -- RTK
   int32_t signalType;     // RTK信号类型,取值参见： 23.16 RTK数据源类型
   int32_t coordinateSys;  //RTK坐标系统,参见FlightControlDefine->RTK_COORDINATE

   std::string ToString() const;
};

struct AUTELSDK_API RtkGpggaInfo
{
    int32_t gpggaPackageCnt;  //gpgga数据的拆包数量
    int32_t gpggaPackageIdx;  //gpgga数据子包id
    std::string gpggaData;  //gpgga数据

    std::string ToString() const;
};

struct AUTELSDK_API RtkRawInfo
{
    int64_t timestamp;  //系统时间戳
    int32_t gpsTime;  //gps时间
    double lattitude;  //纬度，精度为 10E-7 度
    double longitude;  //经度，精度为 10E-7 度
    float altitude;  //高度(相对海平面)，精度为 10E-3 米
    float velNedX;  //x速度，精度为 10E-3 m/s
    float velNedY;  //y速度，精度为 10E-3 m/s
    float velNedZ;  //z速度，精度为 10E-3 m/s
    float accuracyH;  //水平精度，单位： 10E-3 m
    float accuracyV;  //垂直精度，单位： 10E-3 m
    float accuracyS;  //速度精度，单位： 10E-3 m/s
    int32_t fixType;  //GNSS fix type 0: no fix 1: dead reckoning only 2: 2D fix 3: 3D fix 4: GNSS + Dead Reckoning 5: Time only Fix
    int32_t satellitesNum;  //搜星数量

    std::string ToString() const;
};

} // namespace AutelMobileSdk

#endif // RTK_KEY_DATA_TYPE_H

