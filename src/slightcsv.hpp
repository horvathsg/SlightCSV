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

#ifndef _UTILS_SLIGHTCSV_HPP
#define _UTILS_SLIGHTCSV_HPP

#include <string>
#include <vector>
#include <exception>
#include <set>
#include <map>

#include "u8char.hpp"

using std::string;
using std::vector;
using std::exception;
using std::set;
using std::map;

/// The namespace used by all SlightCSV classes and methods.
namespace utils {

    /// A forward declared class to hold SlightCSV's private data members (pImpl).
    class SlightCSVPrivate;

    /// The "main" class of the library. Provides methods for setting up the library, triggering data processing 
    ///  and getting the results.
    class SlightCSV {

        public:

            /// The class's default constructor. Takes care of allocating memory for the class's private data members.
            SlightCSV(void);

            /// The class's default destructor. Takes care of de-allocating memory held by the class's private data members.
            ~SlightCSV(void);

            /// Method to set the name of the CSV file to be parsed. Required before triggering data loading.
            /// \param t_filename name and relative path of the file.
            /// \see getFileName()
            void setFileName(const string t_filename);

            /// Method to get the previously set name of the CSV file to be parsed.
            /// \return previously set name and relative path of the file.
            /// \see setFileName()
            string getFileName(void) const;

            /// Method to set the delimiter character. It is used as a separator between "cells" in a row. Required 
            /// before triggering data loading.
            /// \param t_separator character to use as delimiter.
            /// \see getSeparator()
            void setSeparator(const U8char t_separator);

            /// Method to get the previously set delimiter character.
            /// \return previously set delimiter character.
            /// \see setSeparator()
            void getSeparator(U8char &t_target) const;

            /// Method to set the escape character. It is used to escape other characters in the file to be processed. 
            /// Escaped delimiter and new line characters are not processed and are propagated to processed "cells". 
            /// Setting (or not setting) the escape character not in accordance with the file format may trigger 
            /// exceptions (e.g. cell count mismatch in row). Order of execution: strip, escape, replace. Characters 
            /// enclosed between escape characters will be escaped even if escape characters are stripped or replaced. 
            /// Method is optional. If used, set it before triggering data loading.
            /// \param t_escape character to be used to escape a group of characters in the input.
            /// \see getEscape()
            void setEscape(const U8char t_escape);

            /// Method to get the previously set escape character.
            /// \return previously set escape character.
            /// \see getEscape()
            void getEscape(U8char &t_target) const;

            /// Method to define a set of character(s) to be stripped from the input of the parser. Order of execution: 
            /// strip, escape, replace. Escape characters may be stripped, but characters enclosed between escape characters
            /// will be escaped and present in the output. Stripped characters won't be seen by replace. Optional method.
            /// If used, set it before triggering data loading.
            /// \param t_strip_chars a set of characters previously populated with characters to be stripped.
            /// \see getStripChars()
            void setStripChars(const set<U8char> &t_strip_chars);

            /// Method to get the previously defined set of character(s) to be stripped from the input of the parser.
            /// \param t_target set that gets populated with the previously defined set of characters 
            /// to be stripped.
             /// \see setStripChars()
            void getStripChars(set<U8char> &t_target) const;

            /// Method to define a map of character pair(s) to be replaced in the input of the parser. The map's "key" 
            /// character is replaced by the "value" character in the input. Order of execution: strip, escape, 
            /// replace. Escape characters may be replaced, but characters enclosed between escape characters
            /// will be escaped and present in the output. Stripped characters won't be seen by the method. Optional method.
            /// If used, set it before triggering data loading.
            /// \param t_rep_chars a map of "replacee" and "replacer" characters.
            /// \see getReplaceChars()
            void setReplaceChars(const map<U8char, U8char> &t_rep_chars);

            /// Method to get the previously set map of character pair(s) to be replaced in the input of the parser.
            /// \param t_target map that gets populated with the previously defined map of character pair(s)
            /// to be replaced.
            /// \see setReplaceChars()
            void getReplaceChars(map<U8char, U8char> &t_target) const;

