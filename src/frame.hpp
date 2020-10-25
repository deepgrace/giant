//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/giant
//

#ifndef FRAME_HPP
#define FRAME_HPP

#include <string>
#include <algorithm>
#include <netinet/in.h>
#include <system_error>
#include <endianness.hpp>
#include <union_converter.hpp>

namespace monster::frame
{
    template <typename T>
    using uint_converter = union_converter<T, uint8_t>;
    using masking_key_type = uint_converter<uint32_t>;

    static const uint8_t min_header_size = 2;
    static const uint8_t max_header_size = 14;
    static const uint8_t max_extended_header_size = 12;
    static const uint8_t max_payload_size = 125;
    static const uint16_t max_extended_payload_size = 0xFFFF;
    static const uint8_t max_close_reason_size = 123;
    static const uint64_t max_jumbo_payload_size = 0x7FFFFFFFFFFFFFFF;

    static const uint8_t FIN = 0x80;
    static const uint8_t RSV1 = 0x40;
    static const uint8_t RSV2 = 0x20;
    static const uint8_t RSV3 = 0x10;
    static const uint8_t OPCODE = 0x0F;
    static const uint8_t MASK = 0x80;
    static const uint8_t PAYLOAD = 0x7F;
    static const uint8_t payload_16bit = 0x7E;
    static const uint8_t payload_64bit = 0x7F;

    enum class opcode
    {
        cont = 0x0,
        text = 0x1,
        binary = 0x2,
        rsv3 = 0x3,
        rsv4 = 0x4,
        rsv5 = 0x5,
        rsv6 = 0x6,
        rsv7 = 0x7,
        close = 0x8,
        ping = 0x9,
        pong = 0xA,
        rsvb = 0xB,
        rsvc = 0xC,
        rsvd = 0xD,
        rsve = 0xE,
        rsvf = 0xF
    };

    inline bool is_reserved(opcode v)
    {
        return (v >= opcode::rsv3 && v <= opcode::rsv7) || (v >= opcode::rsvb && v <= opcode::rsvf);
    }

    inline bool is_valid(opcode v)
    {
        return v >= opcode::cont && v <= opcode::rsvf;
    }

    inline bool is_control(opcode v)
    {
        return v >= opcode::close;
    }

    class extended_header
    {
        public:        
            extended_header()
            {
                reset();
            }
    
            void reset()
            {
                std::fill_n(bytes, max_extended_header_size, 0x00);
            }

            extended_header(uint64_t payload_size)
            {
                reset();
                copy_payload_size(payload_size);
            }

            extended_header(uint64_t payload_size, uint32_t masking_key) 
            {
                reset();
                uint_converter<uint32_t> conv;
                conv.s = masking_key;
                int payload_byte = copy_payload_size(payload_size);
                std::copy(conv.d, conv.d + 4, bytes + payload_byte);
            }

            uint16_t extended_size() const
            {
                uint_converter<uint16_t> conv;
                std::copy(bytes, bytes + 2, conv.d);
                return ntohs(conv.s);
            }

            uint64_t jumbo_size() const
            {
                uint_converter<uint64_t> conv;
                std::copy(bytes, bytes + 8, conv.d);
                return _ntohll(conv.s);
            }

            uint8_t bytes[max_extended_header_size];

        private:
            int copy_payload_size(uint64_t payload_size)
            {
                int offset = 0;
                if (payload_size <= max_payload_size)
                    offset = 8;
                else if (payload_size <= max_extended_payload_size)
                    offset = 6;
                uint_converter<uint64_t> conv;
                conv.s = _htonll(payload_size);
                std::copy(conv.d + offset, conv.d + 8, bytes);
                return 8 - offset;  // begin index of masking key in bytes
            }
    };

    struct base_header
    {
        base_header(){}
        base_header(opcode op, uint64_t payload_size, bool fin, bool mask, bool rsv1 = false, bool rsv2 = false, bool rsv3 = false)
        {
            if (fin)
                bhl |= FIN;
            if (rsv1)
                bhl |= RSV1;
            if (rsv2)
                bhl |= RSV2;
            if (rsv3)
                bhl |= RSV3;
            bhl |= (to_underlying(op) & OPCODE);
            if (mask)
                bhr |= MASK;
            uint8_t payload_bit = payload_64bit;
            if (payload_size <= max_payload_size)
                payload_bit = static_cast<uint8_t>(payload_size);
            else if (payload_size <= max_extended_payload_size)
                payload_bit = payload_16bit;
            bhr |= payload_bit;
        }
        
