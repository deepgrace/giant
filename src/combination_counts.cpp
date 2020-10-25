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
#include <combination_counts.hpp>

int main(int argc, char* argv[])
{
    int r = 2;
    int n = 3;
    std::vector<int> v(n, 0);
    v.back() = r;

    do
    {
        std::cout << "[ " << v[0];
        for (int j = 1; j < n; ++j)
             std::cout << ", " << v[j];
        std::cout << " ]" << std::endl;
    } while (next_combination_counts(v.begin(), v.end()));

    std::cout << std::endl;

    std::vector<int> k(n, 0);
    k.front() = r;

    do
    {
        std::cout << "[ " << k[0];
        for (int j = 1; j < n; ++j)
             std::cout << ", " << k[j];
        std::cout << " ]" << std::endl;
    } while (prev_combination_counts(k.begin(), k.end()));

    return 0;
}
