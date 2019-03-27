# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Linux)

# the name of the C and CXX compilers to use
SET(CMAKE_C_COMPILER x86_64-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER x86_64-linux-gnu-g++)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH /usr/x86_64-linux-gnu)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

