# SlightCSV - simple, lightweight CSV parser library
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

set(CPPUTEST_INC_DIR /usr/include/CppUTest)
set(CPPUTEST_LIB_DIR /usr/lib/x86_64-linux-gnu)
set(CPPUTEST_LIBS CppUTest CppUTestExt)

include_directories(${CPPUTEST_INC_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib ${CPPUTEST_LIB_DIR})
add_executable(slightcsv_test main.cpp test.cpp)
target_link_libraries(slightcsv_test PRIVATE slightcsv ${CPPUTEST_LIBS})
target_include_directories(slightcsv_test PUBLIC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET slightcsv_test COMMAND ./slightcsv_test POST_BUILD)