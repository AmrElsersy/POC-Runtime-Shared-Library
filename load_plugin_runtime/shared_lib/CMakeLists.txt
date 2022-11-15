cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(SHARED_LIBRARY)


set(SHARED_LIBRARY_TARGET shared_lib)
set(SHARED_LIBRARY_SOURCES shared_lib.cpp)

# add library = make object files (library.o(linux)/library.obj(windows)) then arcive it to static library.a(linux)/library.lib(windows) file
# library(.a | .lib) is a collection of many object files
# https://stackoverflow.com/questions/21140021/why-are-c-obj-files-important
# specify the target name of that library and type of it(static.lib, shared.dll)(windows names)
add_library(${SHARED_LIBRARY_TARGET} SHARED ${SHARED_LIBRARY_SOURCES})
# add_library(${SHARED_LIBRARY_TARGET} SHARED ${SHARED_LIBRARY_SOURCES})

target_include_directories(
    ${SHARED_LIBRARY_TARGET} PUBLIC
    . # same as C:/IQT/POC, which is path that contains the headers of the library
)

execute_process(COMMAND echo "library CMakeLists ends with target name: ${SHARED_LIBRARY_TARGET}")


# Test linking our library to an executable
# set(TEST_EXE_TARGET main_shared_lib)
# add_executable(${TEST_EXE_TARGET} main.cpp)

# target_link_libraries(
#     ${TEST_EXE_TARGET} PUBLIC
#     ${SHARED_LIBRARY_TARGET}
#     # C:/IQT/POC/shared_lib/lib/libshared_lib.dll
# )
