cmake_minimum_required(VERSION 3.6)
project(termNote)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_executable(termNote ${SOURCES})
target_link_libraries(${PROJECT_NAME} stdc++fs)
target_link_libraries(${PROJECT_NAME} config++)

install(TARGETS termNote DESTINATION bin)
