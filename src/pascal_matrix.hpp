//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <vector>
using namespace std;

vector<vector<int>> pascal_matrix(int n)
{
    vector<vector<int>> matrix(n, vector<int>{});

    for (int i = 0; i != n; ++i)
         matrix[i].assign(n, 0);

    for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
              matrix[i][j] = i && j ? matrix[i][j - 1] + matrix[i - 1][j] : 1;

    return matrix;
}
