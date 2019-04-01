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
    SlightCSV scsv;
    string t = "";
    try {
        scsv.getFileName();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,set_empty_filename) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.setFileName(t);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,set_get_filename) {
    SlightCSV scsv;
    string t = "abc.def";
    scsv.setFileName(t);
    CHECK_EQUAL(t, scsv.getFileName());
};

TEST(slightcsv,get_empty_separator) {
    SlightCSV scsv;
    string t = "";
    string sep;
    try {
        scsv.getSeparator(sep);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Separator character invalid or missing.", t);
};

TEST(slightcsv,set_empty_separator) {
    SlightCSV scsv;
    string c;
    string t = "";
    try {
        scsv.setSeparator(c);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Separator character invalid or missing.", t);
};

TEST(slightcsv,set_get_separator) {
    SlightCSV scsv;
    string sepset = ";";
    string sepget;
    scsv.setSeparator(sepset);
    scsv.getSeparator(sepget);
    CHECK_EQUAL(sepset, sepget);
};

TEST(slightcsv,load_data_with_no_filename_and_separator) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.loadData();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,load_data_with_no_separator) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.setFileName("abc.def");
        scsv.loadData();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Separator character invalid or missing.", t);
};

TEST(slightcsv,load_data_with_wrong_filename) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.setFileName("abc.def");
        scsv.setSeparator(";");
        scsv.loadData();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,load_data_ok) {
    SlightCSV scsv;
    size_t t;
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        t = scsv.loadData();
    } catch(const exception &e) {
    }
    CHECK_EQUAL(865, t);
};

TEST(slightcsv,get_column_count_nofile_nosep_noload) {
    SlightCSV scsv;
    string t = "";
    try {
        t = scsv.getColumnCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_nosep_noload) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        t = scsv.getColumnCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_noload) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        t = scsv.getColumnCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_count_ok) {
    SlightCSV scsv;
    size_t t;
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        t = scsv.getColumnCount();
    } catch(const exception &e) {
    }
    CHECK_EQUAL(30, t);
};

TEST(slightcsv,get_row_count_nofile_nosep_noload) {
    SlightCSV scsv;
    string t = "";
    try {
        t = scsv.getRowCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_nosep_noload) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        t = scsv.getRowCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_noload) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        t = scsv.getRowCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_row_count_ok) {
    SlightCSV scsv;
    size_t t;
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        t = scsv.getRowCount();
    } catch(const exception &e) {
    }
    CHECK_EQUAL(865, t);
};

TEST(slightcsv,get_column_nofile_nosep_noload) {
    SlightCSV scsv;
    string t = "";
    vector<string> vect;
    try {
        scsv.getColumn(vect, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_nofile_noload) {
    SlightCSV scsv;
    string t = "";
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.getColumn(vect, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_noload) {
    SlightCSV scsv;
    string t = "";
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.getColumn(vect, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_string_ok) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(865, vect.size());
};

TEST(slightcsv,get_column_string_ok_verify_0_0) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("10", vect.at(1));
};

TEST(slightcsv,get_column_string_ok_verify_0_6000) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("10", vect.at(600));
};

TEST(slightcsv,get_column_string_ok_verify_0_8639) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("10", vect.at(864));
};

TEST(slightcsv,get_column_string_ok_verify_29_0) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 29);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("0", vect.at(1));
};

TEST(slightcsv,get_column_string_ok_verify_29_4000) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 29);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("0", vect.at(399));
};

TEST(slightcsv,get_column_string_ok_verify_29_8639) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 29);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("0", vect.at(864));
};

TEST(slightcsv,get_column_float_ok_verify_1_33) {
    SlightCSV scsv;
    string t;
    vector<float> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0.4f, vect.at(34));
};

TEST(slightcsv,get_column_float_ok_verify_28_8632) {
    SlightCSV scsv;
    string t;
    vector<float> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0.1f, vect.at(857));
};

TEST(slightcsv,get_column_double_ok_verify_28_8632) {
    SlightCSV scsv;
    string t;
    vector<double> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    double d = 0.1;
    CHECK_EQUAL(d, vect.at(857));
};

