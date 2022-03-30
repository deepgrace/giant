# Giant [![LICENSE](https://img.shields.io/github/license/deepgrace/giant.svg)](https://github.com/deepgrace/giant/blob/master/LICENSE_1_0.txt)

> **Algorithms and Data Structures in Modern C++**

## Overview

## permutation
```cpp
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
```

## combination
```cpp
#include <algorithm>

template <typename Iterator>
bool combination(Iterator first1, Iterator last1, Iterator first2, Iterator last2, bool ASC)
{
    if (first1 == last1 || first2 == last2)
          return false;

    Iterator m1 = last1;
    Iterator m2 = last2;
    --m2;

    auto comp = [ASC](const auto& x, const auto& y){ return ASC ? x < y : x > y; };

    while (--m1 != first1 && !comp(*m1, *m2));

    bool result = m1 == first1 && !comp(*first1, *m2);
    if (! result)
    {
        while (first2 != m2 && !comp(*m1, *first2))
               ++first2;

        first1 = m1;
        std::iter_swap(first1, first2);
        ++first1;
        ++first2;
    }

    if (first1 != last1 && first2 != last2)
    {
        m1 = last1; 
        m2 = first2;

        while (m1 != first1 && m2 != last2)
        {
               std::iter_swap(--m1 , m2);
               ++m2;
        }

       std::reverse(first1, m1);
       std::reverse(first1, last1);
       std::reverse(m2, last2);
       std::reverse(first2, last2);
    }
    return !result;
}

template <typename Iterator>
bool next_combination(Iterator first, Iterator middle, Iterator last)
{
    return combination(first, middle, middle, last, true);
}

template <typename Iterator>
bool prev_combination(Iterator first, Iterator middle, Iterator last)
{
    return combination(first, middle, middle, last, false);
}
```
