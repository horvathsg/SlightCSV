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

#include "slightcsv.hpp"
#include "slightcsvprivate.hpp"
#include "slightrow.hpp"

#include <cstdio>

utils::SlightCSV::SlightCSV(void) {
    // allocate object holding data members dynamically
    m_csvp = new SlightCSVPrivate;
    this->reset();
}

utils::SlightCSV::~SlightCSV(void) {
    // de-allocate data member object
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
    // TODO: store value in one place only (SlightRow would be a more logical choice as it directly needs the delimiter) 
    m_csvp->m_separator = t_separator;
    m_csvp->m_row.setSeparator(t_separator);
}

char utils::SlightCSV::getSeparator(void) const {
    if (!m_csvp->m_separator) {
        throw slightcsv_separator_error();
    }
    return m_csvp->m_separator;
}

void utils::SlightCSV::setEscape(char t_escape) {
    if (!t_escape) {
        throw slightcsv_escape_error();
    }
    // TODO: store value in one place only (even though it is needed for file and row-level parsing as well)
    m_csvp->m_escape = t_escape;
    m_csvp->m_row.setEscape(t_escape);
}

char utils::SlightCSV::getEscape(void) const {
    if (!m_csvp->m_escape) {
        throw slightcsv_escape_error();
    }
    return m_csvp->m_escape;
}

void utils::SlightCSV::setStripChars(set<char> &t_strip_chars) {
    if (!t_strip_chars.size()) {
        throw slightcsv_strip_error();
    }
    m_csvp->m_strip_chars = t_strip_chars;
}

void utils::SlightCSV::getStripChars(set<char> &t_target) const {
    if (!m_csvp->m_strip_chars.size()) {
        throw slightcsv_strip_error();
    }
    t_target = m_csvp->m_strip_chars;
}

void utils::SlightCSV::setReplaceChars(map<char, char> &t_rep_chars) {
    if (!t_rep_chars.size()) {
        throw slightcsv_replace_error();
    }
    m_csvp->m_rep_chars = t_rep_chars;
}

void utils::SlightCSV::getReplaceChars(map<char, char> &t_target) const {
    if (!m_csvp->m_rep_chars.size()) {
        throw slightcsv_replace_error();
    }
    t_target = m_csvp->m_rep_chars;
}

size_t utils::SlightCSV::loadData(void) {

    if (!m_csvp->m_filename.size()) {
        throw slightcsv_filename_error();
    }

    if (m_csvp->m_separator == 0) {
        throw slightcsv_separator_error();
    }

    size_t retval = 0;

    // open file for processing
    FILE *in_file = fopen(m_csvp->m_filename.c_str(), "rb");
    if (!in_file) {
        throw slightcsv_filename_error();
    }

    // get file size in order to support resource allocation (row count not known in advance)
    fseek(in_file, 0L, SEEK_END);
    m_csvp->m_file_size = ftell(in_file);
    fseek(in_file, 0L, SEEK_SET);
    
    // set up variables to be used in parsing cycle
    char in_char;
    string in_line = "";
    bool is_escaped = false;
    size_t row_id = 0;

    // parse the file character by character
    while (in_char = fgetc(in_file), in_char != EOF) {
        // if there is at least one character to be stripped
        if (m_csvp->m_strip_chars.size()) {
                // if the incoming character is present in the strip set
                if (m_csvp->m_strip_chars.count(in_char)) {
                    // don't put it in the buffer
                    continue;
                }
            }
        // if the escape character is set
        if (m_csvp->m_escape) {
            // if the incoming character matches the escape character
            if (in_char == m_csvp->m_escape) {
                // set escaped state by a XOR
                // this is an efficient way of keeping track of escape state without using expensive "maps"
                is_escaped ^= true;
            }
        }
        // if incoming character is not newline, or if the character is escaped
        if ((in_char != '\r' && in_char != '\n') || is_escaped) {
            // if there are any characters to be replaced
            if (m_csvp->m_rep_chars.size()) {
                // check if the incoming character needs to be replaced
                map<char, char>::const_iterator it = m_csvp->m_rep_chars.find(in_char);
                // if incoming character needs to be replaced
                if (it != m_csvp->m_rep_chars.end()) {
                    // replace "replacee" with "replacer"
                    in_char = it->second;
                }
            }
            // add character to line buffer
            in_line += in_char;
        // if incoming character is newline, and it is not escaped
        } else {
            // if incoming line is not empty (might be if two new lines follow each other, e.g. \r\n)
            if (in_line.size()) {
                // submit line for processing with row id
                processLine(in_line, row_id);
                // clear line buffer
                in_line.clear();
                // increment row id
                ++row_id;
            }
        }
    }
    // submit remaining characters for processing with row id (needed because there might be no new line character at the 
    // end of the last row to trigger processing)
    processLine(in_line, row_id);

    // close file
    fclose(in_file);

    // set return value (number if rows processed)
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
    m_csvp->m_row.clear();
    m_csvp->m_file_size = 0;
}

void utils::SlightCSV::reset(void) {
    m_csvp->m_data_matrix.reset();
    m_csvp->m_filename.clear();
    m_csvp->m_separator = 0;
    m_csvp->m_escape = 0;
    m_csvp->m_strip_chars.clear();
    m_csvp->m_csv_format_detect_done = false;
    m_csvp->m_row.reset();
    m_csvp->m_file_size = 0;
}

void utils::SlightCSV::processLine(string &t_input, size_t t_row_id) {

    if (!t_input.size()) {
        return;
    }

    // clear row
    m_csvp->m_row.clear();
    
    // set row input
    m_csvp->m_row.setInput(t_input);
    
    // process row
    m_csvp->m_row.process();

    // determine column count from the first row processed
    // reserve memory for the estimated number of cells (based on file size, row size and cell count in row)
    if (!m_csvp->m_csv_format_detect_done) {
        m_csvp->m_data_matrix.setCapacity(m_csvp->m_file_size / t_input.size() * m_csvp->m_row.getCellCount());
        m_csvp->m_data_matrix.setColumnCount(m_csvp->m_row.getCellCount());
        m_csvp->m_csv_format_detect_done = true;
    }

    // check if row is header
    // multiple headers are allowed, but only at the beginning of the file
    // if a non-header comes after a header, more headers are not allowed (exception is thrown)
    // TODO: make approximate row number available in the exception
    if (m_csvp->m_row.getIsHeader()) {
        size_t header_count = m_csvp->m_data_matrix.getHeaderCount();
        if (t_row_id == header_count) {
            m_csvp->m_data_matrix.setHeaderCount(++header_count);
        } else {
            throw slightcsv_format_header_error();
        }
    }

    // if cell count is not consistent, an exception is thrown
    // TODO: make approximate row number available in the exception
    if (m_csvp->m_row.getCellCount() != m_csvp->m_data_matrix.getColumnCount()) {
        throw slightcsv_format_cellcnt_error();
    }
    
    // get parsed cells from row
    vector<string> cells;
    m_csvp->m_row.getCells(cells);
    
    // add cells to data matrix
    m_csvp->m_data_matrix.addCells(cells);

}