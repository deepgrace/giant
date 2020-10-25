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
void bubble_sort(vector<T>& A)
{
    for (int i = 0; i < A.size() - 1; ++i)
         for (int j = A.size() - 1; j > i; --j)
              if (A[j] < A[j-1])
                  swap(A[j], A[j-1]);
}
