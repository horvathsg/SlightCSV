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

#ifndef _UTILS_SLIGHTCSVPRIVATE_HPP
#define _UTILS_SLIGHTCSVPRIVATE_HPP

#include <string>
#include <vector>
#include <set>
#include <map>

#include "slightmatrix.hpp"
#include "slightrow.hpp"
#include "u8char.hpp"

using std::string;
using std::vector;
using utils::SlightMatrix;
using utils::SlightRow;
using std::set;
using std::map;

namespace utils {
    
    class SlightCSVPrivate {

        public:
            string m_filename;
            U8char m_separator;
            U8char m_escape;
            bool m_csv_format_detect_done;
            SlightMatrix m_data_matrix;
            set<U8char> m_strip_chars;
            map<U8char, U8char> m_rep_chars;
            SlightRow m_row;
            size_t m_file_size;

    };

} // utils

#endif // _UTILS_SLIGHTCSVPRIVATE_HPP