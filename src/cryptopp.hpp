//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef CRYPTOPP_HPP
#define CRYPTOPP_HPP

#include <memory>
#include <vector>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

using cryptopp_byte_t = CryptoPP::byte;
using vecbyte_t = std::vector<cryptopp_byte_t>;
using cipher_t = CryptoPP::CBC_Mode_ExternalCipher;
using filter_t = CryptoPP::StreamTransformationFilter;

void fill(vecbyte_t& v, const std::string& s, size_t length)
{
    size_t i = 0;
    for (auto c : s)
    {
        v[i] = static_cast<cryptopp_byte_t>(c);
        if (++i == length)
            return;
    }    
}

template <typename Cryption, typename Cipher>
std::string crypt(const std::string& in, const std::string& key = std::string(), const std::string& iv = std::string(), size_t bits = 256)
{
    size_t length = bits / 8;
    vecbyte_t key_(length, 0x00);
    vecbyte_t iv_(CryptoPP::AES::BLOCKSIZE, 0x00);

    fill(key_, key, length);
    fill(iv_, iv, CryptoPP::AES::BLOCKSIZE);

    Cryption cryption(std::addressof(key_[0]), length);
    Cipher cipher(cryption, std::addressof(iv_[0]));

    std::string out;
    filter_t filter(cipher, new CryptoPP::StringSink(out));
    int inc = std::is_same_v<Cryption, CryptoPP::AES::Encryption>;
    filter.Put(reinterpret_cast<const unsigned char*>(in.c_str()), in.length() + inc);
    filter.MessageEnd();
    return out;
}

std::string encrypt(const std::string& plaintext, const std::string& key = std::string(), const std::string& iv = std::string(), size_t bits = 256)
{
    return crypt<CryptoPP::AES::Encryption, cipher_t::Encryption>(plaintext, key, iv, bits);
}

std::string decrypt(const std::string& ciphertext, const std::string& key = std::string(), const std::string& iv = std::string(), size_t bits = 256)
{
    return crypt<CryptoPP::AES::Decryption, cipher_t::Decryption>(ciphertext, key, iv, bits);
}

#endif
