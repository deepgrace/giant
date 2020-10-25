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
#include <iostream>
using namespace std;

template <typename T>
int cut_rod(vector<T>& p, int n)
{
    if (n == 0)
        return 0;
    int q = 0;
    for (int i = 0; i != n; ++i)
         q = max(q, p[i] + cut_rod(p, n - i));
    return q;
}

template <typename T>
int memoized_cut_rod_aux(vector<T>& p, int n, vector<T>& r)
{
    if (r[n] >= 0)
        return r[n];
    int q ;
    if (n == 0)
        q = 0;
    else
    {
        q = -1;
        for (int i = 0; i != n; ++i)
             q = max(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
    }
    r[n] = q;
    return q;
}   

template <typename T>
int memoized_cut_rod(vector<T>& p, int n)
{
    vector<T> r(n+1, -1);
    return memoized_cut_rod_aux(p, n, r);
}

template <typename T>
int buttom_up_cut_rod(vector<T>& p, int n)
{
    vector<T> r(n + 1);
    r[0] = 0;
    for (int j = 0; j != n; ++j)
    {
         int q = -1;
         for (int i = 0; i <= j; ++i)
              q = max(q, p[i] + r[j-i]);
         r[j] = q;
    }
    return r[n];
}

template <typename T>
tuple<vector<T>, vector<T>> extended_buttom_up_cut_rod(vector<T>& p, int n)
{
    vector<T> r(n + 1);
    vector<T> s(n + 1);
    r[0] = 0;
    for (int j = 0; j != n; ++j)
    {
         int q = -1;
         for (int i = 0; i <= j; ++i)
         {
              auto revenue = p[i] + r[j - i];
              if (q < revenue)
              {
                  q = revenue;
                  s[j] = i;
              }
         }
         r[j] = q;
    }
    return { r, s };
}

template <typename T>
void print_cut_rod_solution(vector<T>& p, int n)
{
    vector<T> r(n + 1);
    vector<T> s(n + 1);
    tie(r, s) = extended_bottom_up_cut_rod(p, n);
    while (n > 0)
    {
           cout << s[n] << ' ';
           n -= s[n];
    }
    cout << endl;
}
