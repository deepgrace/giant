//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <iostream>
#include <iterator>
#include <permutation.hpp>

int main(int argc, char* argv[])
{
    int n = 4;
    std::vector<int> v { 1, 2, 3, 4};

    do
    {
        std::cout << "[ " << v[0];
        for (int j = 1; j < n; ++j)
             std::cout << ", " << v[j];
        std::cout << " ] " << std::endl;
    } while(next_partial_permutation(v, n));

    std::cout << std::endl;

    std::vector<int> k { 4, 3, 2, 1 };

    do
    {
        std::cout << "[ " << k[0];
        for (int j = 1; j < n; ++j)
             std::cout << ", " << k[j];
        std::cout << " ] " << std::endl;
    } while(prev_partial_permutation(k, n));

    return 0;
}
