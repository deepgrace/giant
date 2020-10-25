//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <iostream>
using namespace std;

template <typename T>
struct node
{
    T key;
    node* p;
    node* left;
    node* right;
};

template <typename T>
void inorder_tree_walk(node<T>*& x)
{
    if (x)
    {
        inorder_tree_walk(x->left);
        cout << x->key << " ";
        inorder_tree_walk(x->right);
    }
}

template <typename T>
void preorder_tree_walk(node<T>*& x)
{
    if (x)
    {
        cout << x->key << " ";
        preorder_tree_walk(x->left);
        preorder_tree_walk(x->right);
    }
}

template <typename T>
void postorder_tree_walk(node<T>*& x)
{
    if (x)
    {
        postorder_tree_walk(x->left);
        postorder_tree_walk(x->right);
        cout << x->key << " ";
    }
}

template <typename T>
node<T>* tree_search(node<T>*& x, T k)
{
    if (x == nullptr || k == x->key)
        return x;
    return k < x->key ? tree_search(x->left, k) : tree_search(x->right, k);
}

template <typename T>
node<T>* iterative_tree_search(node<T>* x, T k)
{
    while (x != nullptr && k != x->key)
           x = k < x->key ? x = x->left : x->right;
    return x;
}

template <typename T>
node<T>* tree_minimum(node<T>* x)
{
    while (x->left != nullptr)
           x = x->left;
    return x;
}

template <typename T>
node<T>* min_tree(node<T>*& x)
{
    if (x->left == nullptr)
        return x;
    return min_tree(x->left);
}

template <typename T>
node<T>* tree_maxmum(node<T>* x)
{
    while (x->right != nullptr)
           x = x->right;
    return x;
}

template <typename T>
node<T>* max_tree(node<T>*& x)
{
    if (x->right == nullptr)
        return x;
    return max_tree(x->right);
}

template <typename T>
node<T>* tree_successor(node<T>* x)
{
    if (x->right != nullptr)
        return tree_minimum(x->right);
    node<T>* y = x->p;
    while (y != nullptr && x == y->right)
    {
           x = y;
           y = y->p;
    }
    return y;
}

template <typename T>
node<T>* tree_predecessor(node<T>* x)
{
    if (x->left != nullptr)
        return tree_maxmum(x->left);
    node<T>* y = x->p;
    while (y != nullptr && x == y->left)
    {
           x = y;
           y = y->p;
    }
    return y;
}

template <typename T>
void tree_insert(node<T>*& root, node<T>*&& z)
{
    node<T>* x = root;
    node<T>* y = nullptr;

    while (x != nullptr)
    {
           y = x;
           x = z->key < x->key ? x->left : x->right;
    }
    z->p = y;
    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}     

template <typename T>
void transplant(node<T>*& root, node<T>*& u, node<T>*& v)
{
    if (u->p == nullptr)
        root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if (v != nullptr)
        v->p = u->p;
}

template <typename T>
void tree_delete(node<T>*& root, node<T>*&& z)
{
    if (z->left == nullptr)
        transplant(root, z, z->right); 
    else if (z->right == nullptr)
        transplant(root, z, z->left);
    else
    {
        auto y = tree_minimum(z->right);
        if (y->p != z)
        {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->p = y;
    }
}
