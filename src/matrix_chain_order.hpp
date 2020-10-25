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
#include <iostream>
using namespace std;

template <typename T>
tuple<vector<T>, vector<T>> matrix_chain_order(const vector<T>& p)
{
    int n = p.size();
    vector<vector<int>> m(n, vector<T>{});
    vector<vector<int>> s(n-1, vector<T>{});
    for (int i = 0; i != n-1; ++i)
    {
         m[i].assign(n, 0);
         s[i].assign(n-1, 0);
    }
    m[n-1].assign(n, 0);
    for (int l = 2; l <= n; ++l)
    {
         for (int i = 1; i <= n - l + 1; ++i)
         {
              int j = i + l - 1;
              m[i][j] = numeric_limits<int>::max();;
              for (int k = i; k != j; ++k)
              {
                   int q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                   if (q < m[i][j])
                   {
                       m[i][j] = q;
                       s[i][j] = k;
                   }
              }
         }
    }
    return { m, s };
}

template <typename T>
void print_optimal_parens(vector<vector<T>>& s, int i, int j)
{
     if (i == j)
         cout << "A" << i;
     else
     {
         cout << "(";
         print_optimal_parens(s, i, s[i][j]);
         print_optimal_parens(s, s[i][j]+1, j);
         cout << ")";
     }
}
