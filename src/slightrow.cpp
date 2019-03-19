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

#include "slightrow.hpp"

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::count;

using std::cout;
using std::endl;

utils::SlightRow::SlightRow(void) {
    this->reset();
}

void utils::SlightRow::setInput(string &t_input) {
    if (!t_input.size()) {
        throw slightrow_input_error();
    }
    m_input = t_input;
    m_processed = false;
}

string utils::SlightRow::getInput(void) {
    if (!m_input.size()) {
        throw slightrow_input_error();
    }
    return m_input;
}

void utils::SlightRow::setSeparator(char t_sep) {
    if (t_sep == 0) {
        throw slightrow_separator_error();
    }
    m_sep = t_sep;
    m_processed = false;
}

char utils::SlightRow::getSeparator(void) {
    if (m_sep == 0) {
        throw slightrow_separator_error();
    }
    return m_sep;
}

void utils::SlightRow::process(void) {
    if (!m_input.size()) {
        throw slightrow_input_error();
    }
    if (m_sep == 0) {
        throw slightrow_separator_error();
    }

    string cell;
    size_t cursor = 0;
    char q = '\"';
    size_t sepmap_size = count(m_input.begin(), m_input.end(), m_sep);
    size_t *sepmap = new size_t[sepmap_size];
    bool *qmap = new bool[m_input.size()];
    qmap[0] = false;
    size_t sepmap_idx = 0;

    for (size_t i = 0; i < m_input.size(); ++i) {
        if (m_input.at(i) == m_sep) {
            sepmap[sepmap_idx] = i;
            ++sepmap_idx;
        }
        if (i) {
            qmap[i] = qmap[i-1];
        } 
        if (m_input.at(i) == q) {
            qmap[i] ^= true;
        }
    }

    for (size_t j = 0; j < sepmap_size; ++j) {
        if (qmap[sepmap[j]] == false) {
            if (sepmap[j] - cursor > 0) {
                cell = m_input.substr(cursor, sepmap[j] - cursor);
                m_cells.push_back(cell);
            } else {
                m_cells.push_back("0");
            }
            cursor = sepmap[j] + 1;
        }
    }

    if (cursor < m_input.size()) {
        cell = m_input.substr(cursor, m_input.size() - cursor);
        m_cells.push_back(cell);
    } else if (cursor == m_input.size() && m_input.at(cursor - 1) == m_sep) {
        m_cells.push_back("0");
    }     

    delete[] sepmap;
    delete[] qmap;

    m_cell_count = m_cells.size();

    m_processed = true;
}

size_t utils::SlightRow::getCellCount(void) {
    if (!m_processed) {
        throw slightrow_process_error();
    }
    return m_cell_count;
}

size_t utils::SlightRow::getCells(vector<string> &t_target) {
    if (!m_processed) {
        throw slightrow_process_error();
    }
    t_target = m_cells;
    return m_cells.size();
}

void utils::SlightRow::reset(void) {
    m_processed = false;
    m_input.clear();
    m_sep = 0;
    m_cell_count = 0;
    m_cells.clear();
}