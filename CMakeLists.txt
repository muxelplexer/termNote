cmake_minimum_required(VERSION 3.12.4)
project(termNote)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(termNote ${SOURCES})
