//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <vector>
#include <algorithm>
using namespace std;

int parent(int i)
{
    return i / 2 - 1;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * (i + 1);
}

template <typename T>
void max_heapify(vector<T>& A, int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int largest = 0;
    if (l <= heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if (r <= heap_size && A[r] > A[largest])
        largest = r;
    if (largest != i)
    {
        swap(A[i], A[largest]);
        max_heapify(A, largest, heap_size);
    }
}   

template <typename T>
void build_max_heap(vector<T>& A)
{  
    int heap_size = A.size() - 1;
    for (int i = heap_size / 2; i >= 0; --i)
         max_heapify(A, i, heap_size);
}

template <typename T>
void heap_sort(vector<T>& A)
{
    int heap_size = A.size() - 1;
    build_max_heap(A);
    for (int i = heap_size; i >= 1; --i)
    {
         --heap_size;
         swap(A[i], A[0]);
         max_heapify(A, 0, heap_size);
    }
}
