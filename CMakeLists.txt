cmake_minimum_required(VERSION 3.22)
project(signs)

set(CMAKE_CXX_STANDARD 20)

include(conan_toolchain.cmake)
include_directories("include")

find_package(pybind11 REQUIRED)

pybind11_add_module(signs src/pybind_sign.cpp
        src/sign.cpp)

target_include_directories(signs PRIVATE ${pybind11_INCLUDE_DIRS})

set_target_properties(signs PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}"
)
