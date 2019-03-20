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

#include "slightcsv.hpp"
#include "slightcsvprivate.hpp"
#include "slightrow.hpp"

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>

using std::string;
using std::vector;
using std::clog;
using std::endl;
using std::stof;
using std::stod;
using std::stoi;
using std::replace;
using std::fread;

using std::cout;
using std::cin;

#define VERBOSE 0

utils::SlightCSV::SlightCSV(void) {
    m_csvp = new SlightCSVPrivate;
    this->reset();
}

utils::SlightCSV::~SlightCSV(void) {
    delete m_csvp;
}

void utils::SlightCSV::setFileName(string t_filename) {
    if (!t_filename.size()) {
        throw slightcsv_filename_error();
    }
    m_csvp->m_filename = t_filename;
}

string utils::SlightCSV::getFileName(void) const {
    if (!m_csvp->m_filename.size()) {
        throw slightcsv_filename_error();
    }
    return m_csvp->m_filename;
}

void utils::SlightCSV::setSeparator(char t_separator) {
    if (!t_separator) {
        throw slightcsv_separator_error();
    }
    m_csvp->m_separator = t_separator;
}

char utils::SlightCSV::getSeparator(void) const {
    if (!m_csvp->m_separator) {
        throw slightcsv_separator_error();
    }
    return m_csvp->m_separator;
}

size_t utils::SlightCSV::loadData(void) {

    if (!m_csvp->m_filename.size()) {
        throw slightcsv_filename_error();
    }

    if (m_csvp->m_separator == 0) {
        throw slightcsv_separator_error();
    }

    size_t retval = 0;

    FILE *in_file;
    
    in_file = fopen(m_csvp->m_filename.c_str(), "rb");
    if (!in_file) {
        throw slightcsv_filename_error();
    }

    // size_t file_size;
    // fseek(in_file, 0L, SEEK_END);
    // file_size = ftell(in_file);
    // fseek(in_file, 0L, SEEK_SET);

    // vector<size_t> rnmap;
    // char q = '\"';
    // int in_char;
    // size_t cursor = 0;
    // string rows;

    // vector<bool> qmap(file_size);

    // qmap[0] = false;

    // size_t row_count = 0;
    // size_t last_sep_idx = 0;

    // for (size_t i = 0; i < file_size; ++i) {
    //     in_char = fgetc(in_file);
    //     if (in_char == EOF) {
    //         throw slightcsv_read_error();
    //     }
    //     if (i) {
    //         qmap[i] = qmap[i-1];
    //     }
    //     if (in_char == q) {
    //         qmap[i] = qmap[i]^true;
    //     }
    //     if (in_char == '\r' || in_char == '\n') {
    //         if (qmap[i] == false) {
    //             rnmap.push_back(i);
    //             if (i - last_sep_idx > 1) {
    //                 ++row_count;
    //                 last_sep_idx = i;
    //             }
    //         } else {
    //             // escaped line ending
    //         }
    //     }
    // }

    // //m_csvp->m_data_matrix.setReserveRowCount(row_count);
    // m_csvp->m_data_matrix.setCapacity(row_count);

    // fseek(in_file, 0L, SEEK_SET);

    // size_t row_id = 0;

    // for (size_t j = 0; j < rnmap.size(); ++j) {
    //     if (rnmap.at(j) - cursor > 0) {
    //         char *row = new char[rnmap.at(j) - cursor + 1];
    //         size_t cnt = fread(row, sizeof(char), rnmap.at(j) - cursor, in_file);
    //         row[cnt] = 0;
    //         string rows = row;
    //         delete[] row;
    //         processLine(rows, row_id);
    //         ++row_id;
    //     } else {
    //         // row is empty
    //     }
    //     fseek(in_file, 1L, SEEK_CUR);
    //     cursor = rnmap.at(j) + 1;
    // }

    // if (cursor < file_size) {

    //     char *row = new char[file_size - cursor + 1];
    //     size_t cnt = fread(row, sizeof(char), file_size - cursor, in_file);
    //     row[cnt] = 0;
    //     string rows = row;
    //     delete[] row;
    //     processLine(rows, row_id);
    //     ++row_id;

    // }

    // fclose(in_file);
    

    char in_char;
    string in_line = "";
    bool is_escaped = false;
    size_t row_id = 0;

    while (in_char = fgetc(in_file), in_char != EOF) {
        if (in_char == '\"') {
            is_escaped ^= true;
        }
        if ((in_char != '\r' && in_char != '\n') || is_escaped) {
            in_line.append((char*)&in_char);
        } else {
            if (in_line.size()) {
                processLine(in_line, row_id);
                in_line.clear();
                ++row_id;
            }
        }
    }

    processLine(in_line, row_id);

    fclose(in_file);


    //m_csvp->m_row_count = m_csvp->m_data_matrix.getRowCount();
    retval = m_csvp->m_data_matrix.getRowCount();

    return retval;
}

