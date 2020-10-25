//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#include <ctime>
#include <string>

std::string timestamp()
{
    char date[80];
    timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    tm* timeinfo = localtime(static_cast<time_t*>(&tp.tv_sec));
    strftime(date, 80, "%Y-%m-%d-%H:%M:%S", timeinfo);
    return std::string(date);
}
