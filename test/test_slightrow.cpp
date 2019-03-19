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

#include "slightrow.hpp"

using std::string;
using std::vector;
using std::exception;
using utils::SlightRow;

TEST_GROUP(slightrow) {
};

TEST(slightrow, get_input_wo_set) {
    SlightRow row;
    string exs = "";
    try {
        string s = row.getInput();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Input string is not defined or empty.", exs);
}

TEST(slightrow, set_input_empty) {
    SlightRow row;
    string exs = "";
    string str = "";
    try {
        row.setInput(str);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Input string is not defined or empty.", exs);
}

TEST(slightrow, set_get_input) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test\n";
    try {
        row.setInput(str);
        str = row.getInput();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("this;is;a;test\n", str);
}

TEST(slightrow, get_separator_wo_set) {
    SlightRow row;
    string exs = "";
    char c = 0;
    try {
        c = row.getSeparator();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Separator is not defined or empty.", exs);
}

TEST(slightrow, set_separator_empty) {
    SlightRow row;
    string exs = "";
    char c = 0;
    try {
        row.setSeparator(c);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Separator is not defined or empty.", exs);
}

TEST(slightrow, set_get_separator) {
    SlightRow row;
    string exs = "";
    char c = ',';
    try {
        row.setSeparator(c);
        c = row.getSeparator();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(',', c);
}

TEST(slightrow, process_noin_nosep) {
    SlightRow row;
    string exs = "";
    try {
        row.process();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Input string is not defined or empty.", exs);
}

TEST(slightrow, process_nosep) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test";
    try {
        row.setInput(str);
        row.process();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Separator is not defined or empty.", exs);
}

TEST(slightrow, process_noin) {
    SlightRow row;
    string exs = "";
    char sep = ';';
    try {
        row.setSeparator(sep);
        row.process();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Input string is not defined or empty.", exs);
}

TEST(slightrow, process_ok) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test";
    char sep = ';';
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("", exs);
}

TEST(slightrow, get_cell_cnt_noproc_noin_nosep) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test";
    char sep = ';';
    try {
        row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Row not processed.", exs);
}

TEST(slightrow, get_cell_cnt_noin_nosep) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test";
    char sep = ';';
    try {
        row.process();
        row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Input string is not defined or empty.", exs);
}

TEST(slightrow, get_cell_cnt_nosep) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test";
    char sep = ';';
    try {
        row.setInput(str);
        row.process();
        row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Separator is not defined or empty.", exs);
}

TEST(slightrow, get_cell_cnt_ok_4_lenok_hassep_noendsep) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test";
    char sep = ';';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(4, cnt);
}

TEST(slightrow, get_cell_cnt_ok_4_lenok_hassep_hasendsep) {
    SlightRow row;
    string exs = "";
    string str = "this;is;a;test;";
    char sep = ';';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(5, cnt);
}

TEST(slightrow, get_cell_cnt_ok_18_lenok_hassep_noendsep) {
    SlightRow row;
    string exs = "";
    string str = "another,example,of,a,string,with,a,slightly,different,line,ending,character,.,will,it,blend?,";
    char sep = ',';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(17, cnt);
}

TEST(slightrow, get_cell_cnt_ok_19_lenok_hassep_hasendsep) {
    SlightRow row;
    string exs = "";
    string str = "another,example,of,a,string,with,a,slightly,different,line,ending,character,.,will,it,work,or,not?,a,";
    char sep = ',';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(20, cnt);
}

TEST(slightrow, get_cell_cnt_ok_22_lenok_hasssep_noendsep) {
    SlightRow row;
    string exs = "";
    string str = "12345678987654345676543234567897654212345621391288654321234567898654312345676543212345678976776566543212343221234545678976786565421234567898654321";
    char sep = '5';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(22, cnt);
}

TEST(slightrow, get_cell_cnt_ok_22_lenok_hasssep_hasendsep) {
    SlightRow row;
    string exs = "";
    string str = "123456789876543456765432345678976542123456213912886543212345678986543123456765432123456789767765665432123432212345456789767865654212345678986543215";
    char sep = '5';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(23, cnt);
}

TEST(slightrow, get_cell_cnt_ok_1_lenok_nosep_noendsep_1) {
    SlightRow row;
    string exs = "";
    string str = "dfhsdbfjhdsbfjshbfshjbhjsbffhjdsbj hdshbfjhsdbfhjb dsjhfbshdjbfjhsbdjfjds";
    char sep = ';';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(1, cnt);
}

TEST(slightrow, get_cell_cnt_ok_0_nolen_hassep_hasendsep) {
    SlightRow row;
    string exs = "";
    string str = ";;;;;;;;;;;;;;;;;;";
    char sep = ';';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(19, cnt);
}

TEST(slightrow, get_cell_cnt_ok_0_nolen_hassep_noendsep) {
    SlightRow row;
    string exs = "";
    string str = ";;;;;;;;;;;;;;;;;;1";
    char sep = ';';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(19, cnt);
}

TEST(slightrow, get_cell_cnt_ok_0_nolen_hassep_noend_hasendsep) {
    SlightRow row;
    string exs = "";
    string str = ";";
    char sep = ';';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(2, cnt);
}

TEST(slightrow, get_cell_cnt_ok_1_lenok_nosep_noendsep_2) {
    SlightRow row;
    string exs = "";
    string str = "A";
    char sep = ';';
    size_t cnt;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        cnt = row.getCellCount();
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(1 , cnt);
}

TEST(slightrow, getcells_noin_nosep_noproc) {
    SlightRow row;
    string exs = "";
    string str = "";
    char sep;
    bool b;
    vector<string> vect;
    try {
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Row not processed." , exs);
}

TEST(slightrow, getcells_nosep_noproc) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    char sep;
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Row not processed." , exs);
}

TEST(slightrow, getcells_noproc) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    char sep = ';';
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Row not processed." , exs);
}

TEST(slightrow, getcells_ok_1) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    char sep = ';';
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(1, vect.size());
    CHECK_EQUAL("testtesttesttesttesttesttesttesttesttesttesttesttesttesttest", vect.at(0));
}

TEST(slightrow, getcells_ok_2) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    char sep = 't';
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(31, vect.size());
    CHECK_EQUAL("0", vect.at(0));
    CHECK_EQUAL("es", vect.at(1));
    CHECK_EQUAL("0", vect.at(2));
    CHECK_EQUAL("es", vect.at(3));
    CHECK_EQUAL("es", vect.at(29));
    CHECK_EQUAL("0", vect.at(30));
}

TEST(slightrow, reset_1) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    char sep = 't';
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        row.reset();
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Row not processed.", exs);
}

TEST(slightrow, reset_2) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    char sep = 't';
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        row.reset();
        row.process();
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Input string is not defined or empty.", exs);
}

