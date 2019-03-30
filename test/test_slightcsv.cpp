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

#include "test_include.hpp"

TEST_GROUP(slightcsv) {
};

TEST(slightcsv,get_empty_filename) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.getFileName();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,set_empty_filename) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName(t);
    } catch(const exception &e) {
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
    U8char u8c;
    try {
        csv_parser.getSeparator(u8c);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,set_empty_separator) {
    SlightCSV csv_parser;
    U8char c;
    string t = "";
    try {
        csv_parser.setSeparator(c);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,set_get_separator) {
    SlightCSV csv_parser;
    U8char t = ";";
    U8char u8c;
    csv_parser.setSeparator(t);
    csv_parser.getSeparator(u8c);
    CHECK_EQUAL(t, u8c);
};

TEST(slightcsv,load_data_with_no_filename_and_separator) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.loadData();
    } catch(const exception &e) {
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
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,load_data_with_wrong_filename) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("abc.def");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,load_data_ok) {
    SlightCSV csv_parser;
    size_t t;
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        t = csv_parser.loadData();
    } catch(const exception &e) {
    }
    CHECK_EQUAL(865, t);
};

TEST(slightcsv,get_column_count_nofile_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        t = csv_parser.getColumnCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        t = csv_parser.getColumnCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        t = csv_parser.getColumnCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_ok) {
    SlightCSV csv_parser;
    size_t t;
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        t = csv_parser.getColumnCount();
    } catch(const exception &e) {
    }
    CHECK_EQUAL(30, t);
};

TEST(slightcsv,get_row_count_nofile_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        t = csv_parser.getRowCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        t = csv_parser.getRowCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        t = csv_parser.getRowCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_ok) {
    SlightCSV csv_parser;
    size_t t;
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        t = csv_parser.getRowCount();
    } catch(const exception &e) {
    }
    CHECK_EQUAL(865, t);
};

TEST(slightcsv,get_column_nofile_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<string> vect;
    try {
        csv_parser.getColumn(vect, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_nofile_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.getColumn(vect, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.getColumn(vect, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_string_ok) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(865, vect.size());
};

TEST(slightcsv,get_column_string_ok_verify_0_0) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("10", vect.at(1));
};

TEST(slightcsv,get_column_string_ok_verify_0_6000) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("10", vect.at(600));
};

TEST(slightcsv,get_column_string_ok_verify_0_8639) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("10", vect.at(864));
};

TEST(slightcsv,get_column_string_ok_verify_29_0) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 29);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("0", vect.at(1));
};

TEST(slightcsv,get_column_string_ok_verify_29_4000) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 29);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("0", vect.at(399));
};

TEST(slightcsv,get_column_string_ok_verify_29_8639) {
    SlightCSV csv_parser;
    string t;
    vector<string> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 29);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("0", vect.at(864));
};

TEST(slightcsv,get_column_float_ok_verify_1_33) {
    SlightCSV csv_parser;
    string t;
    vector<float> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0.4f, vect.at(34));
};

TEST(slightcsv,get_column_float_ok_verify_28_8632) {
    SlightCSV csv_parser;
    string t;
    vector<float> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0.1f, vect.at(857));
};

TEST(slightcsv,get_column_double_ok_verify_28_8632) {
    SlightCSV csv_parser;
    string t;
    vector<double> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    double d = 0.1;
    CHECK_EQUAL(d, vect.at(857));
};

TEST(slightcsv,get_column_int_ok_verify_28_8632) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0, vect.at(857));
};

TEST(slightcsv,get_column_int_ok_verify_4_11) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 4);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0, vect.at(12));
};

TEST(slightcsv,get_column_int_ok_verify_28_12) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(1, vect.at(13));
};

TEST(slightcsv,get_column_after_unload) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.getColumn(vect, 28);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_after_unload_load) {
    SlightCSV csv_parser;
    string t;
    vector<int> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(1, vect.at(13));
};

TEST(slightcsv,get_column_overload_1_ok) {
    SlightCSV csv_parser;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 864);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 865);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0, 1);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0, 5);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 862, 2);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 862, 4);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getColumn(vect, 1, 0, 866);
        cnt = vect.size();
    } catch(const exception &e) {
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
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_filename_after_reset) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.reset();
        csv_parser.getFileName();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,get_separator_after_reset) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    U8char u8c;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.reset();
        csv_parser.getSeparator(u8c);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing separator.", t);
};

