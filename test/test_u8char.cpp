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
    // 01101111 (traditional ASCII char)
    char u8c_first = '\x6f';
    char c;
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
    // 01101111 (traditional ASCII char)
    char u8c_first = '\x6f';
    char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c[0];
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL('\x6f', c);
};

TEST(u8char, add_get_byte_2) {
    string ex = "";
    // 01101111 (traditional ASCII char)
    char u8c_first = '\x6f';
    char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c.getByte(0);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL('\x6f', c);
};

TEST(u8char, add_get_byte_3) {
    string ex = "";
    // 01101111 (traditional ASCII char)
    char u8c_first = '\x6f';
    char c;
    bool valid;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c.getByte(0);
        valid = u8c.isValid();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL('\x6f', c);
    CHECK_EQUAL(true, valid);
};

TEST(u8char, add_get_byte_4) {
    string ex = "";
    // 01101111 (traditional ASCII char)
    char u8c_first = '\x6f';
    char c;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        c = u8c.getByte(0);
        valid = u8c.isValid();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL('\x6f', c);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(1, size);
    };

    TEST(u8char, add_byte_invalid_first) {
    string ex = "";
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_first = '\xa8';
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF-8 format error.", ex);
};

TEST(u8char, add_get_byte_5) {
    string ex = "";
    // 01101111 (traditional ASCII char)
    char u8c_first = '\x6f';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_second = '\xa8';
    char c;
    char d;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        u8c.addByte(u8c_second);
        c = u8c.getByte(0);
        d = u8c.getByte(1);
        valid = u8c.isValid();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF-8 format error.", ex);
};

TEST(u8char, add_get_byte_6) {
    string ex = "";
    // 11001101 (starting byte beginning with 110 - only valid as first byte of 2 bytes sequence)
    char u8c_first = '\xcd';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_second = '\xa8';
    char c;
    char d;
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_first);
        u8c.addByte(u8c_second);
        c = u8c[0];
        d = u8c[1];
        valid = u8c.isValid();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL('\xcd', c);
    CHECK_EQUAL('\xa8', d);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(2, size);
};

TEST(u8char, add_get_byte_7) {
    string ex = "";
    // 11001101 (starting byte beginning with 110 - only valid as first byte of 2 bytes sequence)
    char u8c_1 = '\xcd';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_2 = '\xa8';
    // 00000001 (invalid UTF-8 byte)
    char u8c_3 = '\x01';
    char c;
    char d;
    char e;
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
        valid = u8c.isValid();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF-8 format error.", ex);
};

TEST(u8char, add_get_byte_8) {
    string ex = "";
    // 11101101 (starting byte beginning with 1110 - only valid as first byte of 3 bytes sequence)
    char u8c_1 = '\xed';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_2 = '\xa8';
    // 00000001 (invalid UTF-8 byte)
    char u8c_3 = '\x01';
    char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
        u8c.addByte(u8c_2);
        u8c.addByte(u8c_3);
        c = u8c.getByte(0);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF-8 format error.", ex);
};

TEST(u8char, add_get_byte_9) {
    string ex = "";
    // 11101101 (starting byte beginning with 1110 - only valid as first byte of 3 bytes sequence)
    char u8c_1 = '\xed';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_3 = '\x81';
    char c;
    char d;
    char e;
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
        valid = u8c.isValid();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL('\xed', c);
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    CHECK_EQUAL('\xa8', d);
    CHECK_EQUAL('\x81', e);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(3, size);
};

TEST(u8char, add_get_byte_10) {
    string ex = "";
    // 11111101 (invalid UTF-8 byte)
    char u8c_1 = '\xfd';
    bool valid;
    int size;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF-8 format error.", ex);
};

TEST(u8char, add_get_byte_11) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char u8c_1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_3 = '\x81';
    // 10000111 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_4 = '\x87';
    char c;
    char d;
    char e;
    char f;
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
        valid = u8c.isValid();
        size = u8c.size();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL('\xf5', c);
    CHECK_EQUAL('\xa8', d);
    CHECK_EQUAL('\x81', e);
    CHECK_EQUAL('\x87', f);
    CHECK_EQUAL(true, valid);
    CHECK_EQUAL(4, size);
};

TEST(u8char, add_get_byte_12) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char u8c_1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char u8c_3 = '\x81';
    char c;
    try {
        U8char u8c;
        u8c.addByte(u8c_1);
        u8c.addByte(u8c_2);
        u8c.addByte(u8c_3);
        c = u8c.getByte(0);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("UTF-8 format error.", ex);
};

