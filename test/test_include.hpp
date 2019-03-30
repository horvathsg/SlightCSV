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

#ifndef _TEST_INCLUDE_HPP
#define _TEST_INCLUDE_HPP

#include "slightrow.hpp"
#include "slightmatrix.hpp"
#include "slightcsv.hpp"
#include "u8char.hpp"

#include "CppUTest/TestHarness.h"

#include <cstring>
#include <iostream>

using std::string;
using std::vector;
using std::set;
using std::map;
using std::pair;
using std::exception;
using std::cout;
using std::endl;
using utils::SlightRow;
using utils::SlightMatrix;
using utils::SlightCSV;
using utils::U8char;

#endif // _TEST_INCLUDE_HPP