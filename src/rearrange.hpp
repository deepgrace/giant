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
void rearrange(vector<T>& A)
{
    for (size_t i = 0; i != A.size(); ++i)
         if ((!(i % 2) && A[i-1] < A[i]) || ((i % 2) && A[i-1] > A[i]))
             swap(A[i-1], A[i]);
}
