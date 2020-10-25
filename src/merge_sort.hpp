//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <limits>
#include <vector>
using namespace std;

template <typename T>
void merge(vector<T>& A, int p, int q, int r)
{
    int n1 = q - p +1;
    int n2 = r - q;
    vector<T> L(n1 + 1);
    vector<T> R(n2 + 1);
    for (int i = 0; i != n1; ++i)
         L[i] = A[p + i];
    for (int j = 0; j != n2; ++j)
         R[j] = A[q + j + 1];
    L[n1] = numeric_limits<T>::max();
    R[n2] = numeric_limits<T>::max();
    int i = 0;
    int j = 0;
    for (int k = p; k <= r; ++k)
         A[k] = L[i] <= R[j] ? L[i++] : R[j++];
}

template <typename T>
void merge_sort(vector<T>& A, int p, int r)
{
    if (p >= r) 
        return;
    int q = (p + r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q + 1, r);
    merge(A, p, q, r);
}
