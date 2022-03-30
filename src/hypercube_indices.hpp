//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

template <typename Iterator, typename T>
bool next_hypercube_indices(Iterator first, Iterator last, T first_value, T last_value)
{
    if (first == last)
        return false;
    do
    {
        if (++(*--last) != last_value)
            return true;
        *last = first_value;
    } while (first != last);

    return false;
}

template <typename Iterator, typename T>
bool prev_hypercube_indices(Iterator first, Iterator last, T first_value, T last_value)
{
    if (first == last)
        return false;
    --last_value;
    do
    {
        if (*--last != first_value)
        {
            --*last;
            return true;
        }
        *last = last_value;
    } while (first != last);

    return false;
}
