//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <tuple>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
using matrix = vector<vector<T>>;

matrix<int> lcs_length(const string& x, const string& y)
{
    auto m = x.size();
    auto n = y.size();

    matrix<int> b(m, vector<int>{});
    matrix<int> c(m + 1, vector<int>{});

    for (auto i = 0; i != m; ++i)
    {
         b[i].assign(n, 0);
         c[i].assign(n + 1, 0);
    }
    c[m].assign(n + 1, 0);

    for (int i = 0; i < m; ++i)
    {
         for (int j = 0; j < n; ++j)
         {
              if (x[i] == y[j])
              {
                  c[i + 1][j + 1] = c[i][j] + 1;
                  b[i][j] = '\\';
              }
              else if (c[i][j + 1] >= c[i + 1][j])
              {
                  c[i + 1][j + 1] = c[i][j + 1];
                  b[i][j] = '|';
              }
              else
              {
                  c[i + 1][j + 1] = c[i + 1][j];
                  b[i][j] = '-';
              }
         }
    }
    return b;
}

void print_lcs(matrix<int>& b, const string& x, int i, int j)
{
    if (i == -1 or j == -1)
        return;
    if (b[i][j] == '\\')
    {
        print_lcs(b, x, i-1, j-1);
        cout << x[i];
    }
    else if (b[i][j] == '|')
        print_lcs(b, x, i-1, j);
    else
        print_lcs(b, x, i, j-1);
}

void lcs(const string& lhs, const string& rhs)
{
     auto b = lcs_length(lhs, rhs);
     std::cout << lhs << std::endl;
     std::cout << rhs << std::endl;
     print_lcs(b, lhs, lhs.size() -1, rhs.size() -1);
     std::cout << std::endl;
}