size_t utils::SlightCSV::getColumnCount(void) const {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    return m_csvp->m_data_matrix.getColumnCount();
}

size_t utils::SlightCSV::getRowCount(void) const {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    return m_csvp->m_data_matrix.getRowCount();
}

void utils::SlightCSV::setHeaderCount(size_t t_header_count) {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    m_csvp->m_data_matrix.setHeaderCount(t_header_count);
}

size_t utils::SlightCSV::getHeaderCount(void) const {
    return m_csvp->m_data_matrix.getHeaderCount();
}

template <class T>
void utils::SlightCSV::getCell(T &t_value, size_t t_row_index, size_t t_column_index) const {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    if (t_row_index >= m_csvp->m_data_matrix.getRowCount()) {
        throw slightcsv_index_error();
    }
    if (t_column_index >= m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_index_error();
    }
    m_csvp->m_data_matrix.getCell(t_value, t_row_index, t_column_index);
}

template void utils::SlightCSV::getCell(string &t_value, size_t t_row_index, size_t t_column_index) const;
template void utils::SlightCSV::getCell(int &t_value, size_t t_row_index, size_t t_column_index) const;
template void utils::SlightCSV::getCell(float &t_value, size_t t_row_index, size_t t_column_index) const;
template void utils::SlightCSV::getCell(double &t_value, size_t t_row_index, size_t t_column_index) const;

template <class T>
void utils::SlightCSV::getColumn(vector<T> &t_target_column, size_t t_column_index) const {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    if (t_column_index >= m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_index_error();
    }

    m_csvp->m_data_matrix.getColumn(t_target_column, t_column_index);
}

template void utils::SlightCSV::getColumn(vector<int> &t_target_column, size_t t_column_index) const;
template void utils::SlightCSV::getColumn(vector<float> &t_target_column, size_t t_column_index) const;
template void utils::SlightCSV::getColumn(vector<double> &t_target_column, size_t t_column_index) const;
template void utils::SlightCSV::getColumn(vector<string> &t_target_column, size_t t_column_index) const;

template <class T>
void utils::SlightCSV::getColumn(vector<T> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index) const {

    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    if (t_column_index >= m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_index_error();
    }
    if (t_start_cell_index > m_csvp->m_data_matrix.getRowCount() - 1) {
        throw slightcsv_index_error();
    }
    m_csvp->m_data_matrix.getColumn(t_target_column, t_column_index, t_start_cell_index);
}

template void utils::SlightCSV::getColumn(vector<int> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index) const;
template void utils::SlightCSV::getColumn(vector<float> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index) const;
template void utils::SlightCSV::getColumn(vector<double> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index) const;
template void utils::SlightCSV::getColumn(vector<string> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index) const;

template <class T>
void utils::SlightCSV::getColumn(vector<T> &t_target_column, size_t t_column_index, size_t t_start_cell_index, 
    size_t t_cell_count) const {

    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    if (t_column_index >= m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_index_error();
    }
    if (t_start_cell_index > m_csvp->m_data_matrix.getRowCount() - 1) {
        throw slightcsv_index_error();
    }
    if (t_start_cell_index + t_cell_count > m_csvp->m_data_matrix.getRowCount()) {
        throw slightcsv_index_error();
    }
    m_csvp->m_data_matrix.getColumn(t_target_column, t_column_index, t_start_cell_index, t_cell_count);
}