TEST(slightrow, reset_3) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    string str2 = "now;try;with;another;input;string";
    char sep = 't';
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        row.reset();
        row.setInput(str2);
        row.process();
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL("Separator is not defined or empty.", exs);
}

TEST(slightrow, reset_4) {
    SlightRow row;
    string exs = "";
    string str = "testtesttesttesttesttesttesttesttesttesttesttesttesttesttest";
    string str2 = "now;try;with;another;input;string";
    char sep = 't';
    char sep2 = ';';
    bool b;
    vector<string> vect;
    try {
        row.setInput(str);
        row.setSeparator(sep);
        row.process();
        row.reset();
        row.setInput(str2);
        row.setSeparator(sep2);
        row.process();
        row.getCells(vect);
    } catch (exception &e) {
        exs = e.what();
    }
    CHECK_EQUAL(6, vect.size());
    CHECK_EQUAL("now", vect.at(0));
    CHECK_EQUAL("string", vect.at(5));
}

TEST(slightrow, escape_quotes_1) {
    SlightRow row;
    string str = "test,test,\"test,test\"";
    char sep = ',';
    vector<string> vect;
    row.setInput(str);
    row.setSeparator(sep);
    row.process();
    row.getCells(vect);
    CHECK_EQUAL(3, vect.size());
    CHECK_EQUAL("test", vect.at(0));
    CHECK_EQUAL("test", vect.at(1));
    CHECK_EQUAL("\"test,test\"", vect.at(2));
}