TEST(slightcsv,get_column_int_ok_verify_28_8632) {
    SlightCSV scsv;
    string t;
    vector<int> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0, vect.at(857));
};

TEST(slightcsv,get_column_int_ok_verify_4_11) {
    SlightCSV scsv;
    string t;
    vector<int> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 4);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(0, vect.at(12));
};

TEST(slightcsv,get_column_int_ok_verify_28_12) {
    SlightCSV scsv;
    string t;
    vector<int> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(1, vect.at(13));
};

TEST(slightcsv,get_column_after_unload) {
    SlightCSV scsv;
    string t = "";
    vector<int> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.unloadData();
        scsv.getColumn(vect, 28);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_column_after_unload_load) {
    SlightCSV scsv;
    string t;
    vector<int> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.unloadData();
        scsv.loadData();
        scsv.getColumn(vect, 28);
    } catch(const exception &e) {
    }
    CHECK_EQUAL(1, vect.at(13));
};

TEST(slightcsv,get_column_overload_1_ok) {
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 0);
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
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 864);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("0", vect.at(0));
};

TEST(slightcsv,get_column_overload_3_ex) {
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 865);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_column_overload_4_ok) {
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 0, 1);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("tst", vect.at(0));
};

TEST(slightcsv,get_column_overload_5_ok) {
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 0, 5);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(5, cnt);
    CHECK_EQUAL("tst", vect.at(0));
};

TEST(slightcsv,get_column_overload_6_ok) {
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 862, 2);
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
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 862, 4);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_column_overload_8_ex) {
    SlightCSV scsv;
    string ex;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getColumn(vect, 1, 0, 866);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,unload_noload) {
    SlightCSV scsv;
    string t = "";
    vector<int> vect;
    try {
        scsv.unloadData();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_filename_after_reset) {
    SlightCSV scsv;
    string t = "";
    vector<int> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.unloadData();
        scsv.loadData();
        scsv.reset();
        scsv.getFileName();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Wrong or missing filename.", t);
};

TEST(slightcsv,get_separator_after_reset) {
    SlightCSV scsv;
    string t = "";
    vector<int> vect;
    string str;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.unloadData();
        scsv.loadData();
        scsv.reset();
        scsv.getSeparator(str);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Separator character invalid or missing.", t);
};

TEST(slightcsv,get_column_after_reset) {
    SlightCSV scsv;
    string t = "";
    vector<int> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.unloadData();
        scsv.loadData();
        scsv.reset();
        scsv.getColumn(vect, 1);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv, header_auto_detect_1) {
    SlightCSV scsv;
    string t = "";
    size_t header_cnt = 0;
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        header_cnt = scsv.getHeaderCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(1, header_cnt);
};

TEST(slightcsv, header_auto_detect_1_override) {
    SlightCSV scsv;
    string t = "";
    size_t header_cnt = 0;
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        scsv.setHeaderCount(0);
        header_cnt = scsv.getHeaderCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(0, header_cnt);
};

TEST(slightcsv, header_auto_detect_0) {
    SlightCSV scsv;
    string t = "";
    size_t header_cnt = 0;
    try {
        scsv.setFileName("../../test/env_data_0.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        header_cnt = scsv.getHeaderCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(0, header_cnt);
};

TEST(slightcsv, header_auto_detect_0_override) {
    SlightCSV scsv;
    string t = "";
    size_t header_cnt = 0;
    try {
        scsv.setFileName("../../test/env_data_0.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        scsv.setHeaderCount(1);
        header_cnt = scsv.getHeaderCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(1, header_cnt);
};

TEST(slightcsv, header_auto_detect_2) {
    SlightCSV scsv;
    string t = "";
    size_t header_cnt = 0;
    try {
        scsv.setFileName("../../test/env_data_2.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        header_cnt = scsv.getHeaderCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(2, header_cnt);
};

TEST(slightcsv, header_auto_detect_2_override) {
    SlightCSV scsv;
    string t = "";
    size_t header_cnt = 0;
    try {
        scsv.setFileName("../../test/env_data_0.csv");
        scsv.setSeparator(";");
        scsv.loadData();
        scsv.setHeaderCount(0);
        header_cnt = scsv.getHeaderCount();
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL(0, header_cnt);
};

TEST(slightcsv,get_row_ok_verify_0_ok) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 0);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("tst", vect.at(0));
    CHECK_EQUAL("tst", vect.at(1));
    CHECK_EQUAL("tst", vect.at(29));
};

TEST(slightcsv,get_row_ok_verify_0_8641_ex) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        cnt = scsv.getRowCount();
        scsv.getRow(vect, cnt);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", t);
};

TEST(slightcsv,get_row_ok_verify_last_ok) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        cnt = scsv.getRowCount();
        scsv.getRow(vect, cnt - 1);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("", t);
    CHECK_EQUAL("10", vect.at(0));
    CHECK_EQUAL("0", vect.at(1));
    CHECK_EQUAL("0", vect.at(29));
};

TEST(slightcsv,get_row_ok_verify_4000_ok) {
    SlightCSV scsv;
    string t;
    vector<string> vect;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 400);
    } catch(const exception &e) {
    }
    CHECK_EQUAL("14", vect.at(0));
    CHECK_EQUAL("0.3", vect.at(1));
    CHECK_EQUAL("0", vect.at(29));
};

TEST(slightcsv,get_row_overload_1_ok) {
    SlightCSV scsv;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 400, 1);
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
    SlightCSV scsv;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 400, 2, 28);
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
    SlightCSV scsv;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 400, 1, 1);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("0.3", vect.at(0));
};

