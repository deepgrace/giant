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

template <typename T>
using matrix = vector<vector<T>>;

template <typename T>
matrix<T> multiply(matrix<T>& A, matrix<T>& B)
{
    int row = A.size();
    int col = B[0].size();
    matrix<T> C(row, vector<T>{});
    for (int i = 0; i != row; ++i)
         C[i].assign(col, T());
    for (int i = 0; i != row; ++i)
         for(int j = 0; j != col; ++j)
             for(int k = 0; k != B.size(); ++k)
                 C[i][j] += A[i][k] * B[k][j];
    return C;
}
