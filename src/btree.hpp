//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef BTREE_HPP
#define BTREE_HPP
   
#include <memory>
#include <vector>
#include <iostream>

namespace monster
{    
    template <typename T>
    class node : public std::enable_shared_from_this<node<T>>
    {
        public:
            node(int degree_, bool leaf_) : degree(degree_), leaf(leaf_)
            {
                key.reserve(2 * degree -1);
                pointer.reserve(2 * degree);
            }
    
            int find(const T& k)
            {
                int i = 0;
                while (i != size && key[i] < k)
                       ++i;
                return i;
            }
     
            std::pair<std::shared_ptr<node<T>>, int> search(const T& k)
            {
                auto i = find(k);
                if (key[i] == k)
                    return { this->shared_from_this(), i };
                return leaf ? std::make_pair(nullptr, -1) : pointer[i]->search(k);
            }
     
            void insert_nonfull(const T& k)
            {
                int i = size - 1;
                if (leaf)
                {
                    while (i >= 0 && k < key[i])
                    {
                           key[i+1] = key[i];
                           --i;
                    }
                    key[i+1] = k;
                    ++size;
                }
                else
                {
                    while (i >= 0 && k < key[i])
                           --i;
                    if (pointer[i+1]->size == 2 * degree - 1)
                    {
                        split_child(i+1, pointer[i+1]);
                        if (key[i+1] < k)
                            ++i;
                    }
                    pointer[i+1]->insert_nonfull(k);
                }
            }
     
            void split_child(int i, std::shared_ptr<node<T>>& y)
            {
                auto next = std::make_shared<node<T>>(y->degree, y->leaf);
                next->size = degree - 1;
                for (int j = 0; j != degree - 1; ++j)
                     next->key[j] = y->key[j+degree];
                if (! y->leaf)
                    for (int j = 0; j != degree; ++j)
                         next->pointer[j] = std::move(y->pointer[j+degree]);
                y->size = degree - 1;
                for (int j = size; j >= i + 1; --j)
                     pointer[j+1] = std::move(pointer[j]);
                pointer[i+1] = std::move(next);
                for (int j = size - 1; j >= i; --j)
                     key[j+1] = key[j];
                key[i] = y->key[degree-1];
                ++size;
            }
    
            void remove_from_leaf(int i)
            {
                for (int j = i; j != size - 1; ++j)
                     key[j] = key[j+1];
                --size;
            }
     
            T& predecessor(int i)
            {
                auto p = pointer[i];
                while (! p->leaf)
                       p = p->pointer[p->size];
                return p->key[p->size-1];
            }
     
            T& successor(int i)
            {
                auto p = pointer[i+1];
                while (! p->leaf)
                       p = p->pointer[0];
                return p->key[0];
            }
     
            void remove_from_nonleaf(int i)
            {
                auto& k = key[i];
                if (pointer[i]->size >= degree)
                {
                    auto& p = predecessor(i);
                    key[i] = p;
                    pointer[i]->remove(p);
                }
                else if  (pointer[i+1]->size >= degree)
                {
                    auto& s = successor(i);
                    key[i] = s;
                    pointer[i+1]->remove(s);
                }
                else
                {
                    merge(i);
                    pointer[i]->remove(k);
                }
            }
     
            void remove(const T& k)
            {
                int i = find(k);
                if (i < size && key[i] == k)
                {
                    if (leaf)
                        remove_from_leaf(i);
                    else
                        remove_from_nonleaf(i);
                }
                else
                {
                    if (leaf)
                        return;
                    bool last_child = (i == size);
                    if (pointer[i]->size < degree)
                        fill(i);
                    if (last_child && i > size)
                         pointer[i-1]->remove(k);
                    else
                         pointer[i]->remove(k);
                }
            }
    
            void move_prev(int i)
            {
                auto& child = pointer[i];
                auto& prev = pointer[i-1];
                for (int j = child->size; j >= 1; --j)
                     child->key[j] = child->key[j-1];
                child->key[0] = key[i-1];
                if (! child->leaf)
                    for(int j = child->size + 1; j >= 1; --j)
                        child->pointer[j] = std::move(child->pointer[j-1]);
                if (! leaf)
                    child->pointer[0] = std::move(prev->pointer[prev->size]);
                key[i-1] = prev->key[prev->size-1];
                prev->size -= 1;
                child->size += 1;
            }
     
            void move_next(int i)
            {
                auto& child = pointer[i];
                auto& next = pointer[i+1];
                child->key[child->size] = key[i];
                if (! child->leaf)
                    child->pointer[child->size+1] = std::move(next->pointer[0]);
                key[i] = next->key[0];
                for (int j = 0; j != next->size - 1; ++j)
                     next->key[j] = next->key[j+1];
                if (! next->leaf)
                    for(int j = 0; j != next->size; ++j)
                        next->pointer[j] = std::move(next->pointer[j+1]);
                next->size -= 1;
                child->size += 1;
            }
     
            void merge(int i)
            {
                auto& child = pointer[i];
                auto& next = pointer[i+1];
                child->key[degree-1] = key[i];
                for (int j = 0; j != next->size; ++j)
                     child->key[j+degree] = next->key[j];
                if (! child->leaf)
                    for(int j  = 0; j <= next->size; ++j)
                        child->pointer[j+degree] = std::move(next->pointer[j]);
                for (int j = i; j != size -1; ++j)
                {
                     key[j] = key[j+1];
                     pointer[j+1] = std::move(pointer[j+2]);
                }
                --size;
                child->size += next->size+1;
            }
     
            void fill(int i)
            {
                if (i != 0 && pointer[i-1]->size >= degree)
                    move_prev(i);
                else if (i != size && pointer[i+1]->size >= degree)
                    move_next(i);
                else
                    merge(i - (i == size));
            }
     
            void traverse()
            {
                for (int i = 0; i != size; ++i)
                {
                     if (! leaf)
                         pointer[i]->traverse();
                     std::cout << " " << key[i];
                }
                if (! leaf)
                    pointer[size]->traverse();
            }
    
            template <typename U>
            friend class btree;
    
        private:
            bool leaf;
            int degree;
            int size = 0;
            std::vector<T> key;
            std::vector<std::shared_ptr<node<T>>> pointer;
    };
     
    template <typename T>
    class btree
    {
        public:
            btree(int degree_ = 2) : degree(degree_){}
    
            std::pair<std::shared_ptr<node<T>>, int> search(const T& k)
            {
                return (! root) ? std::make_pair(nullptr, -1) : root->search(k);
            }
    
            void insert(const T& k)
            {
                if (! root)
                {
                    root = std::make_shared<node<T>>(degree, true);
                    root->key[0] = k;
                    root->size = 1;
                }
                else
                {
                    if (root->size == 2 * degree-1)
                    {
                        auto new_root =  std::make_shared<node<T>>(degree, false);
                        new_root->pointer[0] = root;
                        new_root->split_child(0, root);
                        int i = (new_root->key[0] < k);
                        new_root->pointer[i]->insert_nonfull(k);
                        root = std::move(new_root);
                    }
                    else
                        root->insert_nonfull(k);
                }
            }
     
            void remove(const T& k)
            {
                if (!root)
                    return;
                root->remove(k);
                if (root->size == 0)
                    root = root->leaf ? nullptr : std::move(root->pointer[0]);
            }
     
            void traverse()
            {
                if (root) 
                    root->traverse();
            }
    
        private:
            int degree;
            std::shared_ptr<node<T>> root;
    };
}

#endif
