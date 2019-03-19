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

void utils::SlightMatrix::setReserveRowCount(size_t t_res_row_count) {
    m_res_row_count = t_res_row_count;
}

void utils::SlightMatrix::setReserveColumnCount(size_t t_res_column_count) {
    m_res_column_count = t_res_column_count;
}

void utils::SlightMatrix::reserveMemory(void) {
    m_data.reserve(m_res_row_count * m_res_column_count);
}

void utils::SlightMatrix::setColumnCount(size_t t_column_count) {
    m_column_count = t_column_count;
}

size_t utils::SlightMatrix::getColumnCount(void) {
    return m_column_count;
}

void utils::SlightMatrix::addCell(string t_cell) {
    m_data.push_back(t_cell);
}

void utils::SlightMatrix::addCells(vector<string> t_cells) {
    m_data.insert(m_data.end(), t_cells.begin(), t_cells.end());
}

void utils::SlightMatrix::finalize(void) {

}

size_t utils::SlightMatrix::getRowCount(void) {
    updateRowCount();
    return m_row_count;
}

string utils::SlightMatrix::getCell(size_t t_row, size_t t_column) {
    return m_data.at(t_row * m_column_count + t_column);
}

void utils::SlightMatrix::getRow(vector<string> &t_target, size_t t_index) {
    t_target.clear();
    for (size_t i = 0; i < m_column_count; ++i) {
        string cell = getCell(t_index, i);
        t_target.push_back(cell);
    }
}

template <class T>
void utils::SlightMatrix::getColumn(vector<T> &t_target, size_t t_index) {
    t_target.clear();
    for (size_t i = 0; i < m_row_count; ++i) {
        string cell = getCell(i, t_index);
        T cell_value;
        convertCell(cell, cell_value);
        t_target.push_back(cell_value);
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
    m_data.reserve(1);
}

void utils::SlightMatrix::updateRowCount(void) {
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