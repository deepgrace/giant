//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

inline short parity(unsigned long x)
{
    short result = 0;
    while (x)
    {
        result ^= 1;
        x &= x - 1;
    }
    return result;
}
