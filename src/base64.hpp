//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef BASE64_HPP
#define BASE64_HPP

#include <array>
#include <string>

namespace monster 
{
    static const std::string table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    static inline bool is_base64(uint8_t c) 
    {
        return isalnum(c) || c == 43 || c == 47;
    }

    inline std::string base64_encode(const uint8_t* src, size_t len)
    {
        auto conv = [](auto& lhs, auto& rhs){
             lhs[0] = (rhs[0] & 0xfc) >> 2;
             lhs[1] = ((rhs[0] & 0x03) << 4) + ((rhs[1] & 0xf0) >> 4);
             lhs[2] = ((rhs[1] & 0x0f) << 2) + ((rhs[2] & 0xc0) >> 6);
             lhs[3] = rhs[2] & 0x3f;
        };

        std::string dst;
        dst.resize((len + 2) / 3 * 4);
        std::array<uint8_t, 4> quad;
        std::array<uint8_t, 3> triple;

        int i = 0;
        while (len--)
        {
            triple[i++] = *src++;
            if (i == 3)
            {
                conv(quad, triple);
                for (auto j = 0; j != quad.size(); ++j)
                     dst.append(1, table[quad[j]]);
                i = 0;
            }
        }

        if (i)
        {
            for (auto j = i; j != triple.size(); ++j)
                 triple[j] = '\0';
            conv(quad, triple);
            for (auto j = 0; j <= i; ++j)
                 dst.append(1, table[quad[j]]);
            while ((i++ < 3))
                 dst.append(1, '=');
        }

        return dst;
    }

    inline std::string base64_encode(const std::string& src)
    {
        return base64_encode(reinterpret_cast<const uint8_t*>(src.data()), src.size());
    }

    inline std::string base64_decode(const std::string& src)
    {
        auto conv = [](auto& lhs, auto& rhs) {
             lhs[0] = (rhs[0] << 2) + ((rhs[1] & 0x30) >> 4);
             lhs[1] = ((rhs[1] & 0xf) << 4) + ((rhs[2] & 0x3c) >> 2);
             lhs[2] = ((rhs[2] & 0x3) << 6) + rhs[3];
        };

        size_t len = src.size();
        std::string dst;
        dst.resize(len / 4 * 3);
        std::array<uint8_t, 4> quad;
        std::array<uint8_t, 3> triple;

        int i = 0;
        int k = 0;
        while (len-- && (src[k] != '=') && is_base64(src[k]))
        {
            quad[i++] = src[k++];
            if (i == 4) 
            {
                for (auto j = 0; j != 4; ++j)
                     quad[j] = table.find(quad[j]);
                conv(triple, quad);
                for (auto j = 0; j != 3; ++j)
                     dst.append(1, triple[j]);
                i = 0;
            }
        }

        if (i)
        {
            for (auto j = i; j <4; ++j)
                 quad[j] = 0;
            for (auto j = 0; j != 4; ++j)
                 quad[j] = table.find(quad[j]);
            conv(triple, quad);
            for (auto j = 0; j < i - 1; j++)
                 dst.append(1, triple[j]);
        }

        return dst;
    }
}

#endif
