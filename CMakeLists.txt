cmake_minimum_required(VERSION 3.15)
project(Project7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project7
        Customer.h
        CustomerDB.cpp
        CustomerDB.h
        main.cpp
        Makefile
        Project7.cpp
        UTString.h)
