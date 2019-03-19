// SlightCSV - a simple and lightweight CSV parser library
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

using std::string;
using std::vector;

namespace utils {

    class SlightMatrix {

        public:
            SlightMatrix(void);
            void setReserveRowCount(size_t t_res_row_count);
            void setReserveColumnCount(size_t t_res_column_count);
            void reserveMemory(void);
            void setColumnCount(size_t t_column_count);
            size_t getColumnCount(void);
            void addCell(string t_cell);
            void addCells(vector<string> t_cells);
            void finalize(void);
            size_t getRowCount(void);
            string getCell(size_t t_row, size_t t_column);
            void getRow(vector<string> &t_target, size_t t_index);
            template <class T>
            void getColumn(vector<T> &t_target, size_t t_index);
            void reset(void);

        private:
            void updateRowCount(void);
            vector<string> m_data;
            size_t m_res_row_count;
            size_t m_res_column_count;
            size_t m_row_count;
            size_t m_column_count;

    };

} // utils

#endif // _UTILS_SLIGHTMATRIX_HPP