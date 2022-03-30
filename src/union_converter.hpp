//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef UNION_CONVERTER_HPP
#define UNION_CONVERTER_HPP

#include <type_traits>

namespace monster
{
    template <typename S, typename D>
    union union_converter
    {
        S s;
        D d[sizeof(S) / sizeof(D)];
    };

    template <typename T>
    constexpr auto to_underlying(T t) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(t);
    }
}

#endif
