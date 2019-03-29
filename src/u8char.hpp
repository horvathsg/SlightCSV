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

#ifndef _UTILS_U8CHAR_HPP
#define _UTILS_U8CHAR_HPP

#include <exception>

using std::exception;

namespace utils {

    class U8char {

        public:
            U8char();
            void addByte(const unsigned char t_char);
            unsigned short size(void) const;
            bool validate(void) const;
            unsigned char getByte(const unsigned short t_index) const;
            unsigned char getBytes(void) const;
            void clear(void);
            bool operator== (U8char const &t_u8char) const;
            unsigned char operator[] (unsigned short t_index) const;
        
        private:
            unsigned short getSizeFromFirstByte(void);
            unsigned char m_chars[5];
            unsigned short m_size;
            unsigned short m_current_count;
    };

    class u8char_error: public exception {};

    class u8char_index_error: public u8char_error {
        const char* what() const throw() {
            return "Invalid character index.";
        }
    };

    class u8char_format_error: public u8char_error {
        const char* what() const throw() {
            return "UTF8 format error.";
        }
    };

} // utils

#endif // _UTILS_U8CHAR_HPP