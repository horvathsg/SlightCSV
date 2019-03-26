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

#ifndef _UTILS_SLIGHTMATRIX_HPP
#define _UTILS_SLIGHTMATRIX_HPP

#include <string>
#include <vector>
#include <exception>

using std::string;
using std::vector;
using std::exception;

namespace utils {

    /// The data storege class of the library. It is storing data in a single vector and mapping cells, rows and columns
    /// based on matrix format data.
    class SlightMatrix {

        public:
            /// The class's default constructor.
            SlightMatrix(void);

            /// Method to allocate and reserve memory for the given number of cells in the data store. It reserves memory
            /// only for cells, not for strings representing cell contents.
            /// \param t_cell_count number of cells to reserve memory for.
            /// \see getCapacity()
            void setCapacity(size_t t_cell_count);

            /// Method to query the amount of cells memory is reserved for in the data matrix.
            /// \return number of cells memory is reserved for.
            /// \see setCapacity()
            size_t getCapacity(void) const;

            /// Method to set the number of columns the data matrix consists of. Without this, the format of the matrix
            /// is undetermined, thus invalid (if the column count is not known, it is not possible to map the cells and 
            /// rows).
            /// \param t_column_count number of columns the data matrix consists of.
            /// \see getColumnCount()
            void setColumnCount(size_t t_column_count);

            /// Method to get the previously set column count.
            /// \return number of columns the data matrix consists of.
            /// \see setColumnCount()
            size_t getColumnCount(void) const;

            /// Method to add single cells (in a continuous manner) to the data matrix. The cell is added at the end of the
            /// vector holding cells. Column and row mapping is determined automatically (based on column count).
            /// \param t_cell string contents of the cell to add.
            /// \see addCells()
            /// \see getCell()
            void addCell(string t_cell);

            /// Method to add multiple cells (vector of cells) to the data matrix. Cells are added at the end of the
            /// vector holding cells. Column and row mapping is determined automatically (based on column count).
            /// \param t_cells contents of the cells to add.
            /// \see addCell()
            /// \see getCell()
            void addCells(vector<string> &t_cells);

            /// Method to set the number of header rows the data matrix contains.
            /// \param t_header_count number of header rows the data matrix contains.
            /// \see getHeaderCount()
            void setHeaderCount(size_t t_header_count);

            /// Method to get the (automatically detected or previously set) number of header rows the data matrix contains.
            /// \return number of header rows the data matrix contains.
            /// \see setHeaderCount()
            size_t getHeaderCount(void) const;

            /// Method to validate cell format and contents. Data query methods automatically call this method and only 
            /// return results on valid data matrices. A valid matrix (1) has its column count set, (2) has less header 
            /// rows than total rows and (3) does not contain a last row which has missing cells (all rows are filled 
            /// with cells).
            bool validate(void) const;

            /// Method the get the number of rows the data matrix consists of. The value depends on the number of 
            /// columns set and the number of cells added.
            /// \return the number of rows the data matrix consists of.
            /// \see setColumnCount()
            /// \see getColumnCount()
            size_t getRowCount(void) const;

            /// Method to get the contents of a specific cell. The internal data structure stores cell values as strings.
            /// When using the method, the library tries to convert the string contents to the type supplied as the 
            /// first parameter of the method. Supported types: int, float, double, string. If conversion fails,
            /// the value returned will be 0. In this case, it is always possible to get the value as string.
            /// \param t_value variable to hold the value of the cell.
            /// \param t_row_index index (starting from 0) of the row the cell queried.
            /// \param t_column_index index (starting from 0) of the column holding the cell queried.
            /// \see addCell()
            /// \see addCells()
            /// \see getRow()
            /// \see getColumn()
            template <class T>
            void getCell(T &t_value, size_t t_row_index, size_t t_column_index) const;

            /// Method to get the cells of a specific row. The row is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library
            /// returns cells in a row as strings.
            /// \param t_target_row vector to hold the values of the cells in the row.
            /// \param t_row_index index (starting from 0) of the row to be returned.
            /// \see getColumn()
            /// \see getCell()            
            void getRow(vector<string> &t_target_row, size_t t_row_index) const;

            /// \overload
            /// Method to get the cells of a specific row. The row is represented in the form of a vector.
            /// The internal data structure stores cell values as strings. When using the method, the library
            /// returns cells in a row as strings.
            /// \param t_target_row vector to hold the values of the cells in the row.
            /// \param t_row_index index (starting from 0) of the row to be returned.
            /// \param t_start_cell_index index (starting from 0) of the first horizontal cell (filtering).
            /// \see getColumn()
            /// \see getCell()
            void getRow(vector<string> &t_target_row, size_t t_row_index, size_t t_start_cell_index) const;

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
            void getRow(vector<string> &t_target_row, size_t t_row_index, size_t t_start_cell_index, size_t t_cell_count) const;
            
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
            void getColumn(vector<T> &t_target_column, size_t t_column_index) const;

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
            void getColumn(vector<T> &t_target_column, size_t t_column_index, size_t t_start_cell_index) const;

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
            void getColumn(vector<T> &t_target_column, size_t t_column_index, size_t t_start_cell_index, size_t t_cell_count) const;
            
            /// Method to reset data matrix to its initial state.
            void reset(void);

        private:
            void updateRowCount(void);
            vector<string> m_data;
            size_t m_row_count;
            size_t m_column_count;
            size_t m_header_count;

    };

    /// Base exception of the class (never gets thrown). Inheriting from std::exception.
    class slightmatrix_error: public exception {};

    /// Exception inheriting from slightmatrix_error. It is thrown when:
    /// - method is called with zero or empty parameter
    class slightmatrix_parameter_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid parameter.";
        }
    };

    /// Exception inheriting from slightmatrix_error. It is thrown when:
    /// - method is called with invalid or out-of-range column count or index.
    class slightmatrix_column_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid column count or index.";
        }
    };

    /// Exception inheriting from slightmatrix_error. It is thrown when:
    /// - method is called with invalid or out-of-range row count or index.
    class slightmatrix_row_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid row count or index.";
        }
    };

    /// Exception inheriting from slightmatrix_error. It is thrown when:
    /// - matrix format is not valid.
    /// \see validate()
    class slightmatrix_matrix_error: public slightmatrix_error {
        const char* what() const throw() {
            return "Invalid matrix (rows incomplete or column count not set).";
        }
    };

} // utils

#endif // _UTILS_SLIGHTMATRIX_HPP