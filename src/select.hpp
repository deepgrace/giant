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
T& select(vector<T>& A, int p, int r, int i)
{
    if (p == r)
        return A[p];
    int q = partition(A, p, r);
    int k = q - p + 1;
    if (i == k)
        return A[q];
    if (i < k)
        return select(A, p, q - 1, i);
    return select(A, q + 1, r, i - k);
}
