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

project(slightcsv_lib)

#set(CMAKE_BUILD_TYPE Debug)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(SLIGHTCSV_SOURCES slightcsv.hpp slightcsvprivate.hpp slightcsv.cpp slightrow.hpp slightrow.cpp slightmatrix.hpp slightmatrix.cpp)
add_library(slightcsv SHARED ${SLIGHTCSV_SOURCES})
target_include_directories(slightcsv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(slightcsv PROPERTIES PUBLIC_HEADER slightcsv.hpp)
INSTALL(TARGETS slightcsv
LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/inc/slightcsv
)