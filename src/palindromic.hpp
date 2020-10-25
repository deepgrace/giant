//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <string>
using namespace std;

inline bool is_palindromic(const string& s)
{
    for (int i = 0, j = s.size() -1; i < j; ++i, --j)
         if (s[i] != s[j])
             return false;
    return true;
}
