cmake_minimum_required(VERSION 3.6)
project(termNote)

include_directories(include)

find_package(PkgConfig)
pkg_check_modules(LIBNOTIFY QUIET libnotify)

find_package(Catch2)

set(COMMON "src/note.cpp")

# Main executable (termNote)
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_executable(termNote src/main.cpp ${COMMON})
target_link_libraries(${PROJECT_NAME} stdc++fs)
install(TARGETS termNote DESTINATION bin)


# noted
if (LIBNOTIFY_FOUND)
   include_directories(${LIBNOTIFY_INCLUDE_DIRS})
   link_directories(${LIBNOTIFY_LIBRARY_DIRS})
   add_definitions(${LIBNOTIFY_CFLAGS})
   add_executable(noted src/noted.cpp ${COMMON})
   target_link_libraries(noted stdc++fs ${LIBNOTIFY_LIBRARIES})
   install(TARGETS noted DESTINATION bin)
endif()

# unit tests
enable_testing()
if (Catch2_FOUND)
   add_executable(unitTest test/main.cpp ${COMMON})
   target_link_libraries(unitTest stdc++fs Catch2::Catch2)
   add_test(main bin/unitTest)
endif ()


