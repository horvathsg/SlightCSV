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

project(slightcsv_demo_prog)

#set(CMAKE_BUILD_TYPE Debug)

set(DEMO_SOURCES main.cpp)
#target_include_directories(demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(demo ${DEMO_SOURCES})
link_directories(${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(demo PRIVATE slightcsv)
target_include_directories(demo PUBLIC ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#INSTALL(TARGETS demo
#RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
#)