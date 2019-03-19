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

#include "CppUTest/TestHarness.h"

#include <string>
#include <vector>
#include <exception>

#include "slightcsv.hpp"

using std::string;
using std::vector;
using std::exception;
using utils::SlightCSV;

TEST_GROUP(slightcsv) {
};

TEST(slightcsv,get_empty_filename) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.getFileName();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,set_empty_filename) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName(t);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,set_get_filename) {
    SlightCSV csv_parser;
    string t = "abc.def";
    csv_parser.setFileName(t);
    CHECK_EQUAL(t, csv_parser.getFileName());
};

TEST(slightcsv,get_empty_separator) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.getSeparator();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,set_empty_separator) {
    SlightCSV csv_parser;
    char c = 0;
    string t = "";
    try {
        csv_parser.setSeparator(c);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,set_get_separator) {
    SlightCSV csv_parser;
    char t = ';';
    csv_parser.setSeparator(t);
    CHECK_EQUAL(t, csv_parser.getSeparator());
};

TEST(slightcsv,load_data_with_no_filename_and_separator) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.loadData();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,load_data_with_no_separator) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("abc.def");
        csv_parser.loadData();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,load_data_with_wrong_filename) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("abc.def");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,load_data_ok) {
    SlightCSV csv_parser;
    size_t t;
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        t = csv_parser.loadData();
    } catch(exception &e) {
    }
    CHECK_EQUAL(8641, t);
};

TEST(slightcsv,get_column_count_nofile_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        t = csv_parser.getColumnCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        t = csv_parser.getColumnCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        t = csv_parser.getColumnCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_ok) {
    SlightCSV csv_parser;
    size_t t;
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        t = csv_parser.getColumnCount();
    } catch(exception &e) {
    }
    CHECK_EQUAL(30, t);
};

TEST(slightcsv,get_row_count_nofile_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        t = csv_parser.getRowCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        t = csv_parser.getRowCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        t = csv_parser.getRowCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_ok) {
    SlightCSV csv_parser;
    size_t t;
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        t = csv_parser.getRowCount();
    } catch(exception &e) {
    }
    CHECK_EQUAL(8641, t);
};

TEST(slightcsv,get_column_nofile_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<string> vect;
    try {
        csv_parser.getColumn(vect, 0);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_nofile_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.getColumn(vect, 0);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.getColumn(vect, 0);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_string_ok) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(exception &e) {
    }
    CHECK_EQUAL(8641, vect.size());
};

TEST(slightcsv,get_column_string_ok_verify_0_0) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(exception &e) {
    }
    CHECK_EQUAL("10", vect.at(1));
};

TEST(slightcsv,get_column_string_ok_verify_0_6000) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(exception &e) {
    }
    CHECK_EQUAL("10", vect.at(6001));
};

TEST(slightcsv,get_column_string_ok_verify_0_8639) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(exception &e) {
    }
    CHECK_EQUAL("10", vect.at(8640));
};

TEST(slightcsv,get_column_string_ok_verify_29_0) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 29);
    } catch(exception &e) {
    }
    CHECK_EQUAL("0", vect.at(1));
};

TEST(slightcsv,get_column_string_ok_verify_29_4000) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 29);
    } catch(exception &e) {
    }
    CHECK_EQUAL("0", vect.at(4001));
};

TEST(slightcsv,get_column_string_ok_verify_29_8639) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 29);
    } catch(exception &e) {
    }
    CHECK_EQUAL("0", vect.at(8640));
};

TEST(slightcsv,get_column_float_ok_verify_1_33) {
    SlightCSV csv_parser;
    string t;
    vector<float> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1);
    } catch(exception &e) {
    }
    CHECK_EQUAL(0.4f, vect.at(34));
};

TEST(slightcsv,get_column_float_ok_verify_28_8632) {
    SlightCSV csv_parser;
    string t;
    vector<float> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(exception &e) {
    }
    CHECK_EQUAL(0.1f, vect.at(8633));
};

