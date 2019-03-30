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

utils::U8char::U8char(const char* const t_chars) {
    this->clear();
    for (int i = 0; i < strlen(t_chars); ++i) {
        this->addChar(t_chars[i]);
    }
}

void utils::U8char::addChar(const char t_char) {
    if (m_size && m_current_count + 1 > m_size) {
        throw u8char_format_error();
    }
    if (!m_current_count) {
        m_size = getSizeFromChar(t_char);
    }
    m_chars[m_current_count] = t_char;
    ++m_current_count;
}

int utils::U8char::size(void) const {
    return m_size;
}

bool utils::U8char::isValid(void) const {  
    
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

char utils::U8char::getChar(const int t_index) const {
    if (t_index >= m_size || t_index >= m_current_count) {
        throw u8char_index_error();
    }
    if (!isValid()) {
        throw u8char_format_error();
    }
    return m_chars[t_index];
}

void utils::U8char::getChars(char* t_chars, const int t_size) const {
    if (!isValid()) {
        throw u8char_format_error();
    }
    // clear result array (at least partially)
    for (int i = 0; i < t_size; ++i) {
        t_chars[i] = 0;
    }
    // determine limit
    int lim = t_size >= m_size ? m_size : t_size;
    // fill result array
    for (int i = 0; i < lim; ++i) {
        t_chars[i] = m_chars[i];
    }
}

void utils::U8char::clear(void) {
    for (int i = 0; i < 5; ++i) {
        m_chars[i] = 0;
    }
    m_size = 0;
    m_current_count = 0;
}

int utils::U8char::getSizeFromChar(const char t_char) {
    int test_size = -1;

    // find the first most significant 0 in the most significant 5 bits of the first byte
    for (int i = 0; i < 5; ++i) {
        if (!(t_char & (1 << (7 - i)))) {
            test_size = i;
            break;
        }
    }

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
    
    return test_size;
}

bool utils::U8char::operator== (U8char const &t_u8char) const {
    bool retval = true;

    retval &= m_size == t_u8char.size();
    
    for (int i = 0; i < m_size; ++i) {
        retval &= m_chars[i] == t_u8char[i];
    }

    return retval;
}

char utils::U8char::operator[] (int t_index) const {
    return m_chars[t_index];
}