cmake_minimum_required(VERSION 3.27)
project(OSLab3)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(OSLab3 main.cpp
        task.h
        ringQueue.cpp
        ringQueue.h)
target_link_libraries(OSLab3  Threads::Threads)