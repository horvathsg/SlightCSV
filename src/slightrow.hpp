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

#ifndef _UTILS_SLIGHTROW_HPP
#define _UTILS_SLIGHTROW_HPP

#include <string>
#include <vector>
#include <exception>

using std::string;
using std::vector;
using std::exception;

namespace utils {

    /// The row class of the library. It is processing extracted line strings into cells.
    class SlightRow {
    
        public:
            /// Default constructor of the class.
            SlightRow(void);

            /// Method to set the input string of the row. Changing the input string invalidates any previous processing
            /// results (it is necessary to process the row again before querying results).
            /// \param t_input input string of the row.
            /// \see getInput()
            void setInput(const string &t_input);
            
            /// Method to get the previously set input string of the row.
            /// \return input string of the row.
            /// \see setInput()
            string getInput(void) const;

            /// Method to set the delimiter character to be used when extracting cells from the row. Changing the 
            /// delimiter character invalidates any previous processins results (it is necessary to process the row 
            /// again before querying results).
            /// \param t_sep delimiter character.
            /// \see getSeparator()
            void setSeparator(const char t_sep);

            /// Method to get the previously set delimiter character to be used when extracting cells from the row.
            /// \return delimiter character.
            /// \see setSeparator()
            char getSeparator(void) const;

            /// Method to set the escape character to be used when extracting cells from the row. Changing the 
            /// escape character invalidates any previous processins results (it is necessary to process the row 
            /// again before querying results).
            /// \param t_esc escape character.
            /// \see getEscape()
            void setEscape(const char t_esc);

            /// Method to get the previously set escape character to be used when extracting cells from the row.
            /// \return escape character.
            /// \see setEscape()
            char getEscape(void) const;

            /// Method to process the row input string and export contents to cells. Input string and delimiter character
            /// settings are required before triggering processing. If those settings are not provided, an excpetion is 
            /// thrown.
            void process(void);

            /// Method to get the number of cells found in the processed row.
            /// \return cell count found in row.
            /// \see getCells()
            /// \see getIsHeader()
            size_t getCellCount(void) const;

            /// Method to get the cells found in the processed row.
            /// \param t_target target variable to add cells to.
            /// \see getCellCount()
            /// \see getIsHeader()
            size_t getCells(vector<string> &t_target) const;

            /// Method to verify if processed row is a header. Automatic header detection is based on a very simple 
            /// algoritm.
            /// \return header flag of processed row.
            /// \see getCellCount()
            /// \see getCells()
            bool getIsHeader(void) const;

            /// Method to clear the processing results related fields of the row. Input string, delimiter and escape 
            /// character settings are preserved.
            /// \see reset()
            void clearResults(void);

            /// Method to clear the input string and processing results related fields of the row. Delimiter and escape 
            /// character settings are preserved.
            /// \see reset()
            void clear(void);

            /// Method to reset the row object to its initial state. No settings are preserved.
            /// \see clear()
            void reset(void);  

        private:
            bool checkIsHeader(void) const;
            string m_input;
            char m_sep;
            char m_esc;
            bool m_processed;
            vector<string> m_cells;
            size_t m_cell_count;
            bool m_is_header;

    };

    /// Base exception of the class (never gets thrown). Inheriting from std::exception.
    class slightrow_error: public exception {};

    /// Exception inheriting from slightrow_error. It is thrown when:
    /// - input string is not set
    /// - input string is empty
    class slightrow_input_error: public slightrow_error {

        const char* what() const throw() {
            return "Input string is not defined or empty.";
        }

    };

    /// Exception inheriting from slightrow_error. It is thrown when:
    /// - separator character is not set
    /// - separator character is not empty
    class slightrow_separator_error: public slightrow_error {

        const char* what() const throw() {
            return "Separator is not defined or empty.";
        }

    };

    /// Exception inheriting from slightrow_error. It is thrown when:
    /// - escape character is not set
    /// - escape character is not empty
    class slightrow_escape_error: public slightrow_error {

        const char* what() const throw() {
            return "Escape character not set.";
        }

    };

    /// Exception inheriting from slightrow_error. It is thrown when:
    /// - calling getter method to get processed row data without processing row first
    class slightrow_process_error: public slightrow_error {

        const char* what() const throw() {
            return "Row not processed.";
        }

    };

} // utils

#endif // _UTILS_SLIGHTROW_HPP