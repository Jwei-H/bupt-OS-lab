cmake_minimum_required(VERSION 3.27)
project(OSLab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(OSLab2 main.cpp
        Banker.cpp
        Banker.h
        SharedMomery.h
        SharedMomery.cpp
        MessageQueue.h
        Process.h
        Process.cpp
        MessageQueue.cpp
)
