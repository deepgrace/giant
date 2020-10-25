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
using namespace std;

inline string encode(const string& s)
{
    string result;
    for (int i = 1, count = 1; i <= s.size(); ++i)
    {
         if (i == s.size() || s[i] != s[i-1])
         {
             result += to_string(count) + s[i-1];
             count = 1;
         }
         else
             ++count;
    }
    return result;
}

inline string decode(const string& s)
{
    int count = 0;
    string result;
    for (const char& c: s)
    {
         if (isdigit(c))
             count = count * 10 + c - '0';
         else
         {
             result.append(count, c);
             count = 0;
         }
    }
    return result;
}
