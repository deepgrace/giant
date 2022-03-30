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

template <typename T>
T& get(vector<vector<T>>& A, const pair<int, int>& p)
{
    return A[p.first][p.second];
}

template <typename T>
decltype(auto) make_indices(const vector<vector<T>>& A)
{
    int n = 0;
    for (const auto& v : A)
         n += v.size();

    vector<pair<int, int>> indices(n);

    for (int k = 0, i = 0; i != A.size(); ++i)
         for (int j = 0; j != A[i].size(); ++j)
              indices[k++] = std::make_pair(i, j);

    return indices;
}

template <typename T>
int partition(vector<vector<T>>& A, int p, int r, const vector<pair<int, int>>& index)
{
    random_device rand;
    int k = rand() % (r - p + 1) + p;

    swap(get(A, index[k]), get(A, index[r]));

    auto& x = get(A, index[r]);
    int i = p - 1;
    for (int j = p; j != r; ++j)
         if (get(A, index[j]) <= x)
             swap(get(A, index[++i]), get(A, index[j]));

    swap(get(A, index[++i]), get(A, index[r]));

    return i;
}
