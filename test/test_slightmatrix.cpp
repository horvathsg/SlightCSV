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

#include "slightmatrix.hpp"

using std::string;
using std::vector;
using std::exception;
using utils::SlightMatrix;

TEST_GROUP(slightmatrix) {
};

TEST(slightmatrix, construct) {
    string msg = "";
    try {
        SlightMatrix sm;
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
}

TEST(slightmatrix, get_init_capacity) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        cnt = sm.getCapacity();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(0, cnt);
}

TEST(slightmatrix, set_capacity_0) {
    string msg = "";
    try {
        SlightMatrix sm;
        sm.setCapacity(0);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid parameter.", msg);
}

TEST(slightmatrix, set_get_capacity_1000) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setCapacity(1000);
        cnt = sm.getCapacity();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(1000, cnt);
}

TEST(slightmatrix, get_column_count_init) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        cnt = sm.getColumnCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(0, cnt);
}

TEST(slightmatrix, get_set_column_count_30) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(30);
        cnt = sm.getColumnCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(30, cnt);
}

TEST(slightmatrix, get_row_count_init) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(0, cnt);
}

TEST(slightmatrix, get_row_count_0_0) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(0, cnt);
}

TEST(slightmatrix, get_row_count_1_1) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("test");
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(1, cnt);
}

TEST(slightmatrix, get_row_count_1_3) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("test");
        sm.addCell("test");
        sm.addCell("test");
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(1, cnt);
}

TEST(slightmatrix, get_row_count_2_4) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("test");
        sm.addCell("test");
        sm.addCell("test");
        sm.addCell("test");
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(2, cnt);
}

TEST(slightmatrix, add_cell_6_empty) {
    string msg = "";
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("");
        sm.addCell("");
        sm.addCell("");
        sm.addCell("");
        sm.addCell("");
        sm.addCell("");
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(2, cnt);
}

TEST(slightmatrix, add_get_cell_1) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("abc");
        sm.addCell("def");
        sm.addCell("ghi");
        sm.addCell("jkl");
        sm.addCell("mno");
        sm.addCell("pqr");
        sm.getCell(cell, 0, 0);
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL("abc", cell);
    CHECK_EQUAL(2, cnt);
}

TEST(slightmatrix, add_get_cell_2) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("abc");
        sm.addCell("def");
        sm.addCell("ghi");
        sm.getCell(cell, 0, 2);
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL("ghi", cell);
    CHECK_EQUAL(1, cnt);
}

TEST(slightmatrix, add_get_cell_3) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("abc");
        sm.addCell("def");
        sm.addCell("ghi");
        sm.addCell("jkl");
        sm.addCell("mno");
        sm.addCell("pqr");
        sm.getCell(cell, 1, 0);
        cnt = sm.getRowCount();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL("jkl", cell);
    CHECK_EQUAL(2, cnt);
}

TEST(slightmatrix, add_get_cell_4_invalid_column) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("abc");
        sm.addCell("def");
        sm.addCell("ghi");
        sm.addCell("jkl");
        sm.addCell("mno");
        sm.addCell("pqr");
        sm.getCell(cell, 1, 3);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid column count or index.", msg);
}

TEST(slightmatrix, add_get_cell_5_invalid_row) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        sm.addCell("abc");
        sm.addCell("def");
        sm.addCell("ghi");
        sm.addCell("jkl");
        sm.addCell("mno");
        sm.addCell("pqr");
        sm.getCell(cell, 2, 0);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid row count or index.", msg);
}

TEST(slightmatrix, add_get_cells_1) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    vector<string> cells;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        sm.addCells(cells);
        sm.getCell(cell, 0, 0);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL("abc", cell);
}

TEST(slightmatrix, add_get_cells_2) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    vector<string> cells;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        sm.addCells(cells);
        sm.getCell(cell, 0, 2);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL("ghi", cell);
}

TEST(slightmatrix, add_get_cells_3) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    vector<string> cells;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        sm.getCell(cell, 1, 0);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL("jkl", cell);
}

TEST(slightmatrix, add_get_cells_4_invalid_column) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    vector<string> cells;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        sm.addCells(cells);
        sm.getCell(cell, 0, 3);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid column count or index.", msg);
}

