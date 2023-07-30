cmake_minimum_required(VERSION 3.24)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/ext/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

project(termNote
   VERSION 2.0.0
)


add_subdirectory(termNote)
