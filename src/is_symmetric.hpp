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
struct node
{
    T data;
    unique_ptr<node<T>> left;
    unique_ptr<node<T>> right;
};

template <typename T>
bool check_symmetric(const unique_ptr<node<T>>& l, const unique_ptr<node<T>>& r)
{
    if (l == nullptr && r == nullptr)
        return true;
    if (l != nullptr && r != nullptr)
        return l->data == r->data && check_symmetric(l->left, r->right) && check_symmetric(l->right, r->left);
    return false;
}

template <typename T>
bool is_symmetric(const unique_ptr<node<T>>& tree)
{
    return tree == nullptr || check_symmetric(tree->left, tree->right);
}
