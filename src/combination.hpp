//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

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
