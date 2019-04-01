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

#include "../../inc/slightcsv/slightcsv.hpp"

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>

using std::string;
using std::vector;
using std::set;
using std::pair;
using std::map;
using std::cout;
using std::endl;
using utils::SlightCSV;

int main(int argc, char *argv[]) {

    // construct object
    SlightCSV scsv;

    // set filename
    scsv.setFileName("../test/utf8_test.csv");
    
    // set delimiter character (semicolon)
    scsv.setSeparator(";");
    
    // set escape character (double quote)
    scsv.setEscape("\"");
    
    // set characters to be stripped (stip spaces and underscores)
    set<string> to_strip;
    to_strip.insert(" ");
    to_strip.insert("_");
    scsv.setStripChars(to_strip);
    
    // set characters to be replaced (replace 'a' with 'b' and 'c' with 'd')
    map<string, string> to_replace;
    pair<string, string> to_replace1("a", "b");
    pair<string, string> to_replace2("c", "d");
    to_replace.insert(to_replace1);
    to_replace.insert(to_replace2);
    scsv.setReplaceChars(to_replace);

    // load data
    scsv.loadData();
    
    // output entity counts
    cout << "File contains " << scsv.getColumnCount() << " columns." << endl;
    cout << "File contains " << scsv.getRowCount() << " rows." << endl;
    cout << "Header count: " << scsv.getHeaderCount() << " rows." << endl;

    // output row 1 (at index 0)
    vector<string> row0;
    scsv.getRow(row0, 0);
    cout << "Row 1 is: " << endl;
    for (vector<string>::iterator it = row0.begin(); it != row0.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // output row 2 (at index 1)
    vector<string> row1;
    scsv.getRow(row1, 1);
    cout << "Row 2 is: " << endl;
    for (vector<string>::iterator it = row1.begin(); it != row1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // output column 1 (at index 0)
    vector<string> column;
    scsv.getColumn(column, 0);
    cout << "Column 1 is: " << endl;
    for (vector<string>::iterator it = column.begin(); it != column.end(); ++it) {
        cout << *it << endl;
    }

    // reset object to initial state (before reuse, e.g. loading another file)
    scsv.reset();

}