template void utils::SlightCSV::getColumn(vector<int> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index, size_t t_cell_count) const;
template void utils::SlightCSV::getColumn(vector<float> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index, size_t t_cell_count) const;
template void utils::SlightCSV::getColumn(vector<double> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index, size_t t_cell_count) const;
template void utils::SlightCSV::getColumn(vector<string> &t_target_column, size_t t_column_index, 
    size_t t_start_cell_index, size_t t_cell_count) const;

void utils::SlightCSV::getRow(vector<string> &t_target_row, size_t t_row_index) const {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    if (t_row_index >= m_csvp->m_data_matrix.getRowCount()) {
        throw slightcsv_index_error();
    }

    m_csvp->m_data_matrix.getRow(t_target_row, t_row_index);
}

void utils::SlightCSV::getRow(vector<string> &t_target_row, size_t t_row_index, size_t t_start_cell_index) const {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    if (t_row_index >= m_csvp->m_data_matrix.getRowCount()) {
        throw slightcsv_index_error();
    }
    if (t_start_cell_index > m_csvp->m_data_matrix.getColumnCount() - 1) {
        throw slightcsv_index_error();
    }
    m_csvp->m_data_matrix.getRow(t_target_row, t_row_index, t_start_cell_index);
}

void utils::SlightCSV::getRow(vector<string> &t_target_row, size_t t_row_index, size_t t_start_cell_index, 
size_t t_cell_count) const {

    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    if (t_row_index >= m_csvp->m_data_matrix.getRowCount()) {
        throw slightcsv_index_error();
    }
    if (t_start_cell_index > m_csvp->m_data_matrix.getColumnCount() - 1) {
        throw slightcsv_index_error();
    }
    if (t_start_cell_index + t_cell_count > m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_index_error();
    }
    m_csvp->m_data_matrix.getRow(t_target_row, t_row_index, t_start_cell_index, t_cell_count);
}

void utils::SlightCSV::unloadData(void) {
    if (!m_csvp->m_data_matrix.getRowCount() || !m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_data_error();
    }
    m_csvp->m_data_matrix.reset();
    m_csvp->m_csv_format_detect_done = false;
}

void utils::SlightCSV::reset(void) {
    m_csvp->m_data_matrix.reset();
    m_csvp->m_filename.clear();
    m_csvp->m_separator = 0;
    m_csvp->m_csv_format_detect_done = false;
}

void utils::SlightCSV::processLine(string &t_input, size_t t_row_id) {

    if (!t_input.size()) {
        #if VERBOSE == 1
        clog << "Row " << t_row_id << " empty." << endl;
        #endif
        return;
    }

    SlightRow row;
    row.setInput(t_input);
    row.setSeparator(m_csvp->m_separator);
    row.process();

    if (!m_csvp->m_csv_format_detect_done) {
        //size_t cap = m_csvp->m_data_matrix.getCapacity();
        //m_csvp->m_data_matrix.setCapacity(cap * row.getCellCount());
        m_csvp->m_data_matrix.setColumnCount(row.getCellCount());
        m_csvp->m_csv_format_detect_done = true;
    }

    if (row.getIsHeader()) {
        size_t header_count = m_csvp->m_data_matrix.getHeaderCount();
        if (t_row_id == header_count) {
            m_csvp->m_data_matrix.setHeaderCount(++header_count);
        } else {
            throw slightcsv_format_header_error();
        }
    }

    if (row.getCellCount() != m_csvp->m_data_matrix.getColumnCount()) {
        // cout << "Cell count " << row.getCellCount() << " in row " << t_row_id << endl;
        throw slightcsv_format_cellcnt_error();
    }
    
    vector<string> cells;
    row.getCells(cells);
    m_csvp->m_data_matrix.addCells(cells);

}