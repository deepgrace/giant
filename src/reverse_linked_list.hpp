//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <list_node.hpp>

template <typename T>
list_t<T> reverse(list_t<T>& head)
{
    list_t<T> prev = nullptr;
    while (head)
    {
          auto next = head->next;
          head->next = prev;
          prev = head;
          head = next;
    }
    return prev;
}
