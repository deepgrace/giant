//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <string>
#include <algorithm>

void reverse_words(std::string& s)
{
    std::reverse(s.begin(), s.end());
    size_t start = 0;
    size_t end = 0;

    while ((end = s.find(" ", start)) != std::string::npos)
    {
           reverse(s.begin() + start, s.begin() + end);
           start = end + 1;
    }

    std::reverse(s.begin() + start, s.end());
}
