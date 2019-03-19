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

#ifndef _UTILS_SLIGHTROW_HPP
#define _UTILS_SLIGHTROW_HPP

#include <string>
#include <vector>
#include <exception>

using std::string;
using std::vector;
using std::exception;

namespace utils {

    class SlightRow {
    
        public:
            SlightRow(void);
            void setInput(string &t_input);
            string getInput(void) const;
            void setSeparator(char t_sep);
            char getSeparator(void) const;
            void process(void);
            size_t getCellCount(void) const;
            size_t getCells(vector<string> &t_target) const;
            bool getIsHeader(void) const;
            void reset(void);

        private:
            bool checkIsHeader(void) const;
            string m_input;
            char m_sep;
            bool m_processed;
            vector<string> m_cells;
            size_t m_cell_count;
            bool m_is_header;

    };

    class slightrow_error: public exception {};

    class slightrow_input_error: public slightrow_error {

        const char* what() const throw() {
            return "Input string is not defined or empty.";
        }

    };

    class slightrow_separator_error: public slightrow_error {

        const char* what() const throw() {
            return "Separator is not defined or empty.";
        }

    };

    class slightrow_process_error: public slightrow_error {

        const char* what() const throw() {
            return "Row not processed.";
        }

    };

} // utils

#endif // _UTILS_SLIGHTROW_HPP