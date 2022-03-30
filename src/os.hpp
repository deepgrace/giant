//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <node.hpp>

template <typename T>
node<T>* os_select(node<T>*& x, int i)
{
    int rank = x->left->size + 1;
    if (i == rank)
        return x;
    return i < rank ? os_select(x->left, i) : os_select(x->right, i - rank);
}

template <typename T>
int os_rank(node<T>*& root, node<T>*&x)
{
    int r = x->left->size + 1;
    node<T>* y = x;
    while (y != root)
    {
          if (y == y->parent->right)
              r += y->parent->left->size + 1;
          y = y->parent;
    }
    return r;
}
