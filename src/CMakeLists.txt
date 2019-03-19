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

project(slightcsv_prog)

add_library(slightcsv SHARED slightcsv.hpp slightcsvprivate.hpp slightcsv.cpp slightrow.hpp slightrow.cpp slightmatrix.hpp slightmatrix.cpp)
target_include_directories(slightcsv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(slightcsv PROPERTIES PUBLIC_HEADER slightcsv.hpp)
INSTALL(TARGETS slightcsv
LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/inc/slightcsv
)

link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(main main.cpp stopwatch.hpp stopwatch.cpp slightmatrix.hpp slightmatrix.cpp)
target_link_libraries(main PRIVATE slightcsv)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/inc)
INSTALL(TARGETS main
RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
)

#set(CMAKE_BUILD_TYPE Debug)
#link_directories(${CMAKE_SOURCE_DIR}/lib)
#add_executable(main main.cpp stopwatch.hpp stopwatch.cpp slightcsv.hpp slightcsvprivate.hpp slightcsv.cpp slightrow.hpp slightrow.cpp)
#target_link_libraries(main PRIVATE slightcsv)
#target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/inc)
#INSTALL(TARGETS main
#RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
#)