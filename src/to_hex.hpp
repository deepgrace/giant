//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <string>

template <typename T>
inline std::string to_hex(const T& c)
{
    std::string dst;
    std::string hex = "0123456789ABCDEF";
    for (auto& v : c)
    {
       auto n = static_cast<uint8_t>(v);
       dst.append(1, hex[(n & 0xF0) >> 4]);
       dst.append(1, hex[n & 0x0F]);
       dst.append(1, ' ');
    }
    return dst;
}
