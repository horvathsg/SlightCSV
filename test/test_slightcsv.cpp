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

TEST(slightcsv,get_column_overload_1_ok) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(cnt, 8641);
    CHECK_EQUAL("tst", vect.at(0));
    CHECK_EQUAL("0.1", vect.at(8633));
    CHECK_EQUAL("0", vect.at(8640));
};

TEST(slightcsv,get_column_overload_2_ok) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 8640);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("0", vect.at(0));
};

TEST(slightcsv,get_column_overload_3_ex) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 8641);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_column_overload_4_ok) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0, 1);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("tst", vect.at(0));
};

TEST(slightcsv,get_column_overload_5_ok) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0, 5);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(5, cnt);
    CHECK_EQUAL("tst", vect.at(0));
};

TEST(slightcsv,get_column_overload_6_ok) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 8638, 2);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(2, cnt);
    CHECK_EQUAL("0", vect.at(0));
    CHECK_EQUAL("0", vect.at(1));
};

TEST(slightcsv,get_column_overload_7_ex) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 8638, 4);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_column_overload_8_ex) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0, 8642);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
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
    CHECK_EQUAL("0.3", vect.at(1));
    CHECK_EQUAL("0", vect.at(29));
};

TEST(slightcsv,get_row_overload_1_ok) {
    SlightCSV csv_parser;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 4000, 1);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(29, cnt);
    CHECK_EQUAL("0.3", vect.at(0));
    CHECK_EQUAL("0", vect.at(28));
};

TEST(slightcsv,get_row_overload_2_ok) {
    SlightCSV csv_parser;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 4000, 2, 28);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(28, cnt);
    CHECK_EQUAL("0", vect.at(0));
    CHECK_EQUAL("0", vect.at(27));
};

TEST(slightcsv,get_row_overload_3_ok) {
    SlightCSV csv_parser;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 4000, 1, 1);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("0.3", vect.at(0));
};

TEST(slightcsv,get_row_overload_4_ok) {
    SlightCSV csv_parser;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 8640, 29, 1);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("0", vect.at(0));
};