            /// Method to trigger data loading. Requires filename and delimiter to be set before calling it.
            /// \return the number of records loaded.
            /// \see unloadData()
            size_t loadData(void);

            /// Method to get the number of columns in the parsed data structure. Data is held in memory.
            /// \return column count in the parsed data structure.
            /// \see getRowCount()
            size_t getColumnCount(void) const;

            /// Method to get the number of rows in the parsed data structure. Data is held in memory.
            /// \return row count in the parsed data structure.
            /// \see getColumnCount()
            size_t getRowCount(void) const;

            /// Method to override and set the number of header rows in the output of the parser. The library tries 
            /// to detect and count header rows automatically.
            /// \param t_header_count the number of header rows at the beginning of the CSV file.
            /// \see getHeaderCount()
            void setHeaderCount(const size_t t_header_count);

            /// Method to get the number of header rows at the beginning of the parsed file. After loading the data 
            /// it returns an automatically detected value which may be overridden by the user.
            /// \return number of header rows at the beginning of the parsed file.
            /// \see setHeaderCount()
            size_t getHeaderCount(void) const;

            /// Method to get the contents of a specific cell. The internal data structure stores cell values as strings.
            /// When using the method, the library tries to convert the string contents to the type supplied as the 
            /// first parameter of the method. Supported types: int, float, double, string. If conversion fails,
            /// the value returned will be 0. In this case, it is always possible to get the value as string.
            /// \param t_value variable to hold the value of the cell.
            /// \param t_row_index index (starting from 0) of the row the cell queried.
            /// \param t_column_index index (starting from 0) of the column holding the cell queried.
            /// \see getRow()
            /// \see getColumn()
            template <class T>
            void getCell(T &t_value, const size_t t_row_index, const size_t t_column_index) const;

            /// Method to get the cells of a specific column. The column is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library tries 
            /// to convert the string contents to the type held by the vector supplied as the method. Supported 
            /// types: int, float, double, string. If conversion fails, the value returned will be 0. In this case, 
            /// it is always possible to get the value as string.
            /// \param t_target_column vector to hold the values of the cells in the column.
            /// \param t_column_index index (starting from 0) of the column to be returned.
            /// \see getRow()
            /// \see getCell()
            template <class T>
            void getColumn(vector<T> &t_target_column, const size_t t_column_index) const;

            /// \overload
            /// Method to get the cells of a specific column. The column is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library tries 
            /// to convert the string contents to the type held by the vector supplied as the method. Supported 
            /// types: int, float, double, string. If conversion fails, the value returned will be 0. In this case, 
            /// it is always possible to get the value as string.
            /// \param t_target_column vector to hold the values of the cells in the column.
            /// \param t_column_index index (starting from 0) of the column to be returned.
            /// \param t_start_cell_index index (starting from 0) of the first vertical cell (filtering).
            /// \see getRow()
            /// \see getCell()
            template <class T>
            void getColumn(vector<T> &t_target_column, const size_t t_column_index, const size_t t_start_cell_index) const;

            /// \overload
            /// Method to get the cells of a specific column. The column is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library tries 
            /// to convert the string contents to the type held by the vector supplied as the method. Supported 
            /// types: int, float, double, string. If conversion fails, the value returned will be 0. In this case, 
            /// it is always possible to get the value as string.
            /// \param t_target_column vector to hold the values of the cells in the column.
            /// \param t_column_index index (starting from 0) of the column to be returned.
            /// \param t_start_cell_index index (starting from 0) of the first vertical cell (filtering)
            /// \param t_cell_count number of cells to return (beginning from the first vertical cell specified).
            /// \see getRow()
            /// \see getCell()
            template <class T>
            void getColumn(vector<T> &t_target_column, const size_t t_column_index, const size_t t_start_cell_index, 
            const size_t t_cell_count) const;

            /// Method to get the cells of a specific row. The row is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library
            /// returns cells in a row as strings.
            /// \param t_target_row vector to hold the values of the cells in the row.
            /// \param t_row_index index (starting from 0) of the row to be returned.
            /// \see getColumn()
            /// \see getCell()
            void getRow(vector<string> &t_target_row, const size_t t_row_index) const;

