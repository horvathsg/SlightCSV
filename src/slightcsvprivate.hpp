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

#ifndef _UTILS_SLIGHTCSVPRIVATE_HPP
#define _UTILS_SLIGHTCSVPRIVATE_HPP

#include <string>
#include <vector>

#include "slightmatrix.hpp"

using std::string;
using std::vector;
using utils::SlightMatrix;

namespace utils {
    
    class SlightCSVPrivate {

        public:
            string m_filename;
            char m_separator;
            bool m_csv_format_detect_done;
            SlightMatrix m_data_matrix;
            size_t m_col_count;
            size_t m_row_count;

    };

} // utils

#endif // _UTILS_SLIGHTCSVPRIVATE_HPP