TEST(slightrow, escape_quotes_2) {
    SlightRow row;
    string str = "test,test,\"test,test\",";
    char sep = ',';
    vector<string> vect;
    row.setInput(str);
    row.setSeparator(sep);
    row.process();
    row.getCells(vect);
    CHECK_EQUAL(4, vect.size());
    CHECK_EQUAL("test", vect.at(0));
    CHECK_EQUAL("test", vect.at(1));
    CHECK_EQUAL("\"test,test\"", vect.at(2));
    CHECK_EQUAL("0", vect.at(3));
}

TEST(slightrow, escape_quotes_3) {
    SlightRow row;
    string str = "test,,test,\"test,,test\",,";
    char sep = ',';
    vector<string> vect;
    row.setInput(str);
    row.setSeparator(sep);
    row.process();
    row.getCells(vect);
    CHECK_EQUAL(6, vect.size());
    CHECK_EQUAL("test", vect.at(0));
    CHECK_EQUAL("0", vect.at(1));
    CHECK_EQUAL("test", vect.at(2));
    CHECK_EQUAL("\"test,,test\"", vect.at(3));
    CHECK_EQUAL("0", vect.at(4));
    CHECK_EQUAL("0", vect.at(5));
}

TEST(slightrow, escape_quotes_4) {
    SlightRow row;
    string str = "test,,test,\"test,,test,,";
    char sep = ',';
    vector<string> vect;
    row.setInput(str);
    row.setSeparator(sep);
    row.process();
    row.getCells(vect);
    CHECK_EQUAL(4, vect.size());
    CHECK_EQUAL("test", vect.at(0));
    CHECK_EQUAL("0", vect.at(1));
    CHECK_EQUAL("test", vect.at(2));
    CHECK_EQUAL("\"test,,test,,", vect.at(3));
}

TEST(slightrow, escape_quotes_5) {
    SlightRow row;
    string str = "\"test,,test,\"test,\",test,\",";
    char sep = ',';
    vector<string> vect;
    row.setInput(str);
    row.setSeparator(sep);
    row.process();
    row.getCells(vect);
    CHECK_EQUAL(3, vect.size());
    CHECK_EQUAL("\"test,,test,\"test", vect.at(0));
    CHECK_EQUAL("\",test,\"", vect.at(1));
    CHECK_EQUAL("0", vect.at(2));
}

TEST(slightrow, escape_quotes_6) {
    SlightRow row;
    string str = "11241824,JB166932,03/07/2016 09:00:00 AM,053XX W IRVING PARK RD,1130,DECEPTIVE PRACTICE,FRAUD OR CONFIDENCE GAME,AUTO / BOAT / RV DEALERSHIP,false,false,1634,016,38,15,11,,,2016,02/28/2018 04:16:24 PM,,,";
    char sep = ',';
    vector<string> vect;
    row.setInput(str);
    row.setSeparator(sep);
    row.process();
    row.getCells(vect);
    CHECK_EQUAL(22, vect.size());
}

TEST(slightrow, get_is_header_exception) {
    string ex = "";
    try {
        SlightRow row;
        row.getIsHeader();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("Row not processed.", ex);
}

TEST(slightrow, get_is_header_true_alpha_only) {
    string ex = "";
    bool is_header = false;
    string str = "this,is,a,header";
    try {
        SlightRow row;
        row.setInput(str);
        row.setSeparator(',');
        row.process();
        is_header = row.getIsHeader();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL(true, is_header);
}

TEST(slightrow, get_is_header_true_mixed_1) {
    string ex = "";
    bool is_header = false;
    string str = "this 41,is 5,a 5,header4,even,if,it,contains,some,numbers";
    try {
        SlightRow row;
        row.setInput(str);
        row.setSeparator(',');
        row.process();
        is_header = row.getIsHeader();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL(true, is_header);
}

TEST(slightrow, get_is_header_false_mixed_2) {
    string ex = "";
    bool is_header = true;
    string str = "this 41,is 5,not44,a 5,header4";
    try {
        SlightRow row;
        row.setInput(str);
        row.setSeparator(',');
        row.process();
        is_header = row.getIsHeader();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL(false, is_header);
}

TEST(slightrow, get_is_header_false_nums_only) {
    string ex = "";
    bool is_header = true;
    string str = "4534354,345345345,43534534,34534,534543,342,2,2,2,2";
    try {
        SlightRow row;
        row.setInput(str);
        row.setSeparator(',');
        row.process();
        is_header = row.getIsHeader();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL(false, is_header);
}