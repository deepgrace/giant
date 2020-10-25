//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <vector>
#include <random>
#include <algorithm>
using namespace std;

template <typename T>
int partition(vector<T>& A, int p, int r)
{
    random_device rand;
    int k = rand() % (r - p + 1) + p;
    swap(A[k], A[r]);

    auto& x = A[r];
    int i = p - 1;
    for (int j = p; j != r; ++j)
         if (A[j] <= x)
             swap(A[++i], A[j]);
    swap(A[++i], A[r]);
    return i;
}
