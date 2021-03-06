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

#include "slightmatrix.hpp"

#include <algorithm>

using std::atof;
using std::atoi;

template <class T>
void convertCell(const string &cell_str, T &cell_value);

utils::SlightMatrix::SlightMatrix(void) {
    reset();
}

void utils::SlightMatrix::setCapacity(const size_t t_cell_count) {
    if (!t_cell_count) {
        throw slightmatrix_parameter_error();
    }
    m_data.reserve(t_cell_count);
}

size_t utils::SlightMatrix::getCapacity(void) const {
    return m_data.capacity();
}

void utils::SlightMatrix::setColumnCount(const size_t t_column_count) {
    m_column_count = t_column_count;
}

size_t utils::SlightMatrix::getColumnCount(void) const {
    return m_column_count;
}

void utils::SlightMatrix::addCell(const string t_cell) {
    m_data.push_back(t_cell);
    // after adding cell, re-calculate row count
    updateRowCount();
}

void utils::SlightMatrix::addCells(const vector<string> &t_cells) {
    m_data.insert(m_data.end(), t_cells.begin(), t_cells.end());
    // after adding cells, re-calculate row count
    updateRowCount();
}

void utils::SlightMatrix::setHeaderCount(const size_t t_header_count) {
    m_header_count = t_header_count;
}

size_t utils::SlightMatrix::getHeaderCount(void) const {
    return m_header_count;
}

bool utils::SlightMatrix::validate(void) const {
    if (!m_column_count) {
        return false;
    }
    if (m_header_count >= m_row_count) {
        return false;
    }
    return (m_data.size() % m_column_count == 0) && (m_data.size() == m_row_count * m_column_count) ? true : false;
}

size_t utils::SlightMatrix::getRowCount(void) const {
    return m_row_count;
}

template <class T>
void utils::SlightMatrix::getCell(T &t_value, const size_t t_row_index, const size_t t_column_index) const {
    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_row_index >= m_row_count) {
        throw slightmatrix_row_error();
    }
    if (t_column_index >= m_column_count) {
        throw slightmatrix_column_error();
    }
    string cell = m_data.at(t_row_index * m_column_count + t_column_index);
    convertCell(cell, t_value);
}

template void utils::SlightMatrix::getCell(string &t_value, const size_t t_row_index, 
const size_t t_column_index) const;
template void utils::SlightMatrix::getCell(int &t_value, const size_t t_row_index, 
const size_t t_column_index) const;
template void utils::SlightMatrix::getCell(float &t_value, const size_t t_row_index, 
const size_t t_column_index) const;
template void utils::SlightMatrix::getCell(double &t_value, const size_t t_row_index, 
const size_t t_column_index) const;

void utils::SlightMatrix::getRow(vector<string> &t_target, const size_t t_row_index) const {
    if (t_row_index >= m_row_count) {
        throw slightmatrix_row_error();
    }
    this->getRow(t_target, t_row_index, 0, m_column_count);
}

void utils::SlightMatrix::getRow(vector<string> &t_target, const size_t t_row_index, 
const size_t t_start_cell_index) const {
    if (t_row_index >= m_row_count) {
        throw slightmatrix_row_error();
    }
    if (t_start_cell_index > m_column_count - 1) {
        throw slightmatrix_column_error();
    }
    this->getRow(t_target, t_row_index, t_start_cell_index, m_column_count - t_start_cell_index);
}

void utils::SlightMatrix::getRow(vector<string> &t_target, const size_t t_row_index, 
const size_t t_start_cell_index, const size_t t_cell_count) const {

    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_row_index >= m_row_count) {
        throw slightmatrix_row_error();
    }
    if (t_start_cell_index > m_column_count - 1) {
        throw slightmatrix_column_error();
    }
    if (t_start_cell_index + t_cell_count > m_column_count) {
        throw slightmatrix_column_error();
    }

    // set iterator to first character of row
    vector<string>::const_iterator first = m_data.begin() + t_row_index * m_column_count + t_start_cell_index;
    // set iterator to last character of row
    vector<string>::const_iterator last = first + t_cell_count - 1;

    // clear and fill target
    t_target.clear();
    t_target.reserve(m_row_count);
    for (vector<string>::const_iterator it = first; it <= last; ++it) {
        t_target.push_back(*it);
    }
   
    // for (size_t i = 0; i < m_column_count; ++i) {
    //     string cell = getCell(t_index, i);
    //     t_target.push_back(cell);
    // }
}

