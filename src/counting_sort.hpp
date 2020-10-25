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
void counting_sort(const vector<T>& A, vector<T>& B, size_t k)
{
    vector<T> C(k + 1, 0);
    for (auto j = 0; j != A.size(); ++j)
         ++C[A[j]];
    for (auto i = 1; i <= k; ++i)
         C[i] += C[i - 1];
    for (int j = A.size() - 1; j >= 0; --j)
         B[--C[A[j]]] = A[j];
}
