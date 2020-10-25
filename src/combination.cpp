//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <vector>
#include <iostream>
#include <iterator>
#include <combination.hpp>

int main()
{
    int n = 3;
    std::vector<int> v {1, 2, 3, 4, 5, 6};

    do
    {
        std::cout << "[ " << v[0];
        for (int j = 1; j < n; ++j)
             std::cout << ", " << v[j];
        std::cout << " ]" << std::endl;
    } while (next_combination(v.begin(), v.begin() + n, v.end()));

    std::cout << std::endl;

    std::vector<int> k {1, 2, 3, 4, 5, 6};
    std::reverse(k.begin(), k.end());

    do
    {
        std::cout << "[ " << k[0];
        for (int j = 1; j < n; ++j)
             std::cout << ", " << k[j];
        std::cout << " ]" << std::endl;
    } while (prev_combination(k.begin(), k.begin() + n, k.end()));

    return 0;
}
