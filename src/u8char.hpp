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
#include <string>

using std::string;
using std::exception;

namespace utils {

    /// Type to represent the bytes forming an UTF-8 character. For compatibility reasons, it is based on the char type.
    typedef char byte;

    /// The UTF-8 character class of the library. 
    class U8char {

        public:
            /// Default constructor of the class.
            /// \see U8char(const byte* const t_bytes)
            U8char(void);
            
            /// Overloaded constructor of the class. Creates an UTF-8 character from the incoming bytes.
            /// \param t_bytes incoming bytes (1-4, depending on the UTF-8 character encoded).
            /// \see U8char(void)
            U8char(const byte* const t_bytes);
            
            /// Method to add an incoming byte to an UTF-8 character. The consistence of the byte to add 
            /// with the bytes already added is checked. In case an invalid byte is added, an exception will 
            /// be thrown.
            /// \param t_char byte to be added to the UTF-8 character object.
            /// \see getByte()
            /// \see getBytes()
            /// \see getString()
            void addByte(const byte t_char);
            
            /// Method the get the number of bytes the UTF-8 character consists of. It is determined after adding 
            /// the first byte of the UTF-8 character.
            /// \return the number of bytes the UTF-8 character consists of.
            int size(void) const;
            
            /// Method to get the validity status of the UTF-8 character object. A valid UTF-8 character:
            /// - has valid length indication in its first byte (e.g. binary 110xxxxx for an UTF-8 character 
            /// consisting of 2 bytes)
            /// - has valid continuation bytes (in the form of binary 10xxxxxx)
            /// - consists of the exact same number of bytes as it's indicated by its first byte
            ///
            /// \return validation status of the UTF-8 object.
            bool isValid(void) const;
            
            /// Method to get a byte from the bytes representing the UTF-8 character. Calling the method to 
            /// get a byte of an invalid UTF-8 character results in an exception.
            /// \param t_index the index of the byte to get.
            /// \return the byte at the given index.
            /// \see addByte()
            /// \see getBytes()
            /// \see getString()
            byte getByte(const int t_index) const;
            
            /// Method to get multiple bytes from the bytes representing the UTF-8 character. Calling the 
            /// method to get bytes of an invalid UTF-8 character results in an exception.
            /// \param t_bytes the buffer to store the bytes in (with a length of at least 5 to hold a maximum 
            /// of 4 bytes and a closing byte).
            /// \param t_size number of bytes to get.
            /// \see addByte()
            /// \see getByte()
            /// \see getString()
            void getBytes(char* t_bytes, const int t_size) const;
            
            /// Method to get UTF-8 character represented by the object.
            /// \return string representation of UTF-8 character.
            /// \see addByte()
            /// \see getByte()
            /// \see getBytes()
            string getString(void) const;
            
            /// Method to clear the UTF-8 character object. After calling the method, the object can be reused to represent
            /// another UTF-8 character.
            void clear(void);
            
            /// Comparison method to evaluate an 'equal' relation of two UTF-8 character objects.
            /// \param t_u8char UTF-8 character object to compare the current UTF-8 character object to.
            /// \return the outcome of the comparison.
            bool operator==(U8char const &t_u8char) const;
            
            /// Comparison method to evaluate a 'not equal' relation of two UTF-8 character objects.
            /// \param t_u8char UTF-8 character object to compare the current UTF-8 character object to.
            /// \return the outcome of the comparison.
            bool operator!=(U8char const &t_u8char) const;
            
            /// Comparison method to evaluate an 'less or equal' relation of two UTF-8 character objects.
            /// \param t_u8char UTF-8 character object to compare the current UTF-8 character object to.
            /// \return the outcome of the comparison.
            bool operator<=(U8char const &t_u8char) const;
            
            /// Comparison method to evaluate an 'less' relation of two UTF-8 character objects.
            /// \param t_u8char UTF-8 character object to compare the current UTF-8 character object to.
            /// \return the outcome of the comparison.
            bool operator<(U8char const &t_u8char) const;
            
            /// Comparison method to evaluate an 'greater or equal' relation of two UTF-8 character objects.
            /// \param t_u8char UTF-8 character object to compare the current UTF-8 character object to.
            /// \return the outcome of the comparison.
            bool operator>=(U8char const &t_u8char) const;
            
            /// Comparison method to evaluate an 'greater' relation of two UTF-8 character objects.
            /// \param t_u8char UTF-8 character object to compare the current UTF-8 character object to.
            /// \return the outcome of the comparison.
            bool operator>(U8char const &t_u8char) const;
            
            /// Method to get a byte from the bytes representing the UTF-8 character. Calling the method to 
            /// get a byte of an invalid UTF-8 character results in an exception.
            /// \param t_index the index of the byte to get.
            /// \return the byte at the given index.
            byte operator[](int t_index) const;
            
            /// Method to convert an UTF-8 character object to bool type. Calling it on an UTF-8 character object 
            /// evaluates to true if the object contains at least one byte and the object is a valid UTF-8 character. 
            operator bool() const;
        
        private:
            int getSizeFromByte(const char t_byte);
            void validate(void);
            int compare(U8char const &t_u8char) const;
            byte m_bytes[5];
            int m_size;
            int m_current_count;
            bool m_valid;
    };

    /// Base exception of the class (never gets thrown). Inheriting from std::exception.
    class u8char_error: public exception {};

    /// Exception inheriting from u8char_error. It is thrown when:
    /// - trying to get byte of U8char with invalid index
    class u8char_index_error: public u8char_error {
        const char* what() const throw() {
            return "Invalid byte index.";
        }
    };

    /// Exception inheriting from u8char_error. It is thrown when:
    /// - bytes held by the object do not represent a valid UTF-8 character
    class u8char_format_error: public u8char_error {
        const char* what() const throw() {
            return "UTF-8 format error.";
        }
    };

} // utils

#endif // _UTILS_U8CHAR_HPP