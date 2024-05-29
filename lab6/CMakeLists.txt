cmake_minimum_required(VERSION 3.27)
project(bupt_OS_lab/lab6)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        main.cpp
        readwrite.h
        createFile.h
        viewMod.h
        updateMod.h
        base.h
        encryption.h
        encryption.cpp
)
