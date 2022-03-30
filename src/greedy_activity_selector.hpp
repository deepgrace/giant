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
vector<T> greedy_activity_selector(const vector<T>& s, const vector<T>& f, vector<T>& a)
{
   int n = s.size();
   vector<T> A;
   A.push_back(a[0]);
   int k = 0;
   for (int m = 1; m != n; ++m)
   {
        if (s[m] >= f[k])
        {
            A.push_back(a[m]);
            k = m;
        }
   }
   return A;
}
