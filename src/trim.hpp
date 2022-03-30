//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef TRIM_HPP
#define TRIM_HPP

#include <string>
#include <algorithm>

namespace monster
{
    template <typename T>
    auto quoted_string(T begin, T end)
    {
        std::string s;
        if (begin == end || *begin != '"')
            return std::make_pair(s, begin);
        auto prev = begin + 1;
        auto next = std::find(prev, end, '"');
        while (next != end)
        {
            if (*(next - 1) == '\\')
            {
                s.append(prev, next-1).append(1,'"');
                prev = ++next;
                next = std::find(prev, end, '"');
            } 
            else
            {
                s.append(prev, next);
                return std::make_pair(s, ++next);
            }
        }
        return std::make_pair(std::string(), begin);
    }

    template <typename T>
    auto strip_space(T begin, T end)
    {
        if (end - begin > 2 && *begin == '\r' && *(begin + 1) == '\n' && [c = static_cast<unsigned char>(*(begin + 2))]{ return c == 9 || c == 32; }())
            begin += 3;
        return std::find_if(begin, end, [](unsigned char c){ return c != 9 && c != 32; });
    }

    inline std::string trim(const std::string& s)
    {
        auto begin = strip_space(s.begin(), s.end());
        auto rbegin = strip_space(s.rbegin(), s.rend());
        if (begin == s.end() || rbegin == s.rend())
            return std::string();
        return std::string(begin, rbegin.base());
    }
}

#endif
