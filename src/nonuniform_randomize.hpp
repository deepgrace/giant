//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <limits>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
T& nonuniform_randomize(const vector<T>& A, const vector<double>& P)
{
    vector<double> prefix_sum;
    prefix_sum.emplace_back(0.0);
    partial_sum(P.cbegin(), P.cend(), back_inserter(prefix_sum));
    default_random_engine seed(random_device()());
    double uniform_zero_one = generate_canonical<double, numeric_limits<double>::digits>(seed);
    int k = distance(prefix_sum.cbegin(), upper_bound(prefix_sum.cbegin(), prefix_sum.cend(), uniform_zero_one)) - 1;
    return A[K];
}
