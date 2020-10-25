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

inline string replace(string& src, const string& dst, const string& rep)
{
    size_t pos = 0;
    while ((pos = src.find(dst, pos)) != string::npos)
    {
          src.replace(pos, dst.length(), rep);
          pos += rep.length();
    }
    return src;
}
