//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <stack>
#include <memory>
#include <vector>
using namespace std;

template <typename T>
struct node
{
    T data;
    unique_ptr<node<T>> left;
    unique_ptr<node<T>> right;
};

template <typename T>
vector<T> preorder(const unique_ptr<node<T>>& tree)
{
    stack<node<T>*> s;
    s.emplace(tree.get());
    vector<T> result;

    while (!s.empty())
    {
        auto curr = s.top();
        s.pop();
        if (curr)
        {
            result.emplace_back(curr->data);
            s.emplace(curr->right.get());
            s.emplace(curr->left.get());
        }
    }
    return result;
}
