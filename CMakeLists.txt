cmake_minimum_required(VERSION 3.27)
project(bupt_OS_lab)

set(CMAKE_CXX_STANDARD 14)

add_executable(bupt_OS_lab
        lab6/main.cpp
        lab6/readwrite.h
        lab6/createFile.h
        lab6/viewMod.h
        lab6/updateMod.h
        lab6/base.h)
