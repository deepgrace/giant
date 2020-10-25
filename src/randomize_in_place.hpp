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

random_device rand;

template <typename T>
int randomize_in_place(vector<T>& A)
{
    int n = A.size();
    for (int i = 0; i != n; ++i)
    {
         int k = rand() % (n - i) + i;
         swap(A[i], A[k]);
    }
}
