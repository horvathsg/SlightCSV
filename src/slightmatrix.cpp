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

#include "slightmatrix.hpp"

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::replace;
using std::stof;
using std::stod;
using std::stoi;

template <class T>
void convertCell(string &cell_str, T &cell_value);

utils::SlightMatrix::SlightMatrix(void) {
    reset();
}

void utils::SlightMatrix::setCapacity(size_t t_cell_count) {
    if (!t_cell_count) {
        throw slightmatrix_parameter_error();
    }
    try {
        m_data.reserve(t_cell_count);
    } catch (exception &e) {
        throw slightmatrix_alloc_error();
    }
}

size_t utils::SlightMatrix::getCapacity(void) {
    return m_data.capacity();
}

void utils::SlightMatrix::setColumnCount(size_t t_column_count) {
    m_column_count = t_column_count;
}

size_t utils::SlightMatrix::getColumnCount(void) {
    return m_column_count;
}

void utils::SlightMatrix::addCell(string t_cell) {
    try {
        m_data.push_back(t_cell);
    } catch (exception &e) {
        throw slightmatrix_alloc_error();
    }
    updateRowCount();
}

void utils::SlightMatrix::addCells(vector<string> t_cells) {
    try {
        m_data.insert(m_data.end(), t_cells.begin(), t_cells.end());
    } catch (exception &e) {
        throw slightmatrix_alloc_error();
    }
    updateRowCount();
}

bool utils::SlightMatrix::validate(void) {
    if (!m_column_count) {
        return false;
    }
    return (m_data.size() % m_column_count == 0) && (m_data.size() == m_row_count * m_column_count) ? true : false;
}

size_t utils::SlightMatrix::getRowCount(void) {
    return m_row_count;
}

string utils::SlightMatrix::getCell(size_t t_row_index, size_t t_column_index) {
    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_row_index >= m_row_count) {
        throw slightmatrix_row_error();
    }
    if (t_column_index >= m_column_count) {
        throw slightmatrix_column_error();
    }
    return m_data.at(t_row_index * m_column_count + t_column_index);
}

void utils::SlightMatrix::getRow(vector<string> &t_target, size_t t_row_index) {
    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_row_index >= m_row_count) {
        throw slightmatrix_row_error();
    }
    
    vector<string>::const_iterator first = m_data.begin() + t_row_index * m_column_count;
    vector<string>::const_iterator last = m_data.begin() + (t_row_index + 1) * m_column_count - 1;

    t_target.clear();

    try {
        t_target.reserve(m_row_count);
        for (vector<string>::const_iterator it = first; it <= last; ++it) {
            t_target.push_back(*it);
        }
    } catch (exception &e) {
        throw slightmatrix_alloc_error();
    }    

    // for (size_t i = 0; i < m_column_count; ++i) {
    //     string cell = getCell(t_index, i);
    //     t_target.push_back(cell);
    // }
}

template <class T>
void utils::SlightMatrix::getColumn(vector<T> &t_target, size_t t_column_index) {
    if (!validate()) {
        throw slightmatrix_matrix_error();
    }
    if (t_column_index >= m_column_count) {
        throw slightmatrix_column_error();
    }

    t_target.clear();

    try {
        t_target.reserve(m_column_count);
        for (size_t i = 0; i < m_row_count; ++i) {
            string cell = getCell(i, t_column_index);
            T cell_value;
            convertCell(cell, cell_value);
            t_target.push_back(cell_value);
        }
    } catch (exception &e) {
        throw slightmatrix_alloc_error();
    }
}

template void utils::SlightMatrix::getColumn(vector<string> &t_target, size_t index);
template void utils::SlightMatrix::getColumn(vector<int> &t_target, size_t index);
template void utils::SlightMatrix::getColumn(vector<float> &t_target, size_t index);
template void utils::SlightMatrix::getColumn(vector<double> &t_target, size_t index);

void utils::SlightMatrix::reset(void) {
    m_row_count = 0;
    m_column_count = 0;
    m_data.clear();
    try {
        m_data.shrink_to_fit();
    } catch (exception &e) {
        throw slightmatrix_alloc_error();
    }
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
void convertCell(string &cell_str, T &cell_value) {
    cell_value = cell_str;
}

template <>
void convertCell(string &cell_str, float &cell_value) {
    replace(cell_str.begin(), cell_str.end(), char(44), char(46));
    try {
        cell_value = stof(cell_str);
    } catch (...) {
        cell_value = 0;
    }   
}

template <>
void convertCell(string &cell_str, double &cell_value) {
    replace(cell_str.begin(), cell_str.end(), char(44), char(46));
    try {
        cell_value = stod(cell_str);
    } catch (...) {
        cell_value = 0;
    }
}

template <>
void convertCell(string &cell_str, int &cell_value) {
    replace(cell_str.begin(), cell_str.end(), char(44), char(46));
    try {
        cell_value = stoi(cell_str);
    } catch (...) {
        cell_value = 0;
    }
}