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

vector<vector<int>> pascal_triangle(int row)
{
    vector<vector<int>> triangle;
    for (int i = 0; i < row; ++i)
    {
         vector<int> curr;
         for (int j = 0; j <= i; ++j)
              curr.emplace_back(0 < j && j < i ? triangle.back()[j-1] + triangle.back()[j] : 1);
         triangle.emplace_back(curr);
    }

    return triangle;
}
