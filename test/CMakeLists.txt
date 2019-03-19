# SlightCSV - a simple and lightweight CSV parser library
# Copyright (C) 2018 Simon Horvath <horvathsg@gmail.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

project(slightcsv_test_prog)

if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

include_directories(/usr/include/CppUTest)
link_directories(/usr/lib/x86_64-linux-gnu)

link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(slightcsv_test main.cpp test.cpp)
target_link_libraries(slightcsv_test PRIVATE slightcsv CppUTest CppUTestExt)
target_include_directories(slightcsv_test PUBLIC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET slightcsv_test COMMAND ./slightcsv_test POST_BUILD)