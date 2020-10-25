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
#include <combination_indices.hpp>

int main(int argc, char* argv[])
{
    std::vector<int> v { 0, 1, 2 };
    
    do
    {
        std::cout << "[ " << v[0];
        for (int j = 1; j < v.size(); ++j)
             std::cout << ", " << v[j];
        std::cout << " ] " << std::endl;
    } while (next_combination_indices(v.begin(), v.end(), 0, 9));

    std::cout << std::endl;

    std::vector<int> k { 6, 7, 8 };
    
    do
    {
        std::cout << "[ " << k[0];
        for (int j = 1; j < k.size(); ++j)
             std::cout << ", " << k[j];
        std::cout << " ] " << std::endl;
    } while (prev_combination_indices(k.begin(), k.end(), 0, 9));

    return 0;
}
