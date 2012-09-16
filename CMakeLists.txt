cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(webcli)

add_executable(webcli src/main.cpp src/webcli.cpp src/command.cpp)