TEST(slightcsv,get_column_double_ok_verify_28_8632) {
    SlightCSV csv_parser;
    string t;
    vector<double> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(exception &e) {
    }
    double d = 0.1;
    CHECK_EQUAL(d, vect.at(8633));
};

TEST(slightcsv,get_column_int_ok_verify_28_8632) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(exception &e) {
    }
    CHECK_EQUAL(0, vect.at(8633));
};

TEST(slightcsv,get_column_int_ok_verify_4_11) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 4);
    } catch(exception &e) {
    }
    CHECK_EQUAL(0, vect.at(12));
};

TEST(slightcsv,get_column_int_ok_verify_28_12) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(exception &e) {
    }
    CHECK_EQUAL(1, vect.at(13));
};

TEST(slightcsv,get_column_after_unload) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.getColumn(vect, 28);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_after_unload_load) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(exception &e) {
    }
    CHECK_EQUAL(1, vect.at(13));
};

TEST(slightcsv,unload_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.unloadData();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_filename_after_reset) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.reset();
        csv_parser.getFileName();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,get_separator_after_reset) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.reset();
        csv_parser.getSeparator();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,get_column_after_reset) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.reset();
        csv_parser.getColumn(vect, 1);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv, header_auto_detect_1) {
    SlightCSV csv_parser;
    string t = "";
    size_t header_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        header_cnt = csv_parser.getHeaderCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(1, header_cnt);
};

TEST(slightcsv, header_auto_detect_1_override) {
    SlightCSV csv_parser;
    string t = "";
    size_t header_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        csv_parser.setHeaderCount(0);
        header_cnt = csv_parser.getHeaderCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(0, header_cnt);
};

TEST(slightcsv, header_auto_detect_0) {
    SlightCSV csv_parser;
    string t = "";
    size_t header_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data_0.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        header_cnt = csv_parser.getHeaderCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(0, header_cnt);
};

TEST(slightcsv, header_auto_detect_0_override) {
    SlightCSV csv_parser;
    string t = "";
    size_t header_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data_0.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        csv_parser.setHeaderCount(1);
        header_cnt = csv_parser.getHeaderCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(1, header_cnt);
};

TEST(slightcsv, header_auto_detect_2) {
    SlightCSV csv_parser;
    string t = "";
    size_t header_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data_2.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        header_cnt = csv_parser.getHeaderCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(2, header_cnt);
};

TEST(slightcsv, header_auto_detect_2_override) {
    SlightCSV csv_parser;
    string t = "";
    size_t header_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data_0.csv");
        csv_parser.setSeparator(';');
        csv_parser.loadData();
        csv_parser.setHeaderCount(0);
        header_cnt = csv_parser.getHeaderCount();
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(0, header_cnt);
};

TEST(slightcsv,get_row_ok_verify_0_ok) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 0);
    } catch(exception &e) {
    }
    CHECK_EQUAL("tst", vect.at(0));
    CHECK_EQUAL("tst", vect.at(1));
    CHECK_EQUAL("tst", vect.at(29));
};

TEST(slightcsv,get_row_ok_verify_0_8641_ex) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        cnt = csv_parser.getRowCount();
        csv_parser.getRow(vect, cnt);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", t);
};

TEST(slightcsv,get_row_ok_verify_last_ok) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        cnt = csv_parser.getRowCount();
        csv_parser.getRow(vect, cnt - 1);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL("10", vect.at(0));
    CHECK_EQUAL("0", vect.at(1));
    CHECK_EQUAL("0", vect.at(29));
};

TEST(slightcsv,get_row_ok_verify_4000_ok) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 4000);
    } catch(exception &e) {
    }
    CHECK_EQUAL("14", vect.at(0));
    CHECK_EQUAL("0,3", vect.at(1));
    CHECK_EQUAL("0", vect.at(29));
};