TEST(slightcsv,get_column_after_reset) {
    SlightCSV csv_parser;
    string t = "";
    vector<int> vect;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.unloadData();
        csv_parser.loadData();
        csv_parser.reset();
        csv_parser.getColumn(vect, 1);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv, header_auto_detect_1) {
    SlightCSV csv_parser;
    string t = "";
    size_t header_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        header_cnt = csv_parser.getHeaderCount();
    } catch(const exception &e) {
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
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        csv_parser.setHeaderCount(0);
        header_cnt = csv_parser.getHeaderCount();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        header_cnt = csv_parser.getHeaderCount();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        csv_parser.setHeaderCount(1);
        header_cnt = csv_parser.getHeaderCount();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        header_cnt = csv_parser.getHeaderCount();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.loadData();
        csv_parser.setHeaderCount(0);
        header_cnt = csv_parser.getHeaderCount();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 0);
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        cnt = csv_parser.getRowCount();
        csv_parser.getRow(vect, cnt);
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        cnt = csv_parser.getRowCount();
        csv_parser.getRow(vect, cnt - 1);
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 400);
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 400, 1);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 400, 2, 28);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 400, 1, 1);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 864, 29, 1);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 864, 30);
        cnt = vect.size();
    } catch(const exception &e) {
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
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.loadData();
        csv_parser.getRow(vect, 864, 29, 2);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_cell_noload) {
    SlightCSV csv_parser;
    string t = "";
    try {
        csv_parser.getCell(t, 0, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_cell_string_0_0) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(U8char(";"));
    csv_parser.setFileName("../../test/env_data_short.csv");
    csv_parser.loadData();
    string ex = "";
    string t = "";
    try {
        csv_parser.getCell(t, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("tst", t);
};

TEST(slightcsv,get_cell_int_8640_0) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(U8char(";"));
    csv_parser.setFileName("../../test/env_data_short.csv");
    csv_parser.loadData();
    string ex = "";
    int t = 0;
    try {
        csv_parser.getCell(t, 864, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(10, t);
};

TEST(slightcsv,get_cell_int_8640_29) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(U8char(";"));
    csv_parser.setFileName("../../test/env_data_short.csv");
    csv_parser.loadData();
    string ex = "";
    int t = 0;
    try {
        csv_parser.getCell(t, 864, 29);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(0, t);
};

TEST(slightcsv,get_cell_float_8628_28) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(U8char(";"));
    csv_parser.setFileName("../../test/env_data_short.csv");
    csv_parser.loadData();
    string ex = "";
    float t = 0;
    try {
        csv_parser.getCell(t, 852, 28);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(0.95f, t);
};

TEST(slightcsv,get_cell_double_8628_28) {
    SlightCSV csv_parser;
    csv_parser.setSeparator(U8char(";"));
    csv_parser.setFileName("../../test/env_data_short.csv");
    csv_parser.loadData();
    string ex = "";
    double t = 0;
    try {
        csv_parser.getCell(t, 852, 28);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    double d = 0.95;
    CHECK_EQUAL(d, t);
};

TEST(slightcsv, get_empty_escape_ex) {
    SlightCSV csv_parser;
    string ex = "";
    U8char u8c;
    try {
        csv_parser.getEscape(u8c);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Escape character not set.", ex);
};

TEST(slightcsv, set_empty_escape_ex) {
    SlightCSV csv_parser;
    string ex = "";
    U8char u8c;
    try {
        csv_parser.setEscape(u8c);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Escape character not set.", ex);
};

TEST(slightcsv, set_get_escape_ok) {
    SlightCSV csv_parser;
    string ex = "";
    U8char esc = "\"";
    U8char c;
    try {
        csv_parser.setEscape(esc);
        csv_parser.getEscape(c);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
};

TEST(slightcsv, set_escape_process_ok_1) {
    SlightCSV csv_parser;
    string ex = "";
    U8char esc = "\"";
    U8char c;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setEscape(esc);
        csv_parser.getEscape(c);
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 0, 0);
    } catch(const exception &e) {
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
    U8char esc = "\"";
    U8char c;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setEscape(esc);
        csv_parser.getEscape(c);
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 1, 0);
    } catch(const exception &e) {
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
    U8char esc = "\"";
    U8char c;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setEscape(esc);
        csv_parser.getEscape(c);
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 2, 0);
    } catch(const exception &e) {
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
    U8char esc = "\"";
    U8char c;
    string cell;
    size_t count = 0;
    try {
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setEscape(esc);
        csv_parser.getEscape(c);
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.loadData();
        count = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 3, 29);
    } catch(const exception &e) {
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
    set<U8char> ss;
    try {
        csv_parser.getStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character set empty.", ex);
};

TEST(slightcsv, set_empty_strip_chars_ex) {
    SlightCSV csv_parser;
    string ex = "";
    set<U8char> ss;
    try {
        csv_parser.setStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character set empty.", ex);
};

TEST(slightcsv, get_set_strip_chars_ok_1) {
    SlightCSV csv_parser;
    string ex = "";
    set<U8char> ss;
    U8char c = "t";
    ss.insert(c);
    try {
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
};

TEST(slightcsv, get_set_strip_chars_ok_2) {
    SlightCSV csv_parser;
    string ex = "";
    set<U8char> ss;
    U8char c = "t";
    U8char d = "z";
    U8char e = "x";
    ss.insert(c);
    ss.insert(d);
    try {
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
    } catch(const exception &e) {
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
    set<U8char> ss;
    U8char c = "t";
    U8char d = "z";
    ss.insert(c);
    ss.insert(d);
    try {
        csv_parser.setStripChars(ss);
        csv_parser.reset();
        csv_parser.getStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character set empty.", ex);
};

TEST(slightcsv, get_set_strip_process_ok_1) {
    SlightCSV csv_parser;
    string ex = "";
    set<U8char> ss;
    U8char c = "t";
    ss.insert(c);
    string cell = "";
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        csv_parser.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL("s", cell);
};

TEST(slightcsv, get_set_strip_process_ok_2) {
    SlightCSV csv_parser;
    string ex = "";
    set<U8char> ss;
    U8char c = ",";
    U8char d = "0";
    ss.insert(c);
    ss.insert(d);
    string cell = "";
    try {
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setEscape(U8char("\""));
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        csv_parser.getCell(cell, 0, 0);
    } catch(const exception &e) {
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
    set<U8char> ss;
    U8char c = "\"";
    ss.insert(c);
    string cell = "";
    try {
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setEscape(U8char("\""));
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        csv_parser.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("CSV format error (cell count mismatch in row).", ex);
};

TEST(slightcsv, get_set_strip_process_ok_4) {
    SlightCSV csv_parser;
    string ex = "";
    set<U8char> ss;
    U8char c = "\r";
    U8char d = "\n";
    ss.insert(c);
    ss.insert(d);
    string cell = "";
    size_t row_cnt = 0;
    size_t col_cnt = 0;
    try {
        csv_parser.setFileName("../../test/env_data_sli.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setEscape(U8char("\""));
        csv_parser.setStripChars(ss);
        csv_parser.getStripChars(ss);
        csv_parser.loadData();
        row_cnt = csv_parser.getRowCount();
        col_cnt = csv_parser.getColumnCount();
        csv_parser.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL(1, ss.count(d));
    CHECK_EQUAL(1, row_cnt);
    CHECK_EQUAL(117, col_cnt);
    CHECK_EQUAL("\"14;0,1\"", cell);
};

TEST(slightcsv, get_empty_rep_chars_ex) {
    SlightCSV csv_parser;
    string ex = "";
    map<U8char, U8char> rmap;
    try {
        csv_parser.getReplaceChars(rmap);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Replace character map empty.", ex);
};

TEST(slightcsv, set_empty_rep_chars_ex) {
    SlightCSV csv_parser;
    string ex = "";
    map<U8char, U8char> rmap;
    try {
        csv_parser.setReplaceChars(rmap);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Replace character map empty.", ex);
};

TEST(slightcsv, get_set_rep_chars_ok_1) {
    SlightCSV csv_parser;
    string ex = "";
    map<U8char, U8char> setmap;
    U8char from = "t";
    U8char to = "d";
    U8char c;
    pair<U8char, U8char> p(from, to);
    setmap.insert(p);
    map<U8char, U8char> getmap;
    size_t cnt = 0;
    try {
        csv_parser.setReplaceChars(setmap);
        csv_parser.getReplaceChars(getmap);
        cnt = getmap.size();
        c = getmap.find(from)->second;
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL(to, c);
};

TEST(slightcsv, get_set_rep_chars_ok_2) {
    SlightCSV csv_parser;
    string ex = "";
    map<U8char, U8char> setmap;
    U8char from1 = "t";
    U8char to1 = "d";
    setmap.insert(pair<U8char, U8char>(from1, to1));
    U8char from2 = "s";
    U8char to2 = "r";
    setmap.insert(pair<U8char, U8char>(from2, to2));
    U8char c;
    U8char d;
    map<U8char, U8char> getmap;
    size_t cnt = 0;
    try {
        csv_parser.setReplaceChars(setmap);
        csv_parser.getReplaceChars(getmap);
        cnt = getmap.size();
        c = getmap.find(from1)->second;
        d = getmap.find(from2)->second;
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(2, cnt);
    CHECK_EQUAL(to1, c);
    CHECK_EQUAL(to2, d);
};

TEST(slightcsv, get_set_rep_chars_ok_3) {
    SlightCSV csv_parser;
    string ex = "";
    map<U8char, U8char> setmap;
    U8char from1 = "t";
    U8char to1 = "d";
    setmap.insert(pair<U8char, U8char>(from1, to1));
    U8char from2 = "s";
    U8char to2 = "r";
    setmap.insert(pair<U8char, U8char>(from2, to2));
    map<U8char, U8char> getmap;
    size_t cnt = 0;
    U8char c;
    U8char d;
    string cell = "";
    try {
        csv_parser.setFileName("../../test/env_data_short.csv");
        csv_parser.setSeparator(U8char(";"));
        csv_parser.setReplaceChars(setmap);
        csv_parser.getReplaceChars(getmap);
        csv_parser.loadData();
        cnt = getmap.size();
        c = getmap.find(from1)->second;
        d = getmap.find(from2)->second;
        csv_parser.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(2, cnt);
    CHECK_EQUAL(to1, c);
    CHECK_EQUAL(to2, d);
    CHECK_EQUAL("drd", cell);
};

TEST(slightcsv, complex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_sli.csv";
    U8char sep = ";";
    U8char esc = "\"";
    set<U8char> stripset;
    U8char strip = "l";
    stripset.insert(strip);
    map<U8char, U8char> setmap;
    U8char from1 = "d";
    U8char to1 = "x";
    setmap.insert(pair<U8char, U8char>(from1, to1));
    vector<string> row1;
    vector<string> row2;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.setEscape(esc);
        csv_parser.setStripChars(stripset);
        csv_parser.setReplaceChars(setmap);
        csv_parser.loadData();
        csv_parser.getRow(row1, 0);
        csv_parser.getRow(row2, 3);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("\"14;0,1\"", row1.at(0));
    CHECK_EQUAL("\"0\r\nxx\"", row2.at(29));
};

TEST(slightcsv, format_header_err) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short_dh.csv";
    U8char sep = ";";
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("CSV format error (intermediate header).", ex);
};

TEST(slightcsv, set_header_count_no_data_loaded_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.setHeaderCount(0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_cell_bad_row_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    string cell = "";
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getCell(cell, 865, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_cell_bad_column_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    string cell = "";
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getCell(cell, 0, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_2p_bad_column_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> column;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getColumn(column, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_3p_data_not_loaded_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> column;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        // data not loaded
        csv_parser.getColumn(column, 29, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_column_3p_bad_column_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> column;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getColumn(column, 30, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_4p_data_not_loaded_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> column;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        // data not loaded
        csv_parser.getColumn(column, 29, 0, 10);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_column_4p_bad_column_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> column;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getColumn(column, 30, 0, 1);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_4p_bad_start_cell_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> column;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getColumn(column, 29, 865, 1);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_row_2p_data_not_loaded_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> row;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        // data not loaded
        csv_parser.getRow(row, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_row_3p_data_not_loaded_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> row;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        // data not loaded
        csv_parser.getRow(row, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_row_4p_data_not_loaded_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> row;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        // data not loaded
        csv_parser.getRow(row, 0, 0, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_row_3p_bad_row_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> row;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getRow(row, 865, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_row_4p_bad_row_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> row;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getRow(row, 865, 0, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_row_4p_bad_start_cell_index_ex) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    U8char sep = ";";
    vector<string> row;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.loadData();
        csv_parser.getRow(row, 864, 30, 1);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, complex_2) {
    SlightCSV csv_parser;
    string ex = "";
    string file = "../../test/utf8_test.csv";
    U8char sep = ";";
    U8char esc = "\"";
    U8char strip = "Z";
    set<U8char> stripset;
    stripset.insert(strip);
    U8char from = "¥";
    U8char to = "$";
    map<U8char, U8char> repmap;
    repmap.insert(pair<U8char, U8char>(from, to));
    string cell1;
    string cell2;
    try {
        csv_parser.setFileName(file);
        csv_parser.setSeparator(sep);
        csv_parser.setEscape(esc);
        csv_parser.setStripChars(stripset);
        csv_parser.setReplaceChars(repmap);
        csv_parser.loadData();
        csv_parser.getCell(cell1, 2, 2);
        csv_parser.getCell(cell2, 2, 5);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("\"jack@smith.jp;jack1.smith@jp\"", cell1);
    CHECK_EQUAL("$", cell2);
};