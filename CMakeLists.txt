cmake_minimum_required(VERSION 3.5)
project(FileSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp tomFile.h fileSystem.h util.h user.h)
add_executable(FileSystem ${SOURCE_FILES})