TEST(slightmatrix, add_get_cells_5_invalid_row) {
    string msg = "";
    size_t cnt = 0;
    string cell = "";
    vector<string> cells;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        sm.addCells(cells);
        sm.getCell(cell, 2, 0);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid matrix (rows incomplete or column count not set).", msg);
}

TEST(slightmatrix, validate_invalid_1_missing_cells) {
    string msg = "";
    vector<string> cells;
    bool valid = true;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        sm.addCells(cells);
        valid = sm.validate();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(false, valid);
}

TEST(slightmatrix, validate_invalid_2_column_cnt_not_set) {
    string msg = "";
    vector<string> cells;
    bool valid = true;
    try {
        SlightMatrix sm;
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        sm.addCells(cells);
        valid = sm.validate();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(false, valid);
}

TEST(slightmatrix, validate_valid) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        sm.addCells(cells);
        valid = sm.validate();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
}

TEST(slightmatrix, getrow_1_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 0);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL("abc", row.at(0));
    CHECK_EQUAL("def", row.at(1));
    CHECK_EQUAL("ghi", row.at(2));
}

TEST(slightmatrix, getrow_2_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL("jkl", row.at(0));
    CHECK_EQUAL("mno", row.at(1));
    CHECK_EQUAL("pqr", row.at(2));
}

TEST(slightmatrix, getrow_3_invalid_row_id) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 2);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid row count or index.", msg);
    CHECK_EQUAL(true, valid);
}

TEST(slightmatrix, getrow_4_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1, 1);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(2, cnt);
    CHECK_EQUAL("mno", row.at(0));
    CHECK_EQUAL("pqr", row.at(1));
}

TEST(slightmatrix, getrow_5_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1, 2);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("pqr", row.at(0));
}

TEST(slightmatrix, getrow_6_range_error) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1, 3);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid column count or index.", msg);
}

TEST(slightmatrix, getrow_7_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1, 1, 2);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(2, cnt);
    CHECK_EQUAL("mno", row.at(0));
    CHECK_EQUAL("pqr", row.at(1));
}

TEST(slightmatrix, getrow_8_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1, 1, 1);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("mno", row.at(0));
}

TEST(slightmatrix, getrow_9_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1, 2, 1);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(1, cnt);
    CHECK_EQUAL("pqr", row.at(0));
}

TEST(slightmatrix, getrow_10_ex) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> row;
    size_t cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(3);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        cells.push_back("mno");
        cells.push_back("pqr");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getRow(row, 1, 2, 2);
        cnt = row.size();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid column count or index.", msg);
}

TEST(slightmatrix, getcolumn_1_string_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> column;
    string str = "";
    size_t size = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getColumn(column, 0);
        size = column.size();
        str = column.at(0);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(1, size);
    CHECK_EQUAL("abc", str);
}

TEST(slightmatrix, getcolumn_2_string_invalid) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<string> column;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("abc");
        cells.push_back("def");
        cells.push_back("ghi");
        cells.push_back("jkl");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getColumn(column, 4);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("Invalid column count or index.", msg);
    CHECK_EQUAL(true, valid);
}

TEST(slightmatrix, getcolumn_3_float_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<float> column;
    size_t size = 0;
    float a = 0;
    float b = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("0");
        cells.push_back("0.1");
        cells.push_back("0.2");
        cells.push_back("0.25");
        cells.push_back("0.3");
        cells.push_back("0.35");
        cells.push_back("0.5");
        cells.push_back("100.25");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getColumn(column, 1);
        size = column.size();
        a = column.at(0);
        b = column.at(1);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(2, size);
    CHECK_EQUAL(0.1f, a);
    CHECK_EQUAL(0.35f, b);
}

TEST(slightmatrix, getcolumn_3_double_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<double> column;
    size_t size = 0;
    float a = 0;
    float b = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("0");
        cells.push_back("0.1");
        cells.push_back("0.2");
        cells.push_back("0.25");
        cells.push_back("0.3");
        cells.push_back("0.35");
        cells.push_back("0.5");
        cells.push_back("100.25");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getColumn(column, 1);
        size = column.size();
        a = column.at(0);
        b = column.at(1);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(2, size);
    CHECK_EQUAL(0.1f, a);
    CHECK_EQUAL(0.35f, b);
}