TEST(slightcsv,get_row_overload_5_ex) {
    SlightCSV csv_parser;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 8640, 30);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_row_overload_6_ex) {
    SlightCSV csv_parser;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 8640, 29, 2);
        cnt = vect.size();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_cell_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.getCell(t, 0, 0);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_cell_string_0_0) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(';');
    csv_parser.setFileName("../../test/env_data.csv");
    csv_parser.loadData();
    string ex = "";
    string t = "";
    try {
        csv_parser.getCell(t, 0, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("tst", t);
};

TEST(slightcsv,get_cell_int_8640_0) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(';');
    csv_parser.setFileName("../../test/env_data.csv");
    csv_parser.loadData();
    string ex = "";
    int t = 0;
    try {
        csv_parser.getCell(t, 8640, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(10, t);
};

TEST(slightcsv,get_cell_int_8640_29) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(';');
    csv_parser.setFileName("../../test/env_data.csv");
    csv_parser.loadData();
    string ex = "";
    int t = 0;
    try {
        csv_parser.getCell(t, 8640, 29);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(0, t);
};

TEST(slightcsv,get_cell_float_8628_28) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(';');
    csv_parser.setFileName("../../test/env_data.csv");
    csv_parser.loadData();
    string ex = "";
    float t = 0;
    try {
        csv_parser.getCell(t, 8628, 28);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(0.95f, t);
};

TEST(slightcsv,get_cell_double_8628_28) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(';');
    csv_parser.setFileName("../../test/env_data.csv");
    csv_parser.loadData();
    string ex = "";
    double t = 0;
    try {
        csv_parser.getCell(t, 8628, 28);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    double d = 0.95;
    CHECK_EQUAL(d, t);
};

TEST(slightcsv, get_empty_escape_ex) {
    SlightCSV csv_parser;
    string ex = "";
    try {
        csv_parser.getEscape();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Escape character not set.", ex);
};

TEST(slightcsv, set_empty_escape_ex) {
    SlightCSV csv_parser;
    string ex = "";
    try {
        csv_parser.setEscape(0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Escape character not set.", ex);
};

TEST(slightcsv, set_get_escape_ok) {
    SlightCSV csv_parser;
    string ex = "";
    char esc = '\"';
    char c = 0;
    try {
        csv_parser.setEscape(esc);
        c = csv_parser.getEscape();
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
};

TEST(slightcsv, set_escape_process_ok_1) {
    SlightCSV csv_parser;
    string ex = "";
    char esc = '\"';
    char c = 0;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setEscape(esc);
        c = csv_parser.getEscape();
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 0, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"14;0,1\"", cell);
};

TEST(slightcsv, set_escape_process_ok_2) {
    SlightCSV csv_parser;
    string ex = "";
    char esc = '\"';
    char c = 0;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setEscape(esc);
        c = csv_parser.getEscape();
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 1, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"14;\"0,1", cell);
};

TEST(slightcsv, set_escape_process_ok_3) {
    SlightCSV csv_parser;
    string ex = "";
    char esc = '\"';
    char c = 0;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setEscape(esc);
        c = csv_parser.getEscape();
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 2, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"14\"", cell);
};
TEST(slightcsv, set_escape_process_ok_4) {
    SlightCSV csv_parser;
    string ex = "";
    char esc = '\"';
    char c = 0;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(';');
        csv_parser.setEscape(esc);
        c = csv_parser.getEscape();
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 3, 29);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"0\r\ndxl\"", cell);
};

TEST(slightcsv, get_empty_strip_chars_ex) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    try {
        csv_parser.getStripChars(ss);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character set empty.", ex);
};

TEST(slightcsv, set_empty_strip_chars_ex) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    try {
        csv_parser.setStripChars(ss);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character set empty.", ex);
};

TEST(slightcsv, get_set_strip_chars_ok_1) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    char c = 't';
    ss.insert(c);
    try {
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
};

TEST(slightcsv, get_set_strip_chars_ok_2) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    char c = 't';
    char d = 'z';
    char e = 'x';
    ss.insert(c);
    ss.insert(d);
    try {
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL(1, ss.count(d));
    CHECK_EQUAL(0, ss.count(e));
};

TEST(slightcsv, get_set_strip_chars_reset_ex) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    char c = 't';
    char d = 'z';
    ss.insert(c);
    ss.insert(d);
    try {
        csv_parser.setStripChars(ss);
        csv_parser.reset();
        csv_parser.getStripChars(ss);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character set empty.", ex);
};

TEST(slightcsv, get_set_strip_process_ok_1) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    char c = 't';
    ss.insert(c);
    string cell = "";
    try {
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.setSeparator(';');
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        csv_parser.getCell(cell, 0, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL("s", cell);
};

TEST(slightcsv, get_set_strip_process_ok_2) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    char c = ',';
    char d = '0';
    ss.insert(c);
    ss.insert(d);
    string cell = "";
    try {
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.setSeparator(';');
        csv_parser.setEscape('\"');
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        csv_parser.getCell(cell, 0, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL(1, ss.count(d));
    CHECK_EQUAL("\"14;1\"", cell);
};

TEST(slightcsv, get_set_strip_process_ex_3) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    char c = '\"';
    ss.insert(c);
    string cell = "";
    try {
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.setSeparator(';');
        csv_parser.setEscape('\"');
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        csv_parser.getCell(cell, 0, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("CSV format error (cell count mismatch in row).", ex);
};

TEST(slightcsv, get_set_strip_process_ok_4) {
    SlightCSV csv_parser;
    string ex = "";
    set<char> ss;
    char c = '\r';
    char d = '\n';
    ss.insert(c);
    ss.insert(d);
    string cell = "";
    size_t row_cnt = 0;
    size_t col_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.setSeparator(';');
        csv_parser.setEscape('\"');
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        row_cnt = csv_parser.getRowCount();
        col_cnt = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 0, 0);
    } catch(exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL(1, ss.count(d));
    CHECK_EQUAL(1, row_cnt);
    CHECK_EQUAL(117, col_cnt);
    CHECK_EQUAL("\"14;0,1\"", cell);
};