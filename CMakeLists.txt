cmake_minimum_required(VERSION 3.17)
project(Final_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_executable(task-1 Task1.cpp)
add_executable(task-2 Task2.cpp)
add_executable(task-3 Task3.cpp)
add_executable(task-4 Task4.cpp)