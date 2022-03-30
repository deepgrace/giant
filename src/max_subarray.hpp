//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <tuple>
#include <vector>
#include <limits>
using namespace std;

template <typename T>
tuple<int, int, T> find_max_crossing_subarray(const vector<T>& A, int low, int mid, int high)
{
    T left_sum = numeric_limits<T>::min();
    T sum = T();
    int max_left = 0;
    for (int i = mid; i >= low; --i)
    {
         sum += A[i];
         if (sum > left_sum)
         {
             left_sum = sum;
             max_left = i;
         }
    }

    T right_sum = numeric_limits<T>::min();
    sum = T();
    int max_right = 0;
    for (int j = mid + 1; j <= high; ++j)
    {
         sum += A[j];
         if (sum > right_sum)
         {
             right_sum = sum;
             max_right = j;
         }
    }
    return { max_left, max_right, left_sum + right_sum };
}

template <typename T>
tuple<int, int, T> find_maximum_subarray(const vector<T>& A, int low, int high)
{
    if (low == high)
        return { low, high, A[low] };
    auto mid = (low + high) / 2;
    auto [left_low, left_high, left_sum] = find_maximum_subarray(A, low, mid);
    auto [right_low, right_high, right_sum] = find_maximum_subarray(A, mid + 1, high);
    auto [cross_low, cross_high, cross_sum] = find_max_crossing_subarray(A, low, mid, high);
    if (left_sum >= right_sum && left_sum >= cross_sum)
        return { left_low, left_high, left_sum };
    else if (right_sum >= left_sum && right_sum >= cross_sum)
        return { right_low, right_high, right_sum };
    return { cross_low, cross_high, cross_sum };
}

template <typename T>
tuple<int, int, T> max_subarray(const std::vector<T>& A)
{
    T max = A[0];
    T cur = A[0];
    int begin = 0;
    int end = 0;
    int new_begin = 0;
    for (int i = 1; i != A.size(); ++i)
    {    
         if (cur < 0)
         {
             new_begin = i;
             cur = A[i];
         }
         else
             cur += A[i];
         if (cur >= max)
         {
             max = cur;
             begin = new_begin;
             end = i;
        }
    }
    return { begin, end, max };
}
