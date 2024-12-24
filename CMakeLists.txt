cmake_minimum_required(VERSION 3.22.1)
project(doodlejump)

set(CMAKE_CXX_STANDARD 17)

add_executable(doodlejump src/main.cpp)
FIND_PACKAGE(SFML 2.5.1 COMPONENTS graphics window system)