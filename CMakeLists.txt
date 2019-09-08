cmake_minimum_required(VERSION 3.12)

project(practical-geometry-processing
    LANGUAGES CXX
    VERSION 0.1.0
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

add_subdirectory(external)
add_subdirectory(use_openmesh)
