cmake_minimum_required(VERSION 3.12.1)
project(termNote)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_executable(termNote ${SOURCES})
