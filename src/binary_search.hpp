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
bool binary_search(vector<T>& vec, int l, int r, T&& v)
{    
    if (l > r)
        return false;
    while (l <= r)
    {
        int mid = l + (r -l ) / 2;
        auto& k = vec[mid];
        if (v == k)
            return true;
        if (v < k)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return false;
}