            /// \overload
            /// Method to get the cells of a specific row. The row is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library
            /// returns cells in a row as strings.
            /// \param t_target_row vector to hold the values of the cells in the row.
            /// \param t_row_index index (starting from 0) of the row to be returned.
            /// \param t_start_cell_index index (starting from 0) of the first horizontal cell (filtering).
            /// \see getColumn()
            /// \see getCell()
            void getRow(vector<string> &t_target_row, const size_t t_row_index, const size_t t_start_cell_index) const;

            /// \overload
            /// Method to get the cells of a specific row. The row is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library
            /// returns cells in a row as strings.
            /// \param t_target_row vector to hold the values of the cells in the row.
            /// \param t_row_index index (starting from 0) of the row to be returned.
            /// \param t_start_cell_index index (starting from 0) of the first horizontal cell (filtering).
            /// \param t_cell_count number of cells to return (beginning from the first horizontal cell specified).
            /// \see getColumn()
            /// \see getCell()
            void getRow(vector<string> &t_target_row, const size_t t_row_index, const size_t t_start_cell_index, 
            const size_t t_cell_count) const;

            /// Method to unload data structure from memory. Settings (filename, delimiter, character manipulation
            /// settings) are preserved. Data queries cannot be made until loading a data structure. Optional,
            /// library will not leak if not used. 
            /// \see loadData()
            void unloadData(void);

            /// Method to reset the library to its initial state. Unloads any data structure loaded previously and
            /// resets settings to their initial state. Optional, library will not leak if not used.
            void reset(void);

        private:
            void processLine(string &t_input, const size_t t_row_id);

            SlightCSVPrivate *m_csvp;

    };

    /// Base exception of the class (never gets thrown). Inheriting from std::exception.
    class slightcsv_error: public exception {};

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - data cannot be loaded (file not found)
    /// - queried filename is empty (not set)
    /// - trying to set empty filename
    class slightcsv_filename_error: public slightcsv_error {
        
        const char* what() const throw() {
            return "Wrong or missing filename.";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - queried delimiter character value is zero (not set)
    /// - trying to set delimiter character with zero value
    class slightcsv_separator_error: public slightcsv_error {

        const char* what() const throw() {
            return "Wrong or missing separator.";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - queried escape character value is zero (not set)
    /// - trying to set escape character with zero value
    class slightcsv_escape_error: public slightcsv_error {

        const char* what() const throw() {
            return "Escape character not set.";
        }

    };

    /// Exception inheriting from std::exception. It is thrown when:
    /// - queried strip character set is empty (not set)
    /// - trying to set empty strip character set
    class slightcsv_strip_error: public slightcsv_error {

        const char* what() const throw() {
            return "Strip character set empty.";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - queried replace character map is empty (not set)
    /// - trying to set empty replace character map
    class slightcsv_replace_error: public slightcsv_error {

        const char* what() const throw() {
            return "Replace character map empty.";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - the CSV file format is invalid (inconsistency in terms of cell quantity in a row)
    /// - settings of the parser cause the CSV file format to seem invalid (as a consequence of character manipulation 
    /// with escape, strip and replace)
    class slightcsv_format_cellcnt_error: public slightcsv_error {

        const char* what() const throw() {
            return "CSV format error (cell count mismatch in row).";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - intermediate header row is found after the beginning of the file
    class slightcsv_format_header_error: public slightcsv_error {

        const char* what() const throw() {
            return "CSV format error (intermediate header).";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - data query methods are called before loading a data structure
    class slightcsv_data_error: public slightcsv_error {

        const char* what() const throw() {
            return "Data not loaded.";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - data query methods called with out-of-range row index
    /// - data query methods called with out-of-range column index
    class slightcsv_index_error: public slightcsv_error {

        const char* what() const throw() {
            return "Bad row or column index.";
        }

    };

    /// Exception inheriting from slightcsv_error. It is thrown when:
    /// - file read error occurred before reaching the end of file (EOF)
    class slightcsv_read_error: public slightcsv_error {

        const char* what() const throw() {
            return "Unexpected error occurred while reading file.";
        }

    };

} // utils

#endif // _UTILS_SLIGHTCSV_HPP