//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <iostream>
#include <node.hpp>
using namespace std;

enum rb_color
{
    red,
    black
};

template <typename T>
void left_rotate(node<T>*& root, node<T>*&& x)
{
    node<T>* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->p = x;
    y->p = x->p;
    if (x->p == nullptr)
        root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

template <typename T>
void right_rotate(node<T>*& root, node<T>*&& y)
{
    node<T>* x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
        x->right->p = y;
    x->p = y->p;
    if (y->p == nullptr)
        root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    x->right = y;
    y->p = x;
}

template <typename T>
void rb_insert(node<T>*& root, node<T>*&& z)
{
    tree_insert(root, z);
    z->left = nullptr;
    z->right = nullptr;
    z->color = red;
    rb_insert_fixup(root, z);
}

template <typename T>
void rb_insert_color(node<T>*&& z, int i)
{
    node<T>* d = i ? z->p->left : z->p->right;
    node<T>* y = i ? z->p->p->left : z->p->p->right;
    if (y->color == red)
    {
        z->p->color = black;
        y->color = black;
        z->p->p->color = red;
        z = z->p->p;
    }
    else 
    {
        if (z == d)
        {
            z = z->p;
            left_rotate(root, z);
        }
        z->p->color = black;
        z->p->p->color = red;
        right_rotate(root, z->p->p);
    }
}
 
template <typename T>
void rb_insert_fixup(node<T>*& root, node<T>*&& z)
{
    while (z->p->color == red)
           rb_insert_color(z, z->p == z->p->p->left ? 0 : 1);
    root->color = black;
}

template <typename T>
void rb_delete_fixup(node<T>*& root, node<T>*&& x)
{
    while (x != root && x->color == black)
    {
           if (x == x->p->left)
           {
               node<T>* w = x->p->right;
               if (w->color == red)
               {
                   w->color = black;
                   x->p->color = red;
                   left_rotate(root, x->p);
                   w = x->p->right;
               }
               if (w->left->color == black && w->right->color == black)
               {
                   w->color = red;
                   x = x->p;
               }                
               else 
               {
                   if (w->right->color == black)
                   {
                       w->left->color = black;
                       w->color = red;
                       right_rotate(root, w);
                       w = x->p->right;
                   }
                   w->color = x->p->color;
                   x->p->color = black;
                   w->right->color = black;
                   left_rotate(root, x->p);
                   x = root;
               }
           }
           else
           {
               node<T>* w = x->p->left;
               if (w->color == red)
               {
                   w->color = black;
                   x->p->color = red;
                   right_rotate(root, x->p);
                   w = x->p->left;
               }
               if (w->right->color == black && w->left->color == black)
               {
                   w->color = red;
                   x = x->p;
               }                
               else
               {
                  if (w->left->color == black)
                   {
                       w->right->color = black;
                       w->color = red;
                       left_rotate(root, w);
                       w = x->p->left;
                   }
                   w->color = x->p->color;
                   x->p->color = black;
                   w->left->color = black;
                   right_rotate(root, x->p);
                   x = root;
               }
           }
    } 
}

template <typename T>
void rb_delete(node<T>*& root, node<T>*&& z)
{
    node<T>* x;
    node<T>* y = z;
    auto y_orig_color = y->color;
    if (z->left == nullptr)
    {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == nullptr)
    {
        x = z->left;
        transplant(root, z, z->let);
    }   
    else
    {
        y = tree_minimux(z->right);
        y_orig_color = y->color;
        x = y->right;
        if (y->p == z)
            x->p = y;
        else
        {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (y_orig_color == black)
        rb_delete_fixup(root, x);
}
