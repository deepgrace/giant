//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <vector>
#include <range/v3/all.hpp>

using namespace std;

template <typename T>
T kadane(const vector<T>& v)
{
    return ranges::max(view::partial_sum(v, [](auto s, auto vi) { return std::max(s+vi, vi); }));
}

