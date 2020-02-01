cmake_minimum_required(VERSION 3.10)

project(Insect_Robot_MK2
    VERSION 0.1
    DESCRIPTION "Code for the MK2 build of the Insect Robot"
    LANGUAGES C)

set(CMAKE_INSTALL_PREFIX install)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(src)


