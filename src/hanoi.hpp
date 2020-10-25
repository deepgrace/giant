//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <stack>
#include <array>
#include <iostream>
using namespace std;

/*
           _                         _                         _
          | |                       | |                       | |
         _| |_                      | |                       | |
        |_____|                     | |                       | |
       |_______|                    | |                       | |
      |_________|                   | |                       | |
     |___________|                  | |                       | |
    |_____________|                 | |                       | |
   |_______________|         _______| |_______         _______| |_______
  |                 |       |                 |       |                 |
 -----------------------------------------------------------------------------
           #0                        #1                        #2
*/

template <typename T>
void hanoi(int n, array<stack<T>, 3>& peg, int from, int to, int use)
{
    if (n > 0)
    {
        hanoi(n - 1, peg, from, use, to);
        peg[to].push(peg[from].top());
        peg[from].pop();
        cout << from << " -> " << to << endl;
        hanoi(n - 1, peg, use, to, from);
    }
}

template <typename T = int>
void move(int n)
{
    array<stack<T>, 3> peg;
    for (int i = n; i > 0; --i)
         peg[0].push(i);
    hanoi(n, peg, 0, 1, 2);
}
