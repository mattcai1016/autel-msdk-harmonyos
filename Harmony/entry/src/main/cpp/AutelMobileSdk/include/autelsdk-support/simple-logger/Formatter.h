// Copyright(c) 2023-present, Dreams Chen.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FORMATTER_H
#define FORMATTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <type_traits>

#ifdef HAS_STD_FORMAT
#include <format>
#include <concepts>
#else
#include <string>
#include <sstream>
#endif

#include "Common.h"

namespace simple_logger
{

#ifdef HAS_STD_FORMAT

#define FORMAT std::format

    template <typename T>
    concept EnumType = std::is_enum_v<T>;

    template <EnumType EnumValue, typename CharType>
    struct std::formatter<EnumValue, CharType> : std::formatter<int, CharType>
    {
        template <typename FormatContext>
        typename FormatContext::iterator format(const EnumValue& v, FormatContext& formatContext)
        {
            typename FormatContext::iterator itr = std::formatter<int, CharType>().format(static_cast<int>(v), formatContext);
            return itr;
        }
    };


#else

#define FORMAT simple_logger::format

    AUTELSDK_API void FormatExpand(std::stringstream& s, const char* fmt);

    template<typename T, typename = typename std::enable_if<std::is_enum_v<T>>::type>
    inline std::stringstream& operator<<(std::stringstream& ss, T& value)
    {
        ss << static_cast<int>(value);
        return ss;
    }

    template<typename T, typename... Args>
    AUTELSDK_API void FormatExpand(std::stringstream& ss, const char* fmt, T& value, Args... args)
    {
        while (*fmt) {
            // 处理参数打印
            if (*fmt == '{' && *(++fmt) == '}') {
                ss << value;
                FormatExpand(ss, ++fmt, args...);
                return;
            }

            ss << *fmt++;
        }

#ifndef NDEBUG
        // 调试版本抛出异常，Release版本不抛异常
        throw std::logic_error("Invalid formatting: too much arguments are provided to format");
#endif
    }

    template<typename ... Args>
    AUTELSDK_API std::string format(const char* fmt, Args ... args)
    {
        std::stringstream ss;
        FormatExpand(ss, fmt, args...);
        return ss.str();
    }

#endif
}
#endif // !FORMATTER_H
