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
T smallest_nonconstructible_value(vector<T>& A)
{
    sort(A.begin(), A.end());
    T max_constructible_value = T();
    for (auto& a : A)
    {
         if (a > max_constructible_value + 1)
             break;
         max_constructible_value += a;
    }
    return max_constructible_value;
}