TEST(u8char, equals_0) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char c1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char c2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char c3 = '\x81';
    // 10001101 (continuation byte beginning with 10 - not valid as first byte)
    char c4 = '\x8d';

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
    CHECK_EQUAL(false, u8c_1 != u8c_2);
};

TEST(u8char, equals_1) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char c1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char c2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char c3 = '\x81';
    // 10001101 (continuation byte beginning with 10 - not valid as first byte)
    char c4 = '\x8d';

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
    CHECK_EQUAL(true, u8c_1 != u8c_2);
};

TEST(u8char, equals_2) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char c1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char c2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char c3 = '\x81';
    // 10001101 (continuation byte beginning with 10 - not valid as first byte)
    char c4 = '\x8d';

    U8char u8c_1;
    U8char u8c_2;

    try {

    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, u8c_1 == u8c_2);
    CHECK_EQUAL(false, u8c_1 != u8c_2);
};

TEST(u8char, equals_3) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char c1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char c2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char c3 = '\x81';
    // 10001101 (continuation byte beginning with 10 - not valid as first byte)
    char c4 = '\x8d';

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
        u8c_1.addByte(c2);
        u8c_1.addByte(c3);
        u8c_1.addByte(c4);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, u8c_1 == u8c_2);
    CHECK_EQUAL(true, u8c_1 != u8c_2);
};

TEST(u8char, equals_4) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char c1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char c2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char c3 = '\x81';
    // 10001101 (continuation byte beginning with 10 - not valid as first byte)
    char c4 = '\x8d';

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
        u8c_1.addByte(c2);
        u8c_2.addByte(c2);
        u8c_1.addByte(c3);
        u8c_2.addByte(c3);
        u8c_1.addByte(c4);
        u8c_2.addByte(c4);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, u8c_1 == u8c_2);
    CHECK_EQUAL(false, u8c_1 != u8c_2);
};

TEST(u8char, equals_5) {
    string ex = "";
    // 11110101 (starting byte beginning with 11110 - only valid as first byte of 4 bytes sequence)
    char c1 = '\xf5';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char c2 = '\xa8';
    // 10000001 (continuation byte beginning with 10 - not valid as first byte)
    char c3 = '\x81';
    // 10001101 (continuation byte beginning with 10 - not valid as first byte)
    char c4 = '\x8d';

    U8char u8c_1;
    U8char u8c_2;

    try {
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
        u8c_1.addByte(c2);
        u8c_2.addByte(c2 + 1);
        u8c_1.addByte(c3);
        u8c_2.addByte(c3);
        u8c_1.addByte(c4);
        u8c_2.addByte(c4);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, u8c_1 == u8c_2);
    CHECK_EQUAL(true, u8c_1 != u8c_2);
};

TEST(u8char, equals_clear_6) {
    string ex = "";
    // 11001101 (starting byte beginning with 110 - only valid as first byte of 2 bytes sequence)
    char c1 = '\xcd';
    // 10101000 (continuation byte beginning with 10 - not valid as first byte)
    char c2 = '\xa8';

    U8char u8c_1;
    U8char u8c_2;

    bool first_comp1;
    bool first_comp2;
    bool sec_comp1;
    bool sec_comp2;

    try {
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
        u8c_1.addByte(c2);
        u8c_2.addByte(c2 + 1);
        first_comp1 = u8c_1 == u8c_2;
        first_comp2 = u8c_1 != u8c_2;
        u8c_1.clear();
        u8c_2.clear();
        u8c_1.addByte(c1);
        u8c_2.addByte(c1);
        u8c_1.addByte(c2);
        u8c_2.addByte(c2);
        sec_comp1 = u8c_1 == u8c_2;
        sec_comp2 = u8c_1 != u8c_2;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, first_comp1);
    CHECK_EQUAL(true, first_comp2);
    CHECK_EQUAL(true, sec_comp1);
    CHECK_EQUAL(false, sec_comp2);
};

