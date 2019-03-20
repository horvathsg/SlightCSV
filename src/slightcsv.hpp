// SlightCSV - simple, lightweight CSV parser library
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

using std::string;
using std::vector;
using std::exception;

namespace utils {

    class SlightCSVPrivate;

    class SlightCSV {

        public:
            SlightCSV(void);
            ~SlightCSV(void);
            void setFileName(string t_filename);
            string getFileName(void) const;
            void setSeparator(char t_separator);
            char getSeparator(void) const;
            void setEscape(char t_escape);
            char getEscape(void) const;
            size_t loadData(void);
            size_t getColumnCount(void) const;
            size_t getRowCount(void) const;
            void setHeaderCount(size_t t_header_count);
            size_t getHeaderCount(void) const;
            template <class T>
            void getCell(T &t_value, size_t t_row_index, size_t t_column_index) const;
            template <class T>
            void getColumn(vector<T> &t_target_column, size_t t_column_index) const;
            template <class T>
            void getColumn(vector<T> &t_target_column, size_t t_column_index, size_t t_start_cell_index) const;
            template <class T>
            void getColumn(vector<T> &t_target_column, size_t t_colunm_index, size_t t_start_cell_index, size_t t_cell_count) const;
            void getRow(vector<string> &t_target_row, size_t t_row_index) const;
            void getRow(vector<string> &t_target_row, size_t t_row_index, size_t t_start_cell_index) const;
            void getRow(vector<string> &t_target_row, size_t t_row_index, size_t t_start_cell_index, size_t t_cell_count) const;
            void unloadData(void);
            void reset(void);

        private:
            void processLine(string &t_input, size_t t_row_id);

            SlightCSVPrivate *m_csvp;

    };

    class slightcsv_error: public exception {};

    class slightcsv_filename_error: public slightcsv_error {
        
        const char* what() const throw() {
            return "Wrong or missing filename.";
        }

    };

    class slightcsv_separator_error: public slightcsv_error {

        const char* what() const throw() {
            return "Wrong or missing separator.";
        }

    };

    class slightcsv_escape_error: public slightcsv_error {

        const char* what() const throw() {
            return "Escape character not set.";
        }

    };

    class slightcsv_format_cellcnt_error: public slightcsv_error {

        const char* what() const throw() {
            return "CSV format error (cell count mismatch in row).";
        }

    };

    class slightcsv_format_header_error: public slightcsv_error {

        const char* what() const throw() {
            return "CSV format error (intermediate header).";
        }

    };

    class slightcsv_data_error: public slightcsv_error {

        const char* what() const throw() {
            return "Data not loaded.";
        }

    };

    class slightcsv_index_error: public slightcsv_error {

        const char* what() const throw() {
            return "Bad row or column index.";
        }

    };

    class slightcsv_alloc_error: public slightcsv_error {

        const char* what() const throw() {
            return "Failed to allocate memory.";
        }

    };

    class slightcsv_read_error: public slightcsv_error {

        const char* what() const throw() {
            return "Unexpected error occurred while reading file.";
        }

    };

} // utils

#endif // _UTILS_SLIGHTCSV_HPP