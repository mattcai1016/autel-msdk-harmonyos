#ifndef UTIL_H
#define UTIL_H

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
#include <atomic>
#include <shared_mutex>
//#include <QImage>
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
#include "SdkApiContext.h"

namespace AutelMobileSdk
{
#ifdef _MSC_VER
#define PATH_SEPERATOR "\\"
#else
#define PATH_SEPERATOR "/"
#endif

#define CASE(_code) \
    case _code: { \
        std::string name(#_code); \
        return name.substr(name.find_last_of(':') + 1);\
    }

#define DEFAULT(_value) \
    default: \
        return FORMAT("Unknow({})", _value);

#define COPY_ARRAY(src, dst) \
    static_assert(std::is_same_v<std::decay<decltype(src[0])>::type, std::decay<decltype(dst[0])>::type>); \
    static_assert((sizeof(dst) / sizeof(dst[0])) >= (sizeof(src) / sizeof(src[0]))); \
    std::copy(src, src + static_cast<int>(sizeof(src) / sizeof(src[0])), dst)

template<typename EnumType, typename = typename std::enable_if<std::is_enum<EnumType>::value>::type>
inline constexpr auto EnumToInt(EnumType t)
{
    return static_cast<int>(t);
}

template <typename EnumType, typename = typename std::enable_if<std::is_enum<EnumType>::value>::type>
inline EnumType IntToEnum(int value)
{
    return static_cast<EnumType>(value);
}

template <typename T>
std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>, AutelStatusCode>
IntToAutelStatusCode(T code)
{
    return static_cast<AutelStatusCode>(code);
}

std::string AutelStatusCodeToString(AutelStatusCode code);
std::string AutelStatusCodeToString(uint32_t code);

template<typename Base, typename Derived>
bool CanDownCast(Base* p)
{
    return dynamic_cast<Derived*>(p) != nullptr;
}

std::string GetChineseKeyName(const std::string& key);
std::string GetModuleName(SdkModule module);
std::string GetGimbalTypeName(GimbalType gimbalType);
GimbalType GetGimbalTypeByName(const std::string& gimbalTypeName);
std::string GetLensTypeName(LensType lensType);
LensType GetLensTypeByName(const std::string& lensTypeName);

float GetLocalTimeZone();
float GetUtcTimeZone();
float GetGmtTimeZone();
float GetTimeZone();
AUTELSDK_API uint64_t GetLocalTimeStamp();
AUTELSDK_API uint64_t GetUtcTimeStamp();
AUTELSDK_API uint64_t GetTimeStamp();
AUTELSDK_API uint64_t GetTickCount(); //获取时间(操作系统启动到当前所经过的毫秒数)

AUTELSDK_API void CreateDir(const std::string& dir);

AUTELSDK_API unsigned char GenerateRandomChar();
AUTELSDK_API std::string GenerateHex(uint32_t len);

inline std::string GetRealTypeName(const char* typeName)
{
#ifdef _MSC_VER
    return typeName;  // MS VC编译器，从typeid(T).name()取出来的名字即为真实类型名字
#else
    // GCC编译器，从typeid(T).name()取出来的名字是变形后的名字，要获取真实类型名字，需要转换
    // abi::__cxa_demangle返回的内存指针是malloc出来的，需要用free释放
    std::unique_ptr<char, std::function<void(char*)>> ptr(abi::__cxa_demangle(typeName, 0, 0, 0), [] (char* ptr) { free(ptr); });
    return ptr.get();
#endif
}

template <typename T>
std::string GetTypeName()
{
    return GetRealTypeName(typeid(T).name());
}

template <typename T>
std::string GetTypeName(const T* value)
{
    return GetRealTypeName(typeid(*value).name());
}

template<typename T>
std::optional<const T*> AnyCast(const std::any& data)
{
    try {
        if (!data.has_value()) {
            return {};
        }

        const T& v = std::any_cast<const T&>(data);
        return &v;  // 返回指针，避免对象拷贝
    } catch (const std::bad_any_cast& e) {
        API_ERROR("Failed to cast from [{}] to [{}], error={}",
            GetRealTypeName(data.type().name()), GetTypeName<T>(), e.what());
        return nullptr;
    }
}

template<typename Key1, typename Key2>
int64_t MakeKeyType(Key1 key1, Key2 key2)
{
    union
    {
        struct
        {
            int key1;
            int key2;
        } data;

        int64_t value;
    } keyType;

    keyType.data.key1 = static_cast<int>(key1);
    keyType.data.key2 = static_cast<int>(key2);

    return keyType.value;
}

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// Unique message map key
struct UniqueMsgKey
{
    int32_t messageType = 0;
    int32_t parameterType = 0;
    int32_t uavComponentType = 0;
    int32_t subUavComponentType = 0;
    int32_t topicId = 0;
    int32_t topicType = 0;
    UniqueMsgKey(int32_t messageType = 0, int32_t parameterType = 0, int32_t uavComponentType = 0, int32_t subUavComponentType = 0, int32_t topicId = 0, int32_t topicType = 0)
        : messageType(messageType), parameterType(parameterType), uavComponentType(uavComponentType), subUavComponentType(subUavComponentType), topicId(topicId), topicType(topicType)
    {
    }

    bool operator==(const UniqueMsgKey& other) const
    {
        return messageType == other.messageType &&
                parameterType == other.parameterType &&
                uavComponentType == other.uavComponentType &&
                subUavComponentType == other.subUavComponentType &&
                topicId == other.topicId &&
                topicType == other.topicType;
    }

    bool operator!=(const UniqueMsgKey& other) const
    {
        return !(*this == other);
    }

    bool operator<(const UniqueMsgKey& other) const
    {
        return std::tie(messageType, parameterType, uavComponentType, subUavComponentType, topicId, topicType) <
                std::tie(other.messageType, other.parameterType, other.uavComponentType, other.subUavComponentType, other.topicId, other.topicType);
    }

    bool operator>(const UniqueMsgKey& other) const
    {
        return std::tie(messageType, parameterType, uavComponentType, subUavComponentType, topicId, topicType) >
                std::tie(other.messageType, other.parameterType, other.uavComponentType, other.subUavComponentType, other.topicId, other.topicType);
    }

    // Add hash function for unordered_map support
    std::size_t GetHash() const
    {
        std::size_t seed = 0;
        hash_combine(seed, messageType);
        hash_combine(seed, parameterType);
        hash_combine(seed, uavComponentType);
        hash_combine(seed, subUavComponentType);
        hash_combine(seed, topicId);
        hash_combine(seed, topicType);
        return seed;
    }
};

// messageListener map key
struct UniqueMapKey
{
    uint32_t objectId = 0;
    UniqueMsgKey msgKey;
    UniqueMapKey() = default;
    UniqueMapKey(uint32_t objectId, UniqueMsgKey msgKey)
        : objectId(objectId), msgKey(msgKey)
    {
    }

    bool operator==(const UniqueMapKey& other) const
    {
        return objectId == other.objectId && msgKey == other.msgKey;
    }

    bool operator!=(const UniqueMapKey& other) const
    {
        return !(*this == other);
    }

    bool operator<(const UniqueMapKey& other) const
    {
        return std::tie(objectId, msgKey) < std::tie(other.objectId, other.msgKey);
    }

    bool operator>(const UniqueMapKey& other) const
    {
        return std::tie(objectId, msgKey) > std::tie(other.objectId, other.msgKey);
    }

    // Add hash function for unordered_map support
    std::size_t GetHash() const
    {
        std::size_t seed = 0;
        hash_combine(seed, objectId);
        hash_combine(seed, msgKey.GetHash());
        return seed;
    }
};

// 默认类型为false
template<typename T, typename... Types>
struct IsContainerType
{
    static const bool value = false;
};

// List类型为true
template<typename T, typename... Types>
struct IsContainerType<std::list<T, Types...>>
{
    static const bool value = true;
};

// Vector类型为true
template<typename T, typename... Types>
struct IsContainerType<std::vector<T, Types...>>
{
    static const bool value = true;
};

// deque类型
template<typename T, typename... Types>
struct IsContainerType<std::deque<T, Types...>>
{
    static const bool value = true;
};

// set类型
template<typename T, typename... Types>
struct IsContainerType<std::set<T, Types...>>
{
    static const bool value = true;
};

// multiset类型
template<typename T, typename... Types>
struct IsContainerType<std::multiset<T, Types...>>
{
    static const bool value = true;
};

// map类型
template<typename K, typename V, typename... Types>
struct IsContainerType<std::map<K, V, Types...>>
{
    static const bool value = true;
};

// multimap类型
template<typename K, typename V, typename... Types>
struct IsContainerType<std::multimap<K, V, Types...>>
{
    static const bool value = true;
};

// 定义获取容器类型的模板
template<typename T, typename... Types>
constexpr bool is_container = IsContainerType<T, Types...>::value;

template <typename T, typename std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
inline std::string ToString(const T& t)
{
    return std::to_string(t);
}

template <typename T, typename std::enable_if_t<std::is_enum_v<T>>* = nullptr>
inline std::string ToString(const T& t)
{
    return std::to_string(EnumToInt(t));
}

/*
inline std::string ToString(const QImage& img)
{
    return "";
}
*/
template <typename T, typename std::enable_if_t<std::is_same_v<typename std::decay<T>::type, char*>>* = nullptr>
inline std::string ToString(const T t)
{
    return std::string(t);
}

template <typename T, typename std::enable_if_t<std::is_same_v<typename std::decay<T>::type, const char*>>* = nullptr>
inline std::string ToString(const T t)
{
    return std::string(t);
}

template <typename T, typename std::enable_if_t<std::is_same_v<typename std::decay<T>::type, std::string>>* = nullptr>
inline std::string ToString(const T& t)
{
    return t;
}

template <typename T, typename std::enable_if_t<is_container<T>>* = nullptr>
inline std::string ToString(const T& t)
{
    std::stringstream ss;
    ss << "[";
    for (const auto& value : t) {
        ss << "[" << ToString(value) << "], ";
    }
    ss << "]";

    return ss.str();
}

template <typename T, typename std::enable_if_t<std::is_class_v<T> && !is_container<T> && !std::is_same_v<typename std::decay<T>::type, std::string>>* = nullptr>
inline std::string ToString(const T& t)
{
    return t.ToString();
}

template <typename T>
inline std::string ToString(const std::optional<T>& opt)
{
    return opt.has_value() ? ToString(opt.value()) : "";
}

template <typename T>
inline std::string ToString(const std::any& opt)
{
    if (opt.type() != typeid(T))
    {
        return "ERROR: Type mismatch: " + std::string(typeid(T).name()) + "=>" + opt.type().name();
    }
    return opt.has_value() ? ToString<T>(std::any_cast<T>(opt)) : "";
}

template <typename T>
void DeleteArrayMemory(T* ptr)
{
    delete[] ptr;
}

template <typename T, T min = T(0), T max = std::numeric_limits<T>::max(), typename = std::enable_if_t<std::is_integral_v<T>>>
class AUTELSDK_API SeqGenerator
{
public:
    SeqGenerator() {}
    SeqGenerator(const SeqGenerator&) = delete;
    SeqGenerator(SeqGenerator&&) = delete;
    SeqGenerator& operator=(const SeqGenerator&) = delete;
    SeqGenerator& operator=(SeqGenerator&&) = delete;
    ~SeqGenerator() = default;

public:
    T GetNextSeqNo()
    {
        ++m_seqNo;
        T seqNo = m_seqNo.load();
        if (seqNo < m_max) {
            return seqNo;
        }

        m_seqNo.store(m_min);
        return m_min;
    }

    inline T GetMin() const
    {
        return m_min;
    }

    inline T GetMax() const
    {
        return m_max;
    }

private:
    T m_min = min;
    T m_max = max;
    std::atomic<T> m_seqNo = min;
};

class AUTELSDK_API ObjectIdentifier
{
public:
    static ObjectIdentifier& GetInstance()
    {
        static ObjectIdentifier instance;
        return instance;
    }

    static uint32_t GetNewId(const std::string& name)
    {
        return ObjectIdentifier::GetInstance().GetNextId(name);
    }

    inline uint32_t GetNextId(const std::string& name)
    {
        auto id = m_generator.GetNextSeqNo();
        std::lock_guard<std::shared_mutex> lock(m_objectsLock);
        m_objectNames.insert({ id, name });
        return id;
    }

    inline std::string GetObjectName(uint32_t objectId)
    {
        std::shared_lock<std::shared_mutex> lock(m_objectsLock);
        auto itr = m_objectNames.find(objectId);
        return itr != m_objectNames.end() ? itr->second : "";
    }

    inline void ReleaseObjectId(uint32_t objectId)
    {
        std::lock_guard<std::shared_mutex> lock(m_objectsLock);
        m_objectNames.erase(objectId);
    }

private:
    ObjectIdentifier() = default;
    ObjectIdentifier(const ObjectIdentifier&) = delete;
    ObjectIdentifier(ObjectIdentifier&&) = delete;
    ObjectIdentifier& operator=(const ObjectIdentifier&) = delete;
    ObjectIdentifier& operator=(ObjectIdentifier&&) = delete;
    ~ObjectIdentifier() = default;

private:
    SeqGenerator<uint32_t, 1> m_generator;
    std::shared_mutex m_objectsLock;
    std::unordered_map<uint32_t, std::string> m_objectNames;
};

template <typename T, size_t size = sizeof(T)>
T GetSwappedByteOrderValue(T value)
{
    union
    {
        uint8_t bytes[size];
        T value;
    } data;

    data.value = value;
    for (size_t i = 0; i < size / 2; ++i) {
        swap(data.bytes[i], data.bytes[size - 1 - i]);
    }

    return data.value;
}

template <typename T, size_t size = sizeof(T)>
T GetSwappedByteOrderValue(char* bytes)
{
    union
    {
        uint8_t bytes[size];
        T value;
    } data;

    for (size_t i = 0; i < size; ++i) {
        data.bytes[i] = static_cast<uint8_t>(bytes[size - 1 - i]);
    }

    return data.value;
}

// 基于RAII机制实现的自动资源清理工具类
template <typename Type>
class AUTELSDK_API AutoClean
{
public:
    using Dtor = std::function<void(Type)>;

public:
    AutoClean(Type type, Dtor dtor) : m_type(type), m_dtor(dtor)
    {
    }

    ~AutoClean()
    {
        m_dtor(m_type);
    }

    inline Type Get()
    {
        return m_type;
    }

private:
    Type m_type;
    Dtor m_dtor;
};


} // namespace AutelMobileSdk

// Add hash support for UniqueMapKey to enable its use in unordered_map
namespace std
{
    template<>
    struct hash<AutelMobileSdk::UniqueMsgKey>
    {
        std::size_t operator()(const AutelMobileSdk::UniqueMsgKey& key) const
        {
            return key.GetHash();
        }
    };
}

// Add hash support for UniqueMapKey to enable its use in unordered_map
namespace std
{
    template<>
    struct hash<AutelMobileSdk::UniqueMapKey>
    {
        std::size_t operator()(const AutelMobileSdk::UniqueMapKey& key) const
        {
            return key.GetHash();
        }
    };
}
#endif