        bool has_fin() const
        {
            return (bhl & FIN) == FIN;
        }

        void set_fin(bool value)
        {
            bhl = (value ? bhl | FIN : bhl & ~FIN);
        }

        bool has_rsv1() const
        {
            return (bhl & RSV1) == RSV1;
        }
    
        void set_rsv1(bool value)
        {
            bhl = (value ? bhl | RSV1 : bhl & ~RSV1);
        }

        bool has_rsv2() const
        {
            return (bhl & RSV2) == RSV2;
        }

        void set_rsv2(bool value)
        {
            bhl = (value ? bhl | RSV2 : bhl & ~RSV2);
        }

        bool has_rsv3() const
        {
            return (bhl & RSV3) == RSV3;
        }
    
        void set_rsv3(bool value)
        {
            bhl = (value ? bhl | RSV3 : bhl & ~RSV3);
        }

        opcode get_opcode() const
        {
            return opcode(bhl & OPCODE);
        }

        bool has_mask() const
        {
            return (bhr & MASK) == MASK;
        }
    
        void set_mask(bool value)
        {
            bhr = (value ? bhr | MASK : bhr & ~MASK);
        }

        uint8_t basic_size() const
        {
           return bhr & PAYLOAD;
        }

        uint8_t get_masking_key_offset() const
        {
            auto size = basic_size();
            if (size == payload_16bit)
                return 2;
            else if (size == payload_64bit)
                return 8;
            return 0;
        }

        size_t get_header_len() const
        {
            size_t size = min_header_size + get_masking_key_offset();
            if (has_mask())
                size += 4;
            return size; 
        }

        std::string prepare_header(const extended_header& ext) const
        {
            std::string s;
            s.push_back(bhl);
            s.push_back(bhr);
            s.append(reinterpret_cast<const char*>(ext.bytes), get_header_len() - min_header_size);
            return s;
        }

        masking_key_type get_masking_key(const extended_header& ext) const
        {
            masking_key_type conv;
            if (! has_mask())
                conv.s = 0;
            else
            {
                unsigned int offset = get_masking_key_offset();
                std::copy(ext.bytes + offset, ext.bytes + offset + 4, conv.d);
            }
            return conv;
        }

        inline uint64_t get_payload_size(const extended_header& ext) const
        {
            auto size = basic_size();
            if (size <= max_payload_size)
                return size;
            else if (size == payload_16bit)
                return ext.extended_size();
            return ext.jumbo_size();
        }

        uint8_t bhl = 0x00;
        uint8_t bhr = 0x00;
    };

    inline size_t prepare_masking_key(const masking_key_type& key)
    {
        size_t low_bits = static_cast<size_t>(key.s);
        if (sizeof(size_t) == 8) 
        {
            uint64_t high_bits = static_cast<size_t>(key.s);
            return static_cast<size_t>((high_bits << 32) | low_bits);
        }
        return low_bits;
    }

    inline size_t shift_key(size_t prepared_key, size_t offset)
    {
        size_t bits = (sizeof(size_t) - offset) * 8;
        if (is_little_endian())
            return (prepared_key >> offset*8) | prepared_key << bits;
        return (prepared_key << offset*8) | prepared_key >> bits;
    }

    template <typename T, typename R>
    void byte_mask(T begin, T end, R result, const masking_key_type& key, size_t offset = 0)
    {
        size_t key_index = offset % 4;
        while (begin != end)
        {
            *result = *begin ^ key.d[key_index++];
            key_index %= 4;
            ++begin;
            ++end;
        }
    }

    template <typename T>
    void byte_mask(T begin, T end, const masking_key_type& key, size_t offset = 0)
    {
        byte_mask(begin, end, begin, key, offset);
    }

    inline size_t byte_mask(uint8_t* src, uint8_t* dst, size_t size, size_t prepared_key)
    {
        uint_converter<uint32_t> key;
        key.s = prepared_key;
        for (size_t i = 0; i != size; ++i)
             dst[i] = src[i] ^ key.d[i % 4];
        return shift_key(prepared_key, size % 4);
    }

    inline size_t byte_mask(uint8_t* data, size_t size, size_t prepared_key)
    {
        return byte_mask(data, data, size, prepared_key);
    }
}

#endif
