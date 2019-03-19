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