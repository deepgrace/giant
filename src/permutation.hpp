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

template <typename T>
bool next_permutation(vector<T>& A)
{
    int k = A.size() - 1;
    while (k > 0 && A[k-1] >= A[k])
           --k;
    if (k == 0)
        return false;

    swap(*find_if(A.rbegin(), A.rend(), [&](auto t){ return t > A[k-1]; }), A[k-1]);
    reverse(A.begin() + k, A.end());

    return true;
}

template <typename T>
bool prev_permutation(vector<T>& A)
{
    int k = A.size() - 1;
    while (k > 0 && A[k-1] <= A[k])
           --k;
    if (k == 0)
        return false;

    swap(*find_if(A.rbegin(), A.rend(), [&](auto t){ return t < A[k-1]; }), A[k-1]);
    reverse(A.begin() + k, A.end());

    return true;
}

template <typename T>
bool next_partial_permutation(vector<T>& A, int k)
{
   reverse(A.begin() + k, A.end());
   return next_permutation(A);
} 

template <typename T>
bool prev_partial_permutation(vector<T>& A, int k)
{
   bool result = prev_permutation(A);
   reverse(A.begin() + k, A.end());
   return result;
} 
