//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <memory>
using namespace std;

template <typename T>
struct list;

template <typename T>
using list_t = shared_ptr<list<T>>;

template <typename T>
struct list
{
    T data;
    list_t<T> next;
};
