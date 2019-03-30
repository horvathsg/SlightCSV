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

#include "slightrow.hpp"

#include <iostream>

using std::cout;
using std::endl;

utils::SlightRow::SlightRow(void) {
    this->reset();
}

void utils::SlightRow::setInput(const string &t_input) {
    if (!t_input.size()) {
        throw slightrow_input_error();
    }
    // clear processing results related fields
    this->clearResults();
    m_input = t_input;
}

string utils::SlightRow::getInput(void) const {
    if (!m_input.size()) {
        throw slightrow_input_error();
    }
    return m_input;
}

void utils::SlightRow::setSeparator(const U8char t_sep) {
    if (!t_sep) {
        throw slightrow_separator_error();
    }
    // clear processing results related fields
    this->clearResults();
    m_sep = t_sep;
}

void utils::SlightRow::getSeparator(U8char &t_target) const {
    if (!m_sep) {
        throw slightrow_separator_error();
    }
    t_target.clear();
    t_target = m_sep;
}

void utils::SlightRow::setEscape(const U8char t_esc) {
    if (!t_esc) {
        throw slightrow_escape_error();
    }
    // clear processing results related fields
    this->clearResults();
    m_esc = t_esc;
}

void utils::SlightRow::getEscape(U8char &t_target) const {
    if (!m_esc) {
        throw slightrow_escape_error();
    }
    t_target.clear();
    t_target = m_esc;
}

void utils::SlightRow::process(void) {
    if (!m_input.size()) {
        throw slightrow_input_error();
    }
    if (!m_sep) {
        throw slightrow_separator_error();
    }

    // define and declare variables used for processing row contents
    string cell = "";
    bool is_escaped = false;
    char c;
    U8char in_u8_char;
    
    // iterate through all characters of input string
    for(size_t i = 0; i < m_input.size(); ++i) {
        c = m_input[i];
        in_u8_char.addChar(c);

        // if UTF8 character is valid (complete)
        if (in_u8_char) {
            
            // if escape character is defined (not zero)
            if (m_esc) {
                // if current character is escape character
                if (in_u8_char == m_esc) {
                    // set escaped state by a XOR
                    // this is an efficient way of keeping track of escape state without using expensive "maps"
                    is_escaped ^= true;
                }
            }
            // if character is not delimiter or it is escaped
            if (in_u8_char != m_sep || is_escaped) {
                // add character to cell buffer
                char char_buff[5] = {0};
                in_u8_char.getChars(char_buff, 4);
                cell += char_buff;
            // if character is delimiter and it is not escaped
            } else {
                // if cell buffer size is not zero
                if (cell.size() != 0) {
                    // insert cell buffer at the end of cells vector
                    m_cells.push_back(cell);
                    // clear cell buffer
                    cell.clear();
                // if cell buffer size is zero (empty field)
                } else {
                    // insert zero at the end of cells vector
                    m_cells.push_back("0");
                }
            }

            in_u8_char.clear();

        }        
    }

    // if there is remainder in cell buffer (row ending characters after last separator)
    if (cell.size()) {
        // insert it at the end of cells vector
        m_cells.push_back(cell);
    }

    // if last character in row is separator and it is not escaped
    U8char u8c;
    u8c.addChar(m_input[m_input.size() - 1]);
    if (u8c == m_sep && !is_escaped) {
        // insert zero at the end of cells vector
        m_cells.push_back("0");
    }

    m_cell_count = m_cells.size();

    m_is_header = this->checkIsHeader();

    m_processed = true;
}

size_t utils::SlightRow::getCellCount(void) const {
    if (!m_processed) {
        throw slightrow_process_error();
    }
    return m_cell_count;
}

size_t utils::SlightRow::getCells(vector<string> &t_target) const {
    if (!m_processed) {
        throw slightrow_process_error();
    }
    t_target = m_cells;
    return m_cells.size();
}

void utils::SlightRow::clearResults(void) {
    m_processed = false;
    m_cell_count = 0;
    m_cells.clear();
    m_is_header = false;
}

void utils::SlightRow::clear(void) {
    this->clearResults();
    m_input.clear();
}

void utils::SlightRow::reset(void) {
    this->clear();
    vector<string>().swap(m_cells);
    m_sep.clear();
    m_esc.clear();
}

bool utils::SlightRow::getIsHeader(void) const {
    if (!m_processed) {
        throw slightrow_process_error();
    }
    return m_is_header;
}

// TODO: examine the possibility of merging header verification with cells extraction in order to save one iteration
// TODO: enhance header detection algorithm
// TODO: make API capable of turning of automatic header detection in order to prevent problems that may arise from false
// positives.
bool utils::SlightRow::checkIsHeader(void) const {
    float num_chars = 0;
    // iterate through all characters of the input string
    for (string::const_iterator it = m_input.begin(); it != m_input.end(); ++it) {
        // if character is numeric, increase counter
        if (*it >= 48 && *it <= 57) {
            ++num_chars;
        }
    }
    // if the ratio of numeric characters is at least 10 percents
    if (num_chars / m_input.size() > 0.1f) {
        // the row is not considered a header
        return false;
    }
    // otherwise the row is considered a header
    return true;
}