TEST(slightmatrix, getcolumn_3_int_ok) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<int> column;
    size_t size = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("0");
        cells.push_back("1");
        cells.push_back("2");
        cells.push_back("25");
        cells.push_back("3");
        cells.push_back("35");
        cells.push_back("-5");
        cells.push_back("100");
        cells.push_back("50");
        cells.push_back("51");
        cells.push_back("49");
        cells.push_back("45");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getColumn(column, 3);
        size = column.size();
        a = column.at(0);
        b = column.at(1);
        c = column.at(2);
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(3, size);
    CHECK_EQUAL(25, a);
    CHECK_EQUAL(100, b);
    CHECK_EQUAL(45, c);
}

TEST(slightmatrix, reset) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    vector<int> column;
    size_t size = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    size_t col_cnt;
    size_t row_cnt;
    size_t cap;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("0");
        cells.push_back("1");
        cells.push_back("2");
        cells.push_back("25");
        cells.push_back("3");
        cells.push_back("35");
        cells.push_back("-5");
        cells.push_back("100");
        cells.push_back("50");
        cells.push_back("51");
        cells.push_back("49");
        cells.push_back("45");
        sm.addCells(cells);
        valid = sm.validate();
        sm.getColumn(column, 3);
        size = column.size();
        a = column.at(0);
        b = column.at(1);
        c = column.at(2);
        sm.reset();
        col_cnt = sm.getColumnCount();
        row_cnt = sm.getRowCount();
        cap = sm.getCapacity();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(3, size);
    CHECK_EQUAL(25, a);
    CHECK_EQUAL(100, b);
    CHECK_EQUAL(45, c);
    CHECK_EQUAL(0, col_cnt);
    CHECK_EQUAL(0, row_cnt);
    CHECK_EQUAL(0, cap);
}

TEST(slightmatrix, set_get_header_count_valid_1) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    size_t header_cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("0");
        cells.push_back("1");
        cells.push_back("2");
        cells.push_back("25");
        cells.push_back("3");
        cells.push_back("35");
        cells.push_back("-5");
        cells.push_back("100");
        cells.push_back("50");
        cells.push_back("51");
        cells.push_back("49");
        cells.push_back("45");
        sm.addCells(cells);
        header_cnt = sm.getHeaderCount();
        valid = sm.validate();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(0, header_cnt);
}

TEST(slightmatrix, set_get_header_count_valid_2) {
    string msg = "";
    vector<string> cells;
    bool valid = false;
    size_t header_cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("0");
        cells.push_back("1");
        cells.push_back("2");
        cells.push_back("25");
        cells.push_back("3");
        cells.push_back("35");
        cells.push_back("-5");
        cells.push_back("100");
        cells.push_back("50");
        cells.push_back("51");
        cells.push_back("49");
        cells.push_back("45");
        sm.addCells(cells);
        sm.setHeaderCount(2);
        header_cnt = sm.getHeaderCount();
        valid = sm.validate();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(2, header_cnt);
}

TEST(slightmatrix, set_get_header_count_invalid) {
    string msg = "";
    vector<string> cells;
    bool valid = true;
    size_t header_cnt = 0;
    try {
        SlightMatrix sm;
        sm.setColumnCount(4);
        cells.push_back("0");
        cells.push_back("1");
        cells.push_back("2");
        cells.push_back("25");
        cells.push_back("3");
        cells.push_back("35");
        cells.push_back("-5");
        cells.push_back("100");
        cells.push_back("50");
        cells.push_back("51");
        cells.push_back("49");
        cells.push_back("45");
        sm.addCells(cells);
        sm.setHeaderCount(3);
        header_cnt = sm.getHeaderCount();
        valid = sm.validate();
    } catch (exception &e) {
        msg = e.what();
    }
    CHECK_EQUAL("", msg);
    CHECK_EQUAL(false, valid);
    CHECK_EQUAL(3, header_cnt);
}