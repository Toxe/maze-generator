cmake_minimum_required(VERSION 3.14)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project("Maze Generator" LANGUAGES CXX)

# adjust or override some CMake defaults
include(cmake/OverrideCMakeDefaults.cmake)

# default compiler options and warnings
include(cmake/DefaultCompilerOptionsAndWarnings.cmake)

# static analyzers
include(cmake/StaticAnalyzers.cmake)

# sanitizers
include(cmake/Sanitizers.cmake)

find_package(clipp CONFIG REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 9)
        find_library(Filesystem_LIBRARY "c++fs")
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

add_executable(maze_generator maze_generator.cpp)
target_compile_features(maze_generator PUBLIC cxx_std_17)
set_target_properties(maze_generator PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(maze_generator PRIVATE clipp::clipp)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(maze_generator PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast -fcolor-diagnostics)
    target_link_libraries(maze_generator PRIVATE "${Filesystem_LIBRARY}")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(maze_generator PRIVATE /W4)
endif()
