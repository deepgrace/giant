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
bool matrix_search(const vector<vector<T>>& v, const T& x)
{
    int row = 0;
    int col = v[0].size() - 1;
    while (row < v.size() && col >= 0)
    {
        auto& k = v[row][col];
        if (k == x)
            return true;
        else if (k < x)
            ++row;
        else
            --col;
    }
    return false;
}