TEST(slightcsv,get_row_overload_4_ok) {
    SlightCSV scsv;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 864, 29, 1);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("0", vect.at(0));
};

TEST(slightcsv,get_row_overload_5_ex) {
    SlightCSV scsv;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 864, 30);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_row_overload_6_ex) {
    SlightCSV scsv;
    string ex = "";
    vector<string> vect;
    size_t cnt = 0;
    try {
        scsv.setSeparator(";");
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.loadData();
        scsv.getRow(vect, 864, 29, 2);
        cnt = vect.size();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv,get_cell_noload) {
    SlightCSV scsv;
    string t = "";
    try {
        scsv.getCell(t, 0, 0);
    } catch(const exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

TEST(slightcsv,get_cell_string_0_0) {
    SlightCSV scsv;
    scsv.setSeparator(";");
    scsv.setFileName("../../test/env_data_short.csv");
    scsv.loadData();
    string ex = "";
    string t = "";
    try {
        scsv.getCell(t, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("tst", t);
};

TEST(slightcsv,get_cell_int_8640_0) {
    SlightCSV scsv;
    scsv.setSeparator(";");
    scsv.setFileName("../../test/env_data_short.csv");
    scsv.loadData();
    string ex = "";
    int t = 0;
    try {
        scsv.getCell(t, 864, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(10, t);
};

TEST(slightcsv,get_cell_int_8640_29) {
    SlightCSV scsv;
    scsv.setSeparator(";");
    scsv.setFileName("../../test/env_data_short.csv");
    scsv.loadData();
    string ex = "";
    int t = 0;
    try {
        scsv.getCell(t, 864, 29);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(0, t);
};

TEST(slightcsv,get_cell_float_8628_28) {
    SlightCSV scsv;
    scsv.setSeparator(";");
    scsv.setFileName("../../test/env_data_short.csv");
    scsv.loadData();
    string ex = "";
    float t = 0;
    try {
        scsv.getCell(t, 852, 28);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(0.95f, t);
};

TEST(slightcsv,get_cell_double_8628_28) {
    SlightCSV scsv;
    scsv.setSeparator(";");
    scsv.setFileName("../../test/env_data_short.csv");
    scsv.loadData();
    string ex = "";
    double t = 0;
    try {
        scsv.getCell(t, 852, 28);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    double d = 0.95;
    CHECK_EQUAL(d, t);
};

TEST(slightcsv, get_empty_escape_ex) {
    SlightCSV scsv;
    string ex = "";
    string str;
    try {
        scsv.getEscape(str);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Escape character invalid or missing.", ex);
};

TEST(slightcsv, set_empty_escape_ex) {
    SlightCSV scsv;
    string ex = "";
    string str;
    try {
        scsv.setEscape(str);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Escape character invalid or missing.", ex);
};

TEST(slightcsv, set_get_escape_ok) {
    SlightCSV scsv;
    string ex = "";
    string esc = "\"";
    string c;
    try {
        scsv.setEscape(esc);
        scsv.getEscape(c);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
};

TEST(slightcsv, set_escape_process_ok_1) {
    SlightCSV scsv;
    string ex = "";
    string esc = "\"";
    string c;
    string cell;
    size_t count = 0;
    try {
        scsv.setSeparator(";");
        scsv.setEscape(esc);
        scsv.getEscape(c);
        scsv.setFileName("../../test/env_data_sli.csv");
        scsv.loadData();
        count = scsv.getColumnCount();
        scsv.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"14;0,1\"", cell);
};

TEST(slightcsv, set_escape_process_ok_2) {
    SlightCSV scsv;
    string ex = "";
    string esc = "\"";
    string c;
    string cell;
    size_t count = 0;
    try {
        scsv.setSeparator(";");
        scsv.setEscape(esc);
        scsv.getEscape(c);
        scsv.setFileName("../../test/env_data_sli.csv");
        scsv.loadData();
        count = scsv.getColumnCount();
        scsv.getCell(cell, 1, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"14;\"0,1", cell);
};

TEST(slightcsv, set_escape_process_ok_3) {
    SlightCSV scsv;
    string ex = "";
    string esc = "\"";
    string c;
    string cell;
    size_t count = 0;
    try {
        scsv.setSeparator(";");
        scsv.setEscape(esc);
        scsv.getEscape(c);
        scsv.setFileName("../../test/env_data_sli.csv");
        scsv.loadData();
        count = scsv.getColumnCount();
        scsv.getCell(cell, 2, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"14\"", cell);
};

TEST(slightcsv, set_escape_process_ok_4) {
    SlightCSV scsv;
    string ex = "";
    string esc = "\"";
    string c;
    string cell;
    size_t count = 0;
    try {
        scsv.setSeparator(";");
        scsv.setEscape(esc);
        scsv.getEscape(c);
        scsv.setFileName("../../test/env_data_sli.csv");
        scsv.loadData();
        count = scsv.getColumnCount();
        scsv.getCell(cell, 3, 29);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(esc, c);
    CHECK_EQUAL(30, count);
    CHECK_EQUAL("\"0\r\ndxl\"", cell);
};

TEST(slightcsv, get_empty_strip_chars_ex) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    try {
        scsv.getStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character invalid or missing.", ex);
};

TEST(slightcsv, set_empty_strip_chars_ex) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    try {
        scsv.setStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character invalid or missing.", ex);
};

TEST(slightcsv, get_set_strip_chars_ok_1) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    string c = "t";
    ss.insert(c);
    try {
        scsv.setStripChars(ss);
        scsv.getStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
};

TEST(slightcsv, get_set_strip_chars_ok_2) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    string c = "t";
    string d = "z";
    string e = "x";
    ss.insert(c);
    ss.insert(d);
    try {
        scsv.setStripChars(ss);
        scsv.getStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL(1, ss.count(d));
    CHECK_EQUAL(0, ss.count(e));
};

TEST(slightcsv, get_set_strip_chars_reset_ex) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    string c = "t";
    string d = "z";
    ss.insert(c);
    ss.insert(d);
    try {
        scsv.setStripChars(ss);
        scsv.reset();
        scsv.getStripChars(ss);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character invalid or missing.", ex);
};

TEST(slightcsv, get_set_strip_process_ok_1) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    string c = "t";
    ss.insert(c);
    string cell = "";
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        scsv.setStripChars(ss);
        scsv.getStripChars(ss);
        scsv.loadData();
        scsv.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL("s", cell);
};

TEST(slightcsv, get_set_strip_process_ok_2) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    string c = ",";
    string d = "0";
    ss.insert(c);
    ss.insert(d);
    string cell = "";
    try {
        scsv.setFileName("../../test/env_data_sli.csv");
        scsv.setSeparator(";");
        scsv.setEscape("\"");
        scsv.setStripChars(ss);
        scsv.getStripChars(ss);
        scsv.loadData();
        scsv.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(1, ss.count(c));
    CHECK_EQUAL(1, ss.count(d));
    CHECK_EQUAL("\"14;1\"", cell);
};

TEST(slightcsv, get_set_strip_process_ex_3) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    string c = "\"";
    ss.insert(c);
    string cell = "";
    try {
        scsv.setFileName("../../test/env_data_sli.csv");
        scsv.setSeparator(";");
        scsv.setEscape("\"");
        scsv.setStripChars(ss);
        scsv.getStripChars(ss);
        scsv.loadData();
        scsv.getCell(cell, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("CSV format error (cell count mismatch in row).", ex);
};

TEST(slightcsv, get_set_strip_process_ok_4) {
    SlightCSV scsv;
    string ex = "";
    set<string> ss;
    string c = "\r";
    string d = "\n";
    ss.insert(c);
    ss.insert(d);
    string cell = "";
    size_t row_cnt = 0;
    size_t col_cnt = 0;
    try {
        scsv.setFileName("../../test/env_data_sli.csv");
        scsv.setSeparator(";");
        scsv.setEscape("\"");
        scsv.setStripChars(ss);
        scsv.getStripChars(ss);
        scsv.loadData();
        row_cnt = scsv.getRowCount();
        col_cnt = scsv.getColumnCount();
        scsv.getCell(cell, 0, 0);
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
    SlightCSV scsv;
    string ex = "";
    map<string, string> rmap;
    try {
        scsv.getReplaceChars(rmap);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Replace character invalid or missing.", ex);
};

TEST(slightcsv, set_empty_rep_chars_ex) {
    SlightCSV scsv;
    string ex = "";
    map<string, string> rmap;
    try {
        scsv.setReplaceChars(rmap);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Replace character invalid or missing.", ex);
};

TEST(slightcsv, get_set_rep_chars_ok_1) {
    SlightCSV scsv;
    string ex = "";
    map<string, string> setmap;
    string from = "t";
    string to = "d";
    string c;
    pair<string, string> p(from, to);
    setmap.insert(p);
    map<string, string> getmap;
    size_t cnt = 0;
    try {
        scsv.setReplaceChars(setmap);
        scsv.getReplaceChars(getmap);
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
    SlightCSV scsv;
    string ex = "";
    map<string, string> setmap;
    string from1 = "t";
    string to1 = "d";
    setmap.insert(pair<string, string>(from1, to1));
    string from2 = "s";
    string to2 = "r";
    setmap.insert(pair<string, string>(from2, to2));
    string c;
    string d;
    map<string, string> getmap;
    size_t cnt = 0;
    try {
        scsv.setReplaceChars(setmap);
        scsv.getReplaceChars(getmap);
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
    SlightCSV scsv;
    string ex = "";
    map<string, string> setmap;
    string from1 = "t";
    string to1 = "d";
    setmap.insert(pair<string, string>(from1, to1));
    string from2 = "s";
    string to2 = "r";
    setmap.insert(pair<string, string>(from2, to2));
    map<string, string> getmap;
    size_t cnt = 0;
    string c;
    string d;
    string cell = "";
    try {
        scsv.setFileName("../../test/env_data_short.csv");
        scsv.setSeparator(";");
        scsv.setReplaceChars(setmap);
        scsv.getReplaceChars(getmap);
        scsv.loadData();
        cnt = getmap.size();
        c = getmap.find(from1)->second;
        d = getmap.find(from2)->second;
        scsv.getCell(cell, 0, 0);
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
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_sli.csv";
    string sep = ";";
    string esc = "\"";
    set<string> stripset;
    string strip = "l";
    stripset.insert(strip);
    map<string, string> setmap;
    string from1 = "d";
    string to1 = "x";
    setmap.insert(pair<string, string>(from1, to1));
    vector<string> row1;
    vector<string> row2;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.setEscape(esc);
        scsv.setStripChars(stripset);
        scsv.setReplaceChars(setmap);
        scsv.loadData();
        scsv.getRow(row1, 0);
        scsv.getRow(row2, 3);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("\"14;0,1\"", row1.at(0));
    CHECK_EQUAL("\"0\r\nxx\"", row2.at(29));
};

TEST(slightcsv, format_header_err) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short_dh.csv";
    string sep = ";";
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("CSV format error (intermediate header).", ex);
};

TEST(slightcsv, set_header_count_no_data_loaded_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.setHeaderCount(0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_cell_bad_row_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    string cell = "";
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getCell(cell, 865, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_cell_bad_column_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    string cell = "";
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getCell(cell, 0, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_2p_bad_column_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> column;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getColumn(column, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_3p_data_not_loaded_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> column;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        // data not loaded
        scsv.getColumn(column, 29, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_column_3p_bad_column_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> column;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getColumn(column, 30, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_4p_data_not_loaded_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> column;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        // data not loaded
        scsv.getColumn(column, 29, 0, 10);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_column_4p_bad_column_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> column;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getColumn(column, 30, 0, 1);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_column_4p_bad_start_cell_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> column;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getColumn(column, 29, 865, 1);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_row_2p_data_not_loaded_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> row;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        // data not loaded
        scsv.getRow(row, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_row_3p_data_not_loaded_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> row;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        // data not loaded
        scsv.getRow(row, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_row_4p_data_not_loaded_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> row;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        // data not loaded
        scsv.getRow(row, 0, 0, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Data not loaded.", ex);
};

TEST(slightcsv, get_row_3p_bad_row_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> row;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getRow(row, 865, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_row_4p_bad_row_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> row;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getRow(row, 865, 0, 30);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, get_row_4p_bad_start_cell_index_ex) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/env_data_short.csv";
    string sep = ";";
    vector<string> row;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.loadData();
        scsv.getRow(row, 864, 30, 1);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Bad row or column index.", ex);
};

TEST(slightcsv, complex_2) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/utf8_test.csv";
    string sep = ";";
    string esc = "\"";
    string strip = "Z";
    set<string> stripset;
    stripset.insert(strip);
    string from = "¥";
    string to = "$";
    map<string, string> repmap;
    repmap.insert(pair<string, string>(from, to));
    string cell1;
    string cell2;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.setEscape(esc);
        scsv.setStripChars(stripset);
        scsv.setReplaceChars(repmap);
        scsv.loadData();
        scsv.getCell(cell1, 2, 2);
        scsv.getCell(cell2, 2, 5);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("\"jack@smith.jp;jack1.smith@jp\"", cell1);
    CHECK_EQUAL("$", cell2);
};

TEST(slightcsv, complex_3) {
    SlightCSV scsv;
    string ex = "";
    string file = "../../test/utf8_test_bom.csv";
    string sep = ";";
    string esc = "\"";
    string strip = "Z";
    set<string> stripset;
    stripset.insert(strip);
    string from = "¥";
    string to = "$";
    map<string, string> repmap;
    repmap.insert(pair<string, string>(from, to));
    string cell1;
    try {
        scsv.setFileName(file);
        scsv.setSeparator(sep);
        scsv.setEscape(esc);
        scsv.setStripChars(stripset);
        scsv.setReplaceChars(repmap);
        scsv.loadData();
        scsv.getCell(cell1, 0, 0);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("date", cell1);
};

TEST(slightcsv, sep_too_long_ex) {
    SlightCSV scsv;
    string ex = "";
    string sep = ";;";
    try {
        scsv.setSeparator(sep);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Separator character invalid or missing.", ex);
};

TEST(slightcsv, esc_too_long_ex) {
    SlightCSV scsv;
    string ex = "";
    string esc = "\".";
    try {
        scsv.setEscape(esc);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Escape character invalid or missing.", ex);
};

TEST(slightcsv, strip_too_long_ex) {
    SlightCSV scsv;
    string ex = "";
    set<string> stripset;
    string strip = "__";
    stripset.insert(strip);
    try {
        scsv.setStripChars(stripset);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Strip character invalid or missing.", ex);
};

TEST(slightcsv, replace_too_long_ex) {
    SlightCSV scsv;
    string ex = "";
    map<string, string> repmap;
    pair<string, string> rep("a", "aa");
    repmap.insert(rep);
    try {
        scsv.setReplaceChars(repmap);
    } catch(const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Replace character invalid or missing.", ex);
};