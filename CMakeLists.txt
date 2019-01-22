cmake_minimum_required(VERSION 3.6)
project(termNote)

include_directories(include)

find_package(PkgConfig)
pkg_check_modules(LIBNOTIFY QUIET libnotify)

set(COMMON "src/note.cpp")

include_directories(${LIBNOTIFY_INCLUDE_DIRS})
link_directories(${LIBNOTIFY_LIBRARY_DIRS})
ADD_DEFINITIONS(${LIBNOTIFY_CFLAGS})

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_executable(termNote src/main.cpp ${COMMON})
add_executable(noted src/noted.cpp ${COMMON})
target_link_libraries(${PROJECT_NAME} stdc++fs)
target_link_libraries(noted stdc++fs ${LIBNOTIFY_LIBRARIES})


install(TARGETS termNote noted DESTINATION bin)

