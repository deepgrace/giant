//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

inline string to_lower(const string& s)
{
    string lower(s);
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}
