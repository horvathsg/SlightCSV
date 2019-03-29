# SlightCSV - simple, lightweight CSV parser library written in C++
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

# CppUTest paths
set(CPPUTEST_INC_DIR /usr/include/CppUTest)
set(CPPUTEST_LIB_DIR /usr/lib/x86_64-linux-gnu)
set(CPPUTEST_LIBS CppUTest CppUTestExt)

# slightcsv_test build
include_directories(${CPPUTEST_INC_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib ${CPPUTEST_LIB_DIR})
add_executable(slightcsv_test main.cpp test_slightcsv.cpp)
target_link_libraries(slightcsv_test PRIVATE slightcsv ${CPPUTEST_LIBS})
target_include_directories(slightcsv_test PUBLIC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET slightcsv_test COMMAND ./slightcsv_test POST_BUILD)

# slightmatrix_test build
include_directories(${CPPUTEST_INC_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib ${CPPUTEST_LIB_DIR})
add_executable(slightmatrix_test main.cpp test_slightmatrix.cpp)
target_link_libraries(slightmatrix_test PRIVATE slightcsv ${CPPUTEST_LIBS})
target_include_directories(slightmatrix_test PUBLIC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET slightmatrix_test COMMAND ./slightmatrix_test POST_BUILD)

# slightrow_test build
include_directories(${CPPUTEST_INC_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib ${CPPUTEST_LIB_DIR})
add_executable(slightrow_test main.cpp test_slightrow.cpp)
target_link_libraries(slightrow_test PRIVATE slightcsv ${CPPUTEST_LIBS})
target_include_directories(slightrow_test PUBLIC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET slightrow_test COMMAND ./slightrow_test POST_BUILD)

# u8char_test build
include_directories(${CPPUTEST_INC_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib ${CPPUTEST_LIB_DIR})
add_executable(u8char_test main.cpp test_u8char.cpp)
target_link_libraries(u8char_test PRIVATE slightcsv ${CPPUTEST_LIBS})
target_include_directories(u8char_test PUBLIC ${CMAKE_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET u8char_test COMMAND ./u8char_test POST_BUILD)

# slightcsv code coverage report
set(OBJECT_DIR ${CMAKE_SOURCE_DIR}/build/src/CMakeFiles/slightcsv.dir)
add_custom_target(codecov
    COMMAND mkdir -p codecov
    WORKING_DIRECTORY ${OBJECT_DIR}
)
add_custom_command(TARGET codecov
    # COMMAND gcov slightcsv.cpp.cpp -o .
    COMMAND lcov -c --directory . --output-file codecov/codecov.info
    COMMAND genhtml codecov/codecov.info --output-directory codecov
    WORKING_DIRECTORY ${OBJECT_DIR}
)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${OBJECT_DIR}/codecov)