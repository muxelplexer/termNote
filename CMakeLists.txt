cmake_minimum_required(VERSION 3.24)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/ext/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

project(termNote
   VERSION 2.0.0
)

add_subdirectory(notiz)
add_subdirectory(termNote)

find_package(Catch2 CONFIG)
enable_testing()
if (Catch2_FOUND)
   add_executable(termNote-test 
      test/main.cpp
   )
   target_link_libraries(termNote-test PRIVATE notiz Catch2::Catch2)
   add_test(main ${CMAKE_BINARY_DIR}/termNote-test)
endif()

