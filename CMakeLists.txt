cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(webcli)

find_library(LIBMICROHTTPD NAMES microhttpd libmicrohttpd PATHS /usr/lib /usr/local/lib)
include_directories( ${LIBMICROHTTPD_INCLUDE_DIRECTORIES} )
link_directories( ${LIBMICROHTTPD} )            

add_executable(webcli src/main.cpp src/webcli.cpp src/command.cpp)
target_link_libraries(webcli ${LIBMICROHTTPD})  
