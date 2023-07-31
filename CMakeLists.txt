cmake_minimum_required(VERSION 3.24)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/ext/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

project(termNote
   VERSION 2.0.0
)

set(WITH_TESTS CACHE BOOL FALSE)

add_subdirectory(notiz)
add_subdirectory(termNote)
add_subdirectory(noted)

if(WITH_TESTS)
   find_package(Catch2 CONFIG)
   enable_testing()
   if (Catch2_FOUND)
      add_executable(termNote-test 
         test/backend.cpp
      )
      target_compile_features(termNote-test PRIVATE cxx_std_23)
      target_link_libraries(termNote-test PRIVATE notiz Catch2::Catch2WithMain)
      add_test("Backend Tests" ${CMAKE_BINARY_DIR}/termNote-test)
   endif()
endif()

