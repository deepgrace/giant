//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
void select_sort(vector<T>& vec)
{
    for (int j = 0; j != vec.size() - 1; ++j)
    {
         int k = j;
         for (int i = j+1; i < vec.size(); ++i)
              if (vec[k] > vec[i])
                  k = i;
         swap(vec[k], vec[j]);
    }
}
