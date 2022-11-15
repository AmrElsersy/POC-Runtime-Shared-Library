cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(electron_runtime_dll)
add_library(${PROJECT_NAME} SHARED my_dll.cpp)
