//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef ZSTD_HPP
#define ZSTD_HPP
#define ZSTD_STATIC_LINKING_ONLY

#include <zstd.h>
#include <to_buffer.hpp>

std::string zstd_compress(const std::string& str)
{
    std::string buffer;
    buffer.resize(ZSTD_compressBound(str.size()));
    size_t actual_size = ZSTD_compress(buffer.data(), buffer.size(), str.data(), str.size(), 22);
    buffer.resize(actual_size);
    return buffer;
}

std::string zstd_decompress(const std::string& str)
{
    auto size = ZSTD_findDecompressedSize(&str[0], str.size());
    if (size == ZSTD_CONTENTSIZE_ERROR || size == ZSTD_CONTENTSIZE_UNKNOWN)
        return std::string();
    std::string buffer;
    buffer.resize(size);
    auto actual_size = ZSTD_decompress(&buffer[0], size, &str[0], str.size());
    if (actual_size != size)
        return std::string();
    return buffer;
}

void zstd_compress(const std::vector<char>& buffer, const std::string& to)
{
    std::vector<char> data(ZSTD_compressBound(buffer.size()));
    size_t actual_size = ZSTD_compress(data.data(), data.size(), buffer.data(), buffer.size(), 22);
    to_binary(to, data, actual_size);
}

void zstd_compress(const std::string& from, const std::string& to)
{
    auto buffer = to_buffer(from);
    zstd_compress(buffer, to);
}

void zstd_decompress(const std::vector<char>& buffer, const std::string& to)
{
    auto size = ZSTD_findDecompressedSize(&buffer[0], buffer.size());
    if (size == ZSTD_CONTENTSIZE_ERROR || size == ZSTD_CONTENTSIZE_UNKNOWN)
        return;
    std::vector<char> data(size);
    auto actual_size = ZSTD_decompress(&data[0], size, &buffer[0], buffer.size());
    if (actual_size != size) 
        return;
    to_binary(to, data, size);
}

void zstd_decompress(const std::string& from, const std::string& to)
{
    auto buffer = to_buffer(from);
    zstd_decompress(buffer, to);
}

#endif
