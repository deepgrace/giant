//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <vector>
using namespace std;

template <typename T>
T majority_search(const vector<T>& v)
{
    int i = 0;
    int j = 0;
    for (int k = 0; k != v.size(); ++k)
    {
         if (i == 0)
         {
             i = 1;
             j = k;
         }
         else if (v[k] == v[j])
             ++i;
         else
             --i;
    }

    return v[j];
}