TEST(u8char, overload_construct_1) {
    string ex = "";
    const char* input = "€";
    int count;
    bool valid;
    U8char u8c;

    try {
        u8c = U8char(input);
        count = u8c.size();
        valid = u8c.isValid();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(3, count);
    CHECK_EQUAL(true, valid);
};

TEST(u8char, overload_construct_check_complete_get_chars_1) {
    string ex = "";
    const char* input = "€";
    char result[5];
    int count;
    bool is_comp;
    U8char u8c;

    try {
        u8c = U8char(input);
        u8c.getBytes(result, 4);
        count = strlen(result);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(3, count);
    CHECK_EQUAL('\xe2', result[0]);
    CHECK_EQUAL('\x82', result[1]);
    CHECK_EQUAL('\xac', result[2]);
};

TEST(u8char, overload_construct_check_complete_get_chars_2) {
    string ex = "";
    const char* input = "€";
    char result[5];
    int count;
    U8char u8c;

    try {
        u8c = U8char(input);
        u8c.getBytes(result, 2);
        count = strlen(result);
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(2, count);
    CHECK_EQUAL('\xe2', result[0]);
    CHECK_EQUAL('\x82', result[1]);
};

TEST(u8char, less_than_1) {
    string ex = "";
    char c1 = '\x10';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c1);
        res1 = u1 < u2;
        res2 = u2 < u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, less_than_2) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 < u2;
        res2 = u2 < u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, less_than_3) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c3);
        res1 = u1 < u2;
        res2 = u2 < u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, less_than_4) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c3);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 < u2;
        res2 = u2 < u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, less_than_5) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c2);
        u2.addByte(c3);
        res1 = u1 < u2;
        res2 = u2 < u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, less_than_6) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c2);
        u1.addByte(c3);
        u2.addByte(c1);
        res1 = u1 < u2;
        res2 = u2 < u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, less_than_eq_1) {
    string ex = "";
    char c1 = '\x10';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c1);
        res1 = u1 <= u2;
        res2 = u2 <= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, less_than_eq_2) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 <= u2;
        res2 = u2 <= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, less_than_eq_3) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c3);
        res1 = u1 <= u2;
        res2 = u2 <= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, less_than_eq_4) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c3);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 <= u2;
        res2 = u2 <= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, less_than_eq_5) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c2);
        u2.addByte(c3);
        res1 = u1 <= u2;
        res2 = u2 <= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, less_than_eq_6) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c2);
        u1.addByte(c3);
        u2.addByte(c1);
        res1 = u1 <= u2;
        res2 = u2 <= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, greater_than_1) {
    string ex = "";
    char c1 = '\x10';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c1);
        res1 = u1 > u2;
        res2 = u2 > u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, greater_than_2) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 > u2;
        res2 = u2 > u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, greater_than_3) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c3);
        res1 = u1 > u2;
        res2 = u2 > u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, greater_than_4) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c3);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 > u2;
        res2 = u2 > u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, greater_than_5) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c2);
        u2.addByte(c3);
        res1 = u1 > u2;
        res2 = u2 > u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, greater_than_6) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c2);
        u1.addByte(c3);
        u2.addByte(c1);
        res1 = u1 > u2;
        res2 = u2 > u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, greater_than_eq_1) {
    string ex = "";
    char c1 = '\x10';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c1);
        res1 = u1 >= u2;
        res2 = u2 >= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, greater_than_eq_2) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 >= u2;
        res2 = u2 >= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, greater_than_eq_3) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u2.addByte(c1);
        u2.addByte(c3);
        res1 = u1 >= u2;
        res2 = u2 >= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, greater_than_eq_4) {
    string ex = "";
    char c1 = '\xd0';
    char c2 = '\x90';
    char c3 = '\x91';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u1.addByte(c3);
        u2.addByte(c1);
        u2.addByte(c2);
        res1 = u1 >= u2;
        res2 = u2 >= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, greater_than_eq_5) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c1);
        u2.addByte(c2);
        u2.addByte(c3);
        res1 = u1 >= u2;
        res2 = u2 >= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(true, res2);
};

TEST(u8char, greater_than_eq_6) {
    string ex = "";
    char c1 = '\x10';
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    U8char u1;
    U8char u2;
    try {
        u1.addByte(c2);
        u1.addByte(c3);
        u2.addByte(c1);
        res1 = u1 >= u2;
        res2 = u2 >= u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(true, res1);
    CHECK_EQUAL(false, res2);
};

TEST(u8char, to_bool) {
    string ex = "";
    char c2 = '\xd0';
    char c3 = '\x90';
    bool res1;
    bool res2;
    bool res3;
    U8char u1;
    try {
        res1 = u1;
        u1.addByte(c2);
        res2 = u1;
        u1.addByte(c3);
        res3 = u1;
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL(false, res1);
    CHECK_EQUAL(false, res2);
    CHECK_EQUAL(true, res3);
};

TEST(u8char, get_string) {
    string ex = "";
    char c1 = '\xe2';
    char c2 = '\x82';
    char c3 = '\xac';
    U8char u1;
    string res;
    try {
        u1.addByte(c1);
        u1.addByte(c2);
        u1.addByte(c3);
        res = u1.getString();
    } catch (const exception &e) {
        ex = e.what();
    }
    CHECK_EQUAL("", ex);
    CHECK_EQUAL("€", res);
};