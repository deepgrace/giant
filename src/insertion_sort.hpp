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
void insertion_sort(vector<T>& A)
{
    for (int i = 1; i < A.size(); ++i)
    {
         auto& key = A[i];
         int j = i - 1;
         while (j > -1 && A[j] > key)
         {
                A[j+1] = A[j];
                --j;
         }
         A[j+1] = key;
    }
}
