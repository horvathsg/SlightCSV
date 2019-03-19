#include "../inc/slightcsv/slightcsv.hpp"
#include "stopwatch.hpp"
#include "slightmatrix.hpp"

#include <iostream>

using utils::SlightCSV;
using utils::StopWatch;
using utils::SlightMatrix;
using std::cout;
using std::endl;
using std::to_string;

int main(int argc, char *argv[]) {

    SlightCSV csv_parser;
    csv_parser.setFileName("../test/Crimes_-_2001_to_present.csv");
    csv_parser.setSeparator(',');
    StopWatch watch;
    watch.start();
    csv_parser.loadData();
    watch.stop();
    cout << "Loaded CSV row count: " << csv_parser.getRowCount() << "." << endl;
    
    // SlightMatrix sm;
    // //sm.getColumnCount();
    // sm.setColumnCount(30);
    // // sm.reserve(25);
    
    // vector<string> vect;

    // for (int i = 0; i < 259200; ++i) {
    //     vect.push_back(to_string(i));
    // }

    // sm.addCells(vect);

    // cout << sm.getRowCount() << endl;
    
    // SlightMatrix sm;
    // for (size_t i = 1;; i += 1000) {
    //     sm.setCapacity(i);
    // }

    exit(EXIT_SUCCESS);
}