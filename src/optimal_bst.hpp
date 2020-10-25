//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <tuple>
#include <limits>
#include <vector>
using namespace std;

typename <typename T>
using matrix = vector<vector<T>>;

template <typename T>
tuple<matrix, matrix> optimal_bst(const vector<T> p, const vector<T> q, int n)
{
    matrix<T> e(n+1, vector<T>{});
    matrix<T> w(n+1, vector<T>{});
    matrix<T> root(n, vector<T>{});
    for (int i = 0; i != n; ++i)
    { 
         e[i].assign(n+1, 0);
         w[i].assign(n+1, 0);
         for (int j = 1; j <= n; ++j)
         {
              e[j][j-1] = q[i-1];
              w[j][j-1] = q[i-1];
         }
         root[i].assign(n, 0);
    }
    e[n].assign(n+1, 0);
    w[n].assign(n+1, 0);
    for (int l = 1; l <= n; ++l)
    {
         for (int i = 1; i <= n - l + 1; ++i)
         {
              int j = i + l - 1;
              e[i][j]= numeric_limits<T>::max();
              w[i][j] = w[i][j-1] + p[j] + q[j];
              for (int r = i ; r <= j; ++r)
              {
                   int t = e[i][r-1] + e[r+1][j] + w[i][j];
                   if (t < e[i][j])
                   {
                       e[i][j] = t;
                       root[i][j] = r;
                   }
              }
         } 
    }
    return { e, root };
}
