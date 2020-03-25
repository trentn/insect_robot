# https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER $ENV{HOME}/x-tools/armv6-rpi-linux-gnueabi/bin/armv6-rpi-linux-gnueabi-gcc)

set(CMAKE_FIND_ROOT_PATH $ENV{HOME}/x-tools/armv6-rpi-linux-gnueabi)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)