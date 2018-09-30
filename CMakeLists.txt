cmake_minimum_required(VERSION 3.12)
project(parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(parser
        main.cpp source/parser.cpp header/parser.hpp header/parser.hpp source/parser.cpp header/debug.hpp header/definitions.hpp)
