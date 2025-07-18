#ifndef ENUM_NAME_CONVERTER_H
#define ENUM_NAME_CONVERTER_H

#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <optional>
#include <sstream>
#include <functional>
#include <any>
#include <memory>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif

#ifdef _WIN32
#include "Formatter.h"
#else
#include <autelsdk-support/simple-logger/Formatter.h>
#endif

#include "ErrorCode.h"
#include "BaseType.h"
#include "CameraBaseType.h"
#include "MsgType.h"
#include "Common.h"

namespace AutelMobileSdk
{
#define CASE(_code) \
    case _code: { \
        std::string name(#_code); \
        return name.substr(name.find_last_of(':') + 1);\
    }

#define DEFAULT(_value) \
    default: \
        return FORMAT("Unknow({})", _value);

AUTELSDK_API std::string AutelStatusCodeToString(AutelStatusCode errorCode);
AUTELSDK_API std::string AutelStatusCodeToString(uint32_t errorCode);
AUTELSDK_API std::string GetChineseKeyName(const std::string& key);
AUTELSDK_API std::string GetModuleName(SdkModule module);
AUTELSDK_API std::string GetGimbalTypeName(GimbalType gimbalType);
AUTELSDK_API std::string GetLensTypeName(LensType lensType);
AUTELSDK_API std::string GetMessageTypeName(MessageType msgType);
AUTELSDK_API std::string GetParameterTypeName(ParameterType paramType);

AUTELSDK_API GimbalType GetGimbalTypeByName(const std::string& gimbalTypeName);
AUTELSDK_API LensType GetLensTypeByName(const std::string& lensTypeName);
}
#endif
