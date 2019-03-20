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

#ifndef _UTILS_SLIGHTMATRIX_HPP
#define _UTILS_SLIGHTMATRIX_HPP

#include <string>
#include <vector>
#include <exception>

using std::string;
using std::vector;
using std::exception;

namespace utils {

    class SlightMatrix {

        public:
            SlightMatrix(void);
            void setCapacity(size_t t_cell_count);
            size_t getCapacity(void) const;
            void setColumnCount(size_t t_column_count);
            size_t getColumnCount(void) const;
            void addCell(string t_cell);
            void addCells(vector<string> t_cells);
            void setHeaderCount(size_t t_header_count);
            size_t getHeaderCount(void) const;
            bool validate(void) const;
            size_t getRowCount(void) const;
            template <class T>
            void getCell(T &t_value, size_t t_row_index, size_t t_column_index) const;
            void getRow(vector<string> &t_target, size_t t_row_index) const;
            void getRow(vector<string> &t_target, size_t t_row_index, size_t t_start_cell_index) const;
            void getRow(vector<string> &t_target, size_t t_row_index, size_t t_start_cell_index, size_t t_cell_count) const;
            template <class T>
            void getColumn(vector<T> &t_target, size_t t_column_index) const;
            template <class T>
            void getColumn(vector<T> &t_target, size_t t_column_index, size_t t_start_cell_index) const;
            template <class T>
            void getColumn(vector<T> &t_target, size_t t_column_index, size_t t_start_cell_index, size_t t_cell_count) const;
            void reset(void);

        private:
            void updateRowCount(void);
            vector<string> m_data;
            size_t m_row_count;
            size_t m_column_count;
            size_t m_header_count;

    };

    class slightmatrix_error: public exception {};

    class slightmatrix_parameter_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid parameter.";
        }
    };

    class slightmatrix_column_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid column count or index.";
        }
    };

    class slightmatrix_row_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid row count or index.";
        }
    };

    class slightmatrix_matrix_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid matrix (rows incomplete or column count not set).";
        }
    };

} // utils

#endif // _UTILS_SLIGHTMATRIX_HPP