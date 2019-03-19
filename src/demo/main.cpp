#include "../../inc/slightcsv/slightcsv.hpp"
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
    csv_parser.setFileName("../../Crimes_-_2001_to_present_1000.csv");
    csv_parser.setSeparator(',');
    StopWatch watch;
    watch.start();
    csv_parser.loadData();
    watch.stop();
    cout << "File contains " << csv_parser.getColumnCount() << " columns." << endl;
    cout << "File contains : " << csv_parser.getRowCount() << " rows." << endl;
    cout << "Header row count: " << csv_parser.getHeaderCount() << "." << endl;
 
    exit(EXIT_SUCCESS);
}