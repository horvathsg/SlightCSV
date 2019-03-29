// SlightCSV - simple, lightweight CSV parser library written in C++
// Copyright (C) 2018 Simon Horvath <horvathsg@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "u8char.hpp"
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

utils::U8char::U8char() {
    this->clear();
}

void utils::U8char::addByte(const unsigned char t_char) {
    if (m_size && m_current_count + 1 > m_size) {
        throw u8char_format_error();
    }
    m_chars[m_current_count] = t_char;
    ++m_current_count;
    if (m_current_count == 1) {
        m_size = getSizeFromFirstByte();
    }
}

unsigned short utils::U8char::size(void) const {
    return m_size;
}

bool utils::U8char::validate(void) const {  
    
    // check remaining bytes of UTF8 character
    for (int i = 1; i < m_size; ++i) {
        // if byte's most significant bits are not '10'
        if (!(m_chars[i] & (1 << 7)) || (m_chars[i] & (1 << 6))) {
            return false;
        }
    }

    // check remaining (not used) bytes for garbage
    for (int i = m_size; i < 4; ++i) {
        // if remaining bytes are not zeros
        if (m_chars[i] != 0) {
            return false;
        }
    }

    return true;
}

unsigned char utils::U8char::getByte(const unsigned short t_index) const {
    if (t_index >= m_size || t_index >= m_current_count) {
        throw u8char_index_error();
    }
    if (!validate()) {
        throw u8char_format_error();
    }
    return m_chars[t_index];
}

unsigned char utils::U8char::getBytes(void) const {
    if (!validate()) {
        throw u8char_format_error();
    }
    // TODO: implement
}

void utils::U8char::clear(void) {
    for (int i = 0; i < 5; ++i) {
        m_chars[i] = 0;
    }
    m_size = 0;
    m_current_count = 0;
}

unsigned short utils::U8char::getSizeFromFirstByte(void) {
    short test_size = -1;

    // find the first most significant 0 in the most significant 5 bits of the first byte
    for (unsigned short i = 0; i < 5; ++i) {
        if (!(m_chars[0] & (1 << (7 - i)))) {
            test_size = i;
            break;
        }
    }

    // cout << "Test size: " << test_size << endl;

    // if bit with zero not found in the most significant 5 bits of the first byte
    if (test_size == -1) {
        throw u8char_format_error();
    }

    // if first byte's most significant bits are '10'
    if (test_size == 1) {
        throw u8char_format_error();
    }

    // if first byte's most significant bit is 0 (plain ASCII char)
    if (test_size == 0) {
        test_size = 1;
    }
    
    return (unsigned short)test_size;
}

bool utils::U8char::operator== (U8char const &t_u8char) const {
    bool retval = true;

    retval &= m_size == t_u8char.size();
    
    for (int i = 0; i < m_size; ++i) {
        retval &= m_chars[i] == t_u8char[i];
    }

    return retval;
}

unsigned char utils::U8char::operator[] (unsigned short t_index) const {
    return m_chars[t_index];
}