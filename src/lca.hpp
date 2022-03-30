//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <memory>
#include <algorithm>
using namespace std;

template <typename T>
struct node
{
    T data;
    unique_ptr<node<T>> left;
    unique_ptr<node<T>> right;
    unique_ptr<node<T>> parent;
};

template <typename T>
int depth(const node<T>* tree)
{
    int h = 0;
    while (tree->parent)
    {
        ++h;
        tree = tree->parent;
    }
    return h;
}

template <typename T>
node<T>* lca(const unique_ptr<node<T>>& l, const unique_ptr<node<T>>& r)
{
    auto p1 = l.get();
    auto p2 = r.get();

    int h1 = depth(p1);
    int h2 = depth(p2);
    if (h2 > h1)
        swap(p1, p2);

    int diff = abs(h1 - h2);
    while (diff--)
        p1 = p1->parent;

    while (p1 != p2)
    {
        p1 = p1->parent;
        p2 = p2->parent;
    }
    return p1;
}
