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

project(slightcsv_lib)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SLIGHTCSV_SOURCES slightcsv.hpp slightcsvprivate.hpp slightcsv.cpp slightrow.hpp slightrow.cpp slightmatrix.hpp slightmatrix.cpp)
add_library(slightcsv SHARED ${SLIGHTCSV_SOURCES})
target_include_directories(slightcsv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(slightcsv PROPERTIES PUBLIC_HEADER slightcsv.hpp)
#target_compile_options(slightcsv PUBLIC -Wall -Wextra)
set_target_properties(slightcsv PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
add_custom_command(TARGET slightcsv
    COMMAND cp src/slightcsv.hpp inc/slightcsv
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Documentation generation
add_custom_target(docs
)
add_custom_command(TARGET docs
    COMMAND doxygen slightcsv
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
)

#INSTALL(TARGETS slightcsv
#LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
#PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/inc/slightcsv
#)