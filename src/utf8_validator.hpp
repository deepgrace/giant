//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef UTF8_VALIDATOR_HPP
#define UTF8_VALIDATOR_HPP

#include <string>
#include <cstdint>

namespace utf8_validator
{
    static unsigned int const utf8_valid = 0;
    static unsigned int const utf8_invalid = 1;

    static uint8_t const utf8_decode_table[] = 
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f
        7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf
        8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df
        0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef
        0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff
        0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2
        1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4
        1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6
        1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8
    };

    inline uint32_t decode(uint32_t* state, uint32_t* codepoint, uint8_t byte) 
    {
        uint32_t type = utf8_decode_table[byte];
        *codepoint = (*state != utf8_valid) ? (byte & 0x3fu) | (*codepoint << 6) : (0xff >> type) & byte;
        *state = utf8_decode_table[256 + *state * 16 + type];
        return *state;
    }

    class validator 
    {
        public:
            validator(){}

            bool consume(uint8_t byte)
            {
                return decode(&state, &codepoint, byte) != utf8_invalid;
            }

            template <typename T>
            bool decode(T begin, T end) 
            {
                for (auto it = begin; it != end; ++it) 
                     if (! consume(static_cast<uint8_t>(*it)))
                         return false;
                return true;
            }

            void reset()
            {
                codepoint = 0;
                state = utf8_valid;
            }

        private:
            uint32_t codepoint = 0;
            uint32_t state = utf8_valid;

    };

    inline bool validate(const std::string& s)
    {
        return validator().decode(s.begin(), s.end());
    }
}

#endif
