//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef CRC32_HPP
#define CRC32_HPP

#include <sstream>
#include <boost/crc.hpp>
#include <to_buffer.hpp>

std::string to_crc32(const std::vector<char>& buffer)
{
    boost::crc_32_type  result;
    result.process_bytes(buffer.data(), buffer.size());
    std::ostringstream oss;
    oss << std::hex << std::uppercase << result.checksum();
    return oss.str();
}

std::string to_crc32(const std::string& file)
{
    auto buffer = to_buffer(file);
    return to_crc32(buffer);
}

#endif
