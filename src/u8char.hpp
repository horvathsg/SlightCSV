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
            U8char(const char* const t_chars);
            void addChar(const char t_char);
            int size(void) const;
            bool isValid(void) const;
            char getChar(const int t_index) const;
            void getChars(char* t_chars, const int t_size) const;
            void clear(void);
            bool operator==(U8char const &t_u8char) const;
            bool operator!=(U8char const &t_u8char) const;
            bool operator<=(U8char const &t_u8char) const;
            bool operator<(U8char const &t_u8char) const;
            // TODO: test
            bool operator>=(U8char const &t_u8char) const;
            // TODO: test
            bool operator>(U8char const &t_u8char) const;
            // TODO: test
            char operator[](int t_index) const;
            operator bool() const;
        
        private:
            int getSizeFromChar(const char t_char);
            void validate(void);
            int compare(U8char const &t_u8char) const;
            char m_chars[5];
            int m_size;
            int m_current_count;
            bool m_valid;
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