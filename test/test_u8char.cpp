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

TEST_GROUP(u8char) {
};

TEST(u8char, construct) {
    string ex = "";
    try {
        U8char u8c;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
};

TEST(u8char, add_byte_1) {
    string ex = "";
    unsigned char u8c_first = 111;
    unsigned char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
};

TEST(u8char, add_get_byte_1) {
    string ex = "";
    unsigned char u8c_first = 111;
    unsigned char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c[0];
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(111, c);
};

TEST(u8char, add_get_byte_2) {
    string ex = "";
    unsigned char u8c_first = 111;
    unsigned char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c.getByte(0);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(111, c);
};

TEST(u8char, add_get_byte_3) {
    string ex = "";
    unsigned char u8c_first = 111;
    unsigned char c;
    bool valid;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c.getByte(0);
        valid = u8c.validate();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(111, c);
    CHECK_EQUAL(true, valid);
};

TEST(u8char, add_get_byte_4) {
    string ex = "";
    unsigned char u8c_first = 111;
    unsigned char c;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c.getByte(0);
        valid = u8c.validate();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(111, c);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(1, size);
    };

    TEST(u8char, add_byte_invalid_first) {
    string ex = "";
    unsigned char u8c_first = 168;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF8 format error.", ex);
};

TEST(u8char, add_get_byte_5) {
    string ex = "";
    unsigned char u8c_first = 111;
    unsigned char u8c_second = 168;
    unsigned char c;
    unsigned char d;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        u8c.addByte(u8c_second);
        c = u8c.getByte(0);
        d = u8c.getByte(1);
        valid = u8c.validate();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF8 format error.", ex);
};

TEST(u8char, add_get_byte_6) {
    string ex = "";
    unsigned char u8c_first = 205;
    unsigned char u8c_second = 168;
    unsigned char c;
    unsigned char d;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        u8c.addByte(u8c_second);
        c = u8c[0];
        d = u8c[1];
        valid = u8c.validate();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(205, c);
    CHECK_EQUAL(168, d);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(2, size);
};

TEST(u8char, add_get_byte_7) {
    string ex = "";
    unsigned char u8c_1 = 205;
    unsigned char u8c_2 = 168;
    unsigned char u8c_3 = 1;
    unsigned char c;
    unsigned char d;
    unsigned char e;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
        u8c.addByte(u8c_2);
        u8c.addByte(u8c_3);
        c = u8c[0];
        d = u8c[1];
        e = u8c[2];
        valid = u8c.validate();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF8 format error.", ex);
};

TEST(u8char, add_get_byte_8) {
    string ex = "";
    unsigned char u8c_1 = 237;
    unsigned char u8c_2 = 168;
    unsigned char u8c_3 = 1;
    unsigned char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
        u8c.addByte(u8c_2);
        u8c.addByte(u8c_3);
        c = u8c.getByte(0);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF8 format error.", ex);
};

TEST(u8char, add_get_byte_9) {
    string ex = "";
    unsigned char u8c_1 = 237;
    unsigned char u8c_2 = 168;
    unsigned char u8c_3 = 129;
    unsigned char c;
    unsigned char d;
    unsigned char e;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
        u8c.addByte(u8c_2);
        u8c.addByte(u8c_3);
        c = u8c.getByte(0);
        d = u8c.getByte(1);
        e = u8c.getByte(2);
        valid = u8c.validate();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(237, c);
    CHECK_EQUAL(168, d);
    CHECK_EQUAL(129, e);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(3, size);
};

TEST(u8char, add_get_byte_10) {
    string ex = "";
    unsigned char u8c_1 = 253;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF8 format error.", ex);
};

TEST(u8char, add_get_byte_11) {
    string ex = "";
    unsigned char u8c_1 = 245;
    unsigned char u8c_2 = 168;
    unsigned char u8c_3 = 129;
    unsigned char u8c_4 = 135;
    unsigned char c;
    unsigned char d;
    unsigned char e;
    unsigned char f;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
        u8c.addByte(u8c_2);
        u8c.addByte(u8c_3);
        u8c.addByte(u8c_4);
        c = u8c.getByte(0);
        d = u8c.getByte(1);
        e = u8c.getByte(2);
        f = u8c.getByte(3);
        valid = u8c.validate();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(245, c);
    CHECK_EQUAL(168, d);
    CHECK_EQUAL(129, e);
    CHECK_EQUAL(135, f);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(4, size);
};

TEST(u8char, add_get_byte_12) {
    string ex = "";
    unsigned char u8c_1 = 245;
    unsigned char u8c_2 = 168;
    unsigned char u8c_3 = 129;
    unsigned char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
        u8c.addByte(u8c_2);
        u8c.addByte(u8c_3);
        c = u8c.getByte(0);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF8 format error.", ex);
};

TEST(u8char, equals_0) {
    string ex = "";
    unsigned char c1 = 245;
    unsigned char c2 = 168;
    unsigned char c3 = 129;
    unsigned char c4 = 141;

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
        u8c_1.addByte(c2);
        u8c_1.addByte(c3);
        u8c_1.addByte(c4);
        u8c_2.addByte(c1);
        u8c_2.addByte(c2);
        u8c_2.addByte(c3);
        u8c_2.addByte(c4);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, u8c_1 == u8c_2);
};

TEST(u8char, equals_1) {
    string ex = "";
    unsigned char c1 = 245;
    unsigned char c2 = 168;
    unsigned char c3 = 129;
    unsigned char c4 = 141;

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
        u8c_1.addByte(c3);
        u8c_1.addByte(c2);
        u8c_1.addByte(c4);
        u8c_2.addByte(c1);
        u8c_2.addByte(c2);
        u8c_2.addByte(c3);
        u8c_2.addByte(c4);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, u8c_1 == u8c_2);
};

TEST(u8char, equals_2) {
    string ex = "";
    unsigned char c1 = 245;
    unsigned char c2 = 168;
    unsigned char c3 = 129;
    unsigned char c4 = 141;

    U8char u8c_1;
    U8char u8c_2;

    try {

    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, u8c_1 == u8c_2);
};

TEST(u8char, equals_3) {
    string ex = "";
    unsigned char c1 = 245;
    unsigned char c2 = 168;
    unsigned char c3 = 129;
    unsigned char c4 = 141;

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, u8c_1 == u8c_2);
};

TEST(u8char, equals_4) {
    string ex = "";
    unsigned char c1 = 245;
    unsigned char c2 = 168;
    unsigned char c3 = 129;
    unsigned char c4 = 141;

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, u8c_1 == u8c_2);
};

TEST(u8char, equals_5) {
    string ex = "";
    unsigned char c1 = 245;
    unsigned char c2 = 168;
    unsigned char c3 = 129;
    unsigned char c4 = 141;

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
        u8c_1.addByte(c2);
        u8c_2.addByte(c2 + 1);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, u8c_1 == u8c_2);
};

TEST(u8char, equals_clear_6) {
    string ex = "";
    unsigned char c1 = 245;
    unsigned char c2 = 168;
    unsigned char c3 = 129;

    U8char u8c_1;
    U8char u8c_2;

    bool first_comp;
    bool sec_comp;

    try {
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
        u8c_1.addByte(c2);
        u8c_2.addByte(c2 + 1);
        first_comp = u8c_1 == u8c_2;
        u8c_1.clear();
        u8c_2.clear();
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
        u8c_1.addByte(c2);
        u8c_2.addByte(c2);
        sec_comp = u8c_1 == u8c_2;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, first_comp);
    CHECK_EQUAL(true, sec_comp);
};