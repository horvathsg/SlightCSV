// SlightCSV - a simple and lightweight CSV parser library
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
#include "slightrow.hpp"

using std::string;
using std::vector;
using std::exception;
using utils::SlightCSV;
using utils::SlightRow;

TEST_GROUP(slightrow) {
};

TEST_GROUP(slightcsv) {
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

// IGNORE_TEST(slightcsv,get_matrix_nofile_nosep_noload) {
//     SlightCSV csv_parser;
//     string t = "";
//     vector<vector<string> > vect;
//     try {
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//         t = e.what();
//     }
//     CHECK_EQUAL("Data not loaded.", t);
// };

// IGNORE_TEST(slightcsv,get_matrix_nosep_noload) {
//     SlightCSV csv_parser;
//     string t = "";
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//         t = e.what();
//     }
//     CHECK_EQUAL("Data not loaded.", t);
// };

// IGNORE_TEST(slightcsv,get_matrix_noload) {
//     SlightCSV csv_parser;
//     string t = "";
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//         t = e.what();
//     }
//     CHECK_EQUAL("Data not loaded.", t);
// };

// IGNORE_TEST(slightcsv,get_matrix_ok) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL(8641, vect.size());
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_0_0) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("10", vect.at(1).at(0));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_0_29) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("0", vect.at(1).at(29));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_0_9) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("10", vect.at(1).at(9));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_0_21) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("10", vect.at(1).at(21));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_5434_0) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("10", vect.at(5435).at(0));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_5434_28) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("0,7", vect.at(5435).at(28));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_5434_29) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("0", vect.at(5435).at(29));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_8639_0) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("10", vect.at(8640).at(0));
// };

// IGNORE_TEST(slightcsv,get_matrix_ok_verify_8639_29) {
//     SlightCSV csv_parser;
//     string t;
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.setSeparator(';');
//         csv_parser.loadData();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL("0", vect.at(8640).at(29));
// };

TEST(slightcsv,get_column_nofile_nosep_noload) {
    SlightCSV csv_parser;
    string t = "";
    vector<string> vect;
    try {
        csv_parser.getDataColumn(vect, 0);
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
        csv_parser.getDataColumn(vect, 0);
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
        csv_parser.getDataColumn(vect, 0);
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
        csv_parser.getDataColumn(vect, 0);
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
        csv_parser.getDataColumn(vect, 0);
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
        csv_parser.getDataColumn(vect, 0);
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
        csv_parser.getDataColumn(vect, 0);
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
        csv_parser.getDataColumn(vect, 29);
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
        csv_parser.getDataColumn(vect, 29);
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
        csv_parser.getDataColumn(vect, 29);
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
        csv_parser.getDataColumn(vect, 1);
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
        csv_parser.getDataColumn(vect, 28);
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
        csv_parser.getDataColumn(vect, 28);
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
        csv_parser.getDataColumn(vect, 28);
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
        csv_parser.getDataColumn(vect, 4);
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
        csv_parser.getDataColumn(vect, 28);
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
        csv_parser.getDataColumn(vect, 28);
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
        csv_parser.getDataColumn(vect, 28);
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
        csv_parser.getDataColumn(vect, 1);
    } catch(exception &e) {
        t = e.what();
    }
    CHECK_EQUAL("Data not loaded.", t);
};

// IGNORE_TEST(slightcsv,get_matrix_after_reset) {
//     SlightCSV csv_parser;
//     string t = "";
//     vector<vector<string> > vect;
//     try {
//         csv_parser.setSeparator(';');
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.loadData();
//         csv_parser.unloadData();
//         csv_parser.loadData();
//         csv_parser.reset();
//         csv_parser.getDataMatrix(vect);
//     } catch(exception &e) {
//         t = e.what();
//     }
//     CHECK_EQUAL("Data not loaded.", t);
// };

// IGNORE_TEST(slightcsv,setup_load_get_fter_reset) {
//     SlightCSV csv_parser;
//     string t;
//     vector<float> vect;
//     try {
//         csv_parser.setSeparator(';');
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.loadData();
//         csv_parser.unloadData();
//         csv_parser.loadData();
//         csv_parser.reset();
//         csv_parser.setSeparator(';');
//         csv_parser.setFileName("../../test/env_data.csv");
//         csv_parser.loadData();
//         csv_parser.unloadData();
//         csv_parser.loadData();
//         csv_parser.getDataColumn(vect, 28);
//     } catch(exception &e) {
//     }
//     CHECK_EQUAL(0.1f, vect.at(8633));
// };

IGNORE_TEST(slightcsv,load_large_csv) {
    SlightCSV csv_parser;
    csv_parser.setFileName("../../test/Crimes_-_2001_to_present_1000k.csv");
    csv_parser.setSeparator(',');
    csv_parser.loadData();
    CHECK_EQUAL(1000000, csv_parser.getRowCount());
}