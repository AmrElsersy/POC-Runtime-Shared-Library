# Tutorials
# https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/developer_guide/gcc-using-libraries
# https://docencia.ac.upc.edu/FIB/USO/Bibliografia/unix-c-libraries.html

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main_project)

set(MAIN_TARGET main)
set(MAIN_TARGET_SOURCES load_plugin_runtime.cpp)
set(SHARED_LIB_INCLUDE_PATH C:/IQT/POC/shared_lib)

# set the prefix and suffix of libraries names for better search, by default ".dll" dosn't exist in the suffix, so when you run
# find_library, it dosn't find the .dlls, so we need to add it to the suffix, ex: when prefix=lib & suffix=.dll so you can find_library 
# that called shared_lib, and it will be translated in libshared_lib.dll
SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")

add_executable(${MAIN_TARGET} ${MAIN_TARGET_SOURCES})
# ================ 3 Ways to link with the library ======================
# 1- find_library: search for a library(static or shared) in a specific path, and get the library target
find_library(SHARED_LIBRARY_TARGET "libshared_lib.dll" PATHS ${SHARED_LIB_INCLUDE_PATH}/lib DOC "shared_library_description" NO_DEFAULT_PATH REQUIRED)
# ========================================

# 2- import library
# set(SHARED_LIBRARY_TARGET shared_lib) # set variable name
# add_library(${SHARED_LIBRARY_TARGET} SHARED IMPORTED) # import library (IMPORTED)
# set_property(TARGET ${SHARED_LIBRARY_TARGET} PROPERTY # set the location of it
#              IMPORTED_LOCATION "C:/IQT/POC/shared_lib/build/libshared_lib.dll")
# set_property(TARGET ${SHARED_LIBRARY_TARGET} PROPERTY # required by windows!, set the location of its implib
#              IMPORTED_IMPLIB "C:/IQT/POC/shared_lib/build/libshared_lib.dll.a")
# ========================================

message("#### SHARED_LIBRARY_TARGET= ${SHARED_LIBRARY_TARGET}")

target_include_directories(
    ${MAIN_TARGET} PUBLIC
    ${SHARED_LIB_INCLUDE_PATH}
)

target_link_libraries(
    ${MAIN_TARGET} PUBLIC
    ${SHARED_LIBRARY_TARGET}
    # 3- write the full path of the static/shared library
    # "C:/IQT/POC/shared_lib/lib/libshared_lib.dll"
)
message("load_plugin CMakeLists ends with target name: ${MAIN_TARGET}")

# ................ Comments ................
# When linking Windows will look in the same directory as the binary, and then search the directories in your PATH
# There is NO rpath concept on windows, this is supported by only linux
# set(CMAKE_BUILD_RPATH ${SHARED_LIBRARY_TARGET})
# ..........................................
# Loading Shared library requires you to set the LD_LIBRARY_PATH (linux) or PATH (windows) for [[[[runtime-linking]]]]
# This will set the enviroment variable inside the cmake build process only, and NOT from the process where you run the cmake build
# $env:Path=$env:Path + ";" + "C:/IQT/POC/shared_lib/lib" # USELESS !
# ..........................................
