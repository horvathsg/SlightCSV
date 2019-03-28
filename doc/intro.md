 # Introduction

 SlightCSV is a CSV parser library written in C++. Its main purpose is to facilitate the programmatic processing of
 CSV files.

 ## Features

 * Customizable delimiter and escape characters.
 * Flexible character manipulation capabilities (stripping, replacement).
 * Automatic handling of macOS, Linux and Windows line endings.
 * Query methods for getting cell, row and column data with automatic type conversion capabilities.
 * Able to load large files (> 1 GB) in reasonable time.
 * Custom exception classes inheriting from std::exception.

 ## In addition

 * Detailed documentation (Doxygen).
 * Automated unit and integration testing (CppUTest, gcov, lcov).
 * Pre-compiled binaries for multiple platforms.
 * Example code.

 # Getting started

 ## Operation

 After constructing the SlightCSV object (and before loading data from CSV file), parameters need to be set up through SlightCSV's setter methods. File loading and processing doesn't happen until triggering data loading through the API. If a mandatory parameter is not set, an exception will be thrown. After loading finished, data is accessible through data getter methods. Data may be unloaded later and the object can be resetted to its initial state. However, this is not mandatory as the library is only using dynamic memory with appropriate release technique (RAII).

 ## Dependencies

 SlightCSV has no external dependencies. However, the following tools are used in the build pipeline to support build management, code quality and documentation.

 * CMake.
 * CppUTest.
 * gcov, lcov.
 * Doxygen.

 It is recommended to install those missing before proceeding.

## Platform

  Binaries for 32/64 bit Linux/Windows are supplied in the dist directory. At the present time, the development platform is Linux. While it is possible to build and use the library on other platforms, various stages of the build pipeline might fail because of missing headers and/or libraries (namely automated testing, documentation generation and code coverage report generation). Those issues may be resolved by building and/or installing missing components.

 ## Project structure

 The structure inside the project root directory is as follows.

 * bin: demo application output directory.
 * build: build directory.
 * dist: distribution directory.
 * doc: Doxygen configuration and output directory.
 * inc: public header output directory.
 * lib: shared library output directory.
 * platform: platform toolchains directory.
 * src: library and demo application source directory.
 * test: unit and integration tests directory.

 In order to use the pre-built shared library, you need to include the public header (slightcsv.hpp) from inc and the 
 library (libslightcsv.so or libslightcsv.dll on Windows) from lib.

 ## Usage

 ### Using the supplied binaries

 Binaries for the following platforms are located in the dist directory:
 
  * Linux 32 bit x86 (Linux32)
  * Linux 64 bit x86-64 (Linux64)
  * Windows 32 bit x86 (Windows32)
  * Windows 64 bit x86-64 (Windows64)

 Public header and documentation are also available in the dist folder. Using the library is a matter of including the public header in your source file(s) and linking your application to the appropriate platform binary.

 ### Building from source

 For building the library from source:

 * Have dependencies installed and available in your environment.
 * Edit CMake config file (CMakeLists.txt) in test and set CppUTest path variables.
 * Run "cmake .. -DCMAKE_BUILD_TYPE=DEBUG" or "cmake .. -DCMAKE_BUILD_TYPE=RELEASE" in build directory for CMake to generate build configuration files. In DEBUG, the library is built with debug symbols included while in RELEASE, those are not present (RELEASE builds use compiler optimization as well).
 * Run "make clean" in build directory to cleanup.
 * Run "make" in build directory to build all artifacts. After issuing the command, artifacts are built and/or run in the following order: SlightCSV build, tests build, tests run, demo build. At the end of each stage, output files are placed in their respective target directories (shared library file in lib, public header file in inc/slightcsv and executable demo application in bin).
 * Install sections are commented out in CMake's config files. If you would like to use "make install", uncomment those rows and set target paths according to your preference.
 * Documentation may be generated by issuing command "make docs". Documentation is generated into the doc folder.
 * Code coverage report may be generated by issuing command "make codecov". Report index file can be found at: build/src/CMakeFiles/slightcsv.dir/codecov/index.html.

### Code example

The following simple example provides an overview of the usage of the library. For additional methods and parameters, please refer to the Doxygen documentation located in the distribution's doc folder.

```cpp
#include "slightcsv.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::pair;
using std::map;
using utils::SlightCSV;

int main(int argc, char *argv[]) {

    // construct object
    SlightCSV scsv;

    // set filename
    scsv.setFileName("../test/env_data.csv");

    // set delimiter character (semicolon)
    scsv.setSeparator(';');
    
    // set escape character (double quote)
    scsv.setEscape('\"');
    
    // set characters to be stripped (stip spaces and underscores)
    set<char> to_strip;
    to_strip.insert(' ');
    to_strip.insert('_');
    scsv.setStripChars(to_strip);
    
    // set characters to be replaced (replace 'a' with 'b' and 'c' with 'd')
    map<char, char> to_replace;
    pair<char, char> to_replace1('a', 'b');
    pair<char, char> to_replace2('c', 'd');
    to_replace.insert(to_replace1);
    to_replace.insert(to_replace2);
    scsv.setReplaceChars(to_replace);

    // load data
    scsv.loadData();
    
    // output entity counts
    cout << "File contains " << scsv.getColumnCount() << " columns." << endl;
    cout << "File contains " << scsv.getRowCount() << " rows." << endl;
    cout << "Header count: " << scsv.getHeaderCount() << " rows." << endl;

    // output row 501 (at index 500)
    vector<string> row;
    scsv.getRow(row, 500);
    cout << "Row 501 is: " << endl;
    for (vector<string>::iterator it = row.begin(); it != row.end(); ++it) {
        cout << *it << " ";
    }

    // output column 22 (at index 21)
    vector<string> column;
    scsv.getColumn(column, 21);
    cout << "Column 22 is: " << endl;
    for (vector<string>::iterator it = column.begin(); it != column.end(); ++it) {
        cout << *it << endl;
    }

    // reset object to initial state (before reuse, e.g. loading another file)
    scsv.reset();

}
```

# Future development

Features to be implemented in the future:

 * C++11 compliant multithreading for even faster processing.
 * Support for UTF-8 character encoding.
 * Extended transformation and conversion support for rows and columns.

 Ideas, contributions, issues and comments are welcome!