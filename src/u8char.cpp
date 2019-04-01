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
#include <string>

using utils::byte;
using std::string;

utils::U8char::U8char(void) {
    // initialize fields
    this->clear();
}

utils::U8char::U8char(const byte* const t_bytes) {
    // initialize fields
    this->clear();
    // add bytes from input
    for (int i = 0; i < strlen(t_bytes); ++i) {
        this->addByte(t_bytes[i]);
    }
}

void utils::U8char::addByte(const byte t_byte) {
    // prevent adding more bytes than indicated in the first byte
    if (m_size && m_current_count + 1 > m_size) {
        throw u8char_format_error();
    }
    // if byte is first, get the total number of bytes and invalidate object
    if (!m_current_count) {
        m_size = getSizeFromByte(t_byte);
        m_valid = false;
    }
    // add byte and increment count
    m_bytes[m_current_count] = t_byte;
    ++m_current_count;
    // if all bytes are added, validate object
    if (m_current_count == m_size) {
        this->validate();
    }
}

int utils::U8char::size(void) const {
    return m_size;
}

bool utils::U8char::isValid(void) const {  
    return m_valid;
}

byte utils::U8char::getByte(const int t_index) const {
    // prevent getting a byte which doesn't exist or is not set
    if (t_index >= m_size || t_index >= m_current_count) {
        throw u8char_index_error();
    }
    // prevent getting byte from an invalid object
    if (!isValid()) {
        throw u8char_format_error();
    }
    return m_bytes[t_index];
}

void utils::U8char::getBytes(byte* t_bytes, const int t_size) const {
    // prevent getting bytes from an invalid object
    if (!isValid()) {
        throw u8char_format_error();
    }
    // clear result array (at least partially)
    for (int i = 0; i < t_size; ++i) {
        t_bytes[i] = 0;
    }
    // determine limit
    int lim = t_size >= m_size ? m_size : t_size;
    // fill result array
    for (int i = 0; i < lim; ++i) {
        t_bytes[i] = m_bytes[i];
    }
}

string utils::U8char::getString(void) const {
    // prevent getting bytes from an invalid object
    if (!isValid()) {
        throw u8char_format_error();
    }
    // generate and return UTF-8 string from bytes
    string u8_str(m_bytes);
    return u8_str;
}

void utils::U8char::clear(void) {
    // clear bytes
    for (int i = 0; i < 5; ++i) {
        m_bytes[i] = 0;
    }
    m_size = 0;
    m_current_count = 0;
    m_valid = true;
}

int utils::U8char::getSizeFromByte(const byte t_byte) {
    int test_size = -1;

    // find the first most significant 0 in the most significant 5 bits of the first byte
    for (int i = 0; i < 5; ++i) {
        if (!(t_byte & (1 << (7 - i)))) {
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

void utils::U8char::validate(void) {
    // check remaining bytes of UTF-8 character
    for (int i = 1; i < m_size; ++i) {
        // if byte's most significant bits are not '10'
        if (!(m_bytes[i] & (1 << 7)) || (m_bytes[i] & (1 << 6))) {
            // invalidate object
            m_valid = false;
            return;
        }
    }

    // check remaining (not used) bytes for garbage - e.g. re-usage without proper cleanup
    for (int i = m_size; i < 4; ++i) {
        // if remaining bytes are not zeros
        if (m_bytes[i] != 0) {
            // invalidate object
            m_valid = false;
            return;
        }
    }

    m_valid = true;

}

int utils::U8char::compare(U8char const &t_u8char) const {
    // if either one of the objects is not valid
    if (!m_valid || !(t_u8char.isValid())) {
        throw u8char_format_error();
    }

    // if current object's size is less
    if (m_size < t_u8char.size()) {
        return -1;
    // if current object's size is greater
    } else if (m_size > t_u8char.size()) {
        return 1;
    }
    
    // if size of the two objects are equal, iterate throught the individual bytes
    for (int i = 0; i < m_size; ++i) {
        // current object's byte is less
        if (m_bytes[i] < t_u8char[i]) {
            return -1;
        // current object's byte is greater
        } else if (m_bytes[i] > t_u8char[i]) {
            return 1;
        }
    }
    return 0;
}

bool utils::U8char::operator==(U8char const &t_u8char) const {
    return compare(t_u8char) == 0;
}

bool utils::U8char::operator!=(U8char const &t_u8char) const {
    return compare(t_u8char) != 0; 
}

bool utils::U8char::operator<(U8char const &t_u8char) const {
    return compare(t_u8char) == -1;
}

bool utils::U8char::operator<=(U8char const &t_u8char) const {
    int comp = compare(t_u8char);
    return comp == -1 || comp == 0;
}

bool utils::U8char::operator>(U8char const &t_u8char) const {
    return compare(t_u8char) == 1;
}

bool utils::U8char::operator>=(U8char const &t_u8char) const {
    int comp = compare(t_u8char);
    return comp == 1 || comp == 0;
}

byte utils::U8char::operator[](int t_index) const {
    return this->getByte(t_index);
}

utils::U8char::operator bool() const {
    // true if number of bytes is greater than zero and object is valid
    return (m_size > 0) && this->isValid();
}