template <class T>
void utils::SlightMatrix::getColumn(vector<T> &t_target, const size_t t_column_index) const {
    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_column_index >= m_column_count) {
        throw slightmatrix_column_error();
    }
    this->getColumn(t_target, t_column_index, 0, m_row_count);
}

template void utils::SlightMatrix::getColumn(vector<string> &t_target, const size_t index) const;
template void utils::SlightMatrix::getColumn(vector<int> &t_target, const size_t index) const;
template void utils::SlightMatrix::getColumn(vector<float> &t_target, const size_t index) const;
template void utils::SlightMatrix::getColumn(vector<double> &t_target, const size_t index) const;

template <class T>
void utils::SlightMatrix::getColumn(vector<T> &t_target, const size_t t_column_index, 
const size_t t_start_cell_index) const {
    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_column_index >= m_column_count) {
        throw slightmatrix_column_error();
    }
    if (t_start_cell_index > m_row_count - 1) {
        throw slightmatrix_row_error();
    }
    this->getColumn(t_target, t_column_index, t_start_cell_index, m_row_count - t_start_cell_index);
}

template void utils::SlightMatrix::getColumn(vector<string> &t_target, const size_t index, 
const size_t t_start_cell_index) const;
template void utils::SlightMatrix::getColumn(vector<int> &t_target, const size_t index, 
const size_t t_start_cell_index) const;
template void utils::SlightMatrix::getColumn(vector<float> &t_target, const size_t index, 
const size_t t_start_cell_index) const;
template void utils::SlightMatrix::getColumn(vector<double> &t_target, const size_t index, 
const size_t t_start_cell_index) const;

template <class T>
void utils::SlightMatrix::getColumn(vector<T> &t_target, const size_t t_column_index, 
const size_t t_start_cell_index, const size_t t_cell_count) const {
    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_column_index >= m_column_count) {
        throw slightmatrix_column_error();
    }
    if (t_start_cell_index > m_row_count - 1) {
        throw slightmatrix_row_error();
    }
    if (t_start_cell_index + t_cell_count > m_row_count) {
        throw slightmatrix_row_error();
    }

    // clear and fill target
    t_target.clear();
    t_target.reserve(m_column_count);
    for (size_t i = t_start_cell_index; i < t_start_cell_index + t_cell_count; ++i) {
        T cell;
        getCell(cell, i, t_column_index);
        t_target.push_back(cell);
    }
}

template void utils::SlightMatrix::getColumn(vector<string> &t_target, const size_t index, 
const size_t t_start_cell_index, const size_t t_cell_count) const;
template void utils::SlightMatrix::getColumn(vector<int> &t_target, const size_t index, 
const size_t t_start_cell_index, const size_t t_cell_count) const;
template void utils::SlightMatrix::getColumn(vector<float> &t_target, const size_t index, 
const size_t t_start_cell_index, const size_t t_cell_count) const;
template void utils::SlightMatrix::getColumn(vector<double> &t_target, const size_t index, 
const size_t t_start_cell_index, const size_t t_cell_count) const;

void utils::SlightMatrix::reset(void) {
    m_row_count = 0;
    m_column_count = 0;
    m_header_count = 0;
    // empty vector and release memory
    vector<string>().swap(m_data);
}

void utils::SlightMatrix::updateRowCount(void) {
    if (!m_column_count) {
        return;
    }
    m_row_count = m_data.size() % m_column_count == 0 ? 
        ((size_t)(m_data.size() / m_column_count)) : 
        ((size_t)(m_data.size() / m_column_count)) + 1;
}

template <class T>
void convertCell(const string &cell_str, T &cell_value) {
    cell_value = cell_str;
}

template <>
void convertCell(const string &cell_str, float &cell_value) {
    cell_value = atof(cell_str.c_str());  
}

template <>
void convertCell(const string &cell_str, double &cell_value) {
    cell_value = atof(cell_str.c_str());
}

template <>
void convertCell(const string &cell_str, int &cell_value) {
    cell_value = atoi(cell_str.c_str());
}