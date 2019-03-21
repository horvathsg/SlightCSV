#include "../../inc/slightcsv/slightcsv.hpp"

#include <iostream>
#include <string>
#include <vector>

using utils::SlightCSV;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char *argv[]) {

    SlightCSV csv_parser;
    csv_parser.setFileName("../../Crimes_-_2001_to_present.csv");
    csv_parser.setSeparator(',');
    csv_parser.setEscape('\"');
    // StopWatch watch;
    // watch.start();
    csv_parser.loadData();
    // watch.stop();
    cout << "File contains " << csv_parser.getColumnCount() << " columns." << endl;
    cout << "File contains " << csv_parser.getRowCount() << " rows." << endl;
    cout << "Header row count: " << csv_parser.getHeaderCount() << "." << endl;
    
    // vector<string> row;
    
    // csv_parser.getRow(row, 500);
    // cout << "Row at index 500 is: " << endl;
    // for (vector<string>::iterator it = row.begin(); it != row.end(); ++it) {
    //     cout << *it << " ";
    // }
    // cout << endl;

    // csv_parser.getColumn(row, 21);
    // cout << "Column at index 21 is: " << endl;
    // for (vector<string>::iterator it = row.begin(); it != row.end(); ++it) {
    //     cout << *it << endl;
    // }

    // exit(EXIT_SUCCESS);
}