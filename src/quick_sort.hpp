//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <partition.hpp>

template <typename T>
void quick_sort(vector<T>& A, int p, int r)
{
    if (p >= r)
        return;
    int q = partition(A, p, r);
    quick_sort(A, p, q - 1);
    quick_sort(A, q + 1, r);
}

template <typename T>
void quick_sort(vector<vector<T>>& A, int p, int r, const vector<pair<int, int>>& index)
{
    if (p >= r)
        return;
    int q = partition(A, p, r, index);
    quick_sort(A, p, q - 1, index);
    quick_sort(A, q + 1, r, index);
}

template <typename T>
void quick_sort(vector<T>& A)
{
    quick_sort(A, 0, A.size() - 1);
}

template <typename T>
void quick_sort(vector<vector<T>>& A)
{
    auto index = make_indices(A);
    quick_sort(A, 0, index.size() - 1, index);
}
