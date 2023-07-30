find_package(argparse CONFIG REQUIRED)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/conf/version.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/version.hpp
)
add_executable(termNote
    src/file_backend.cpp
    src/main.cpp
    src/notebook.cpp
)

target_link_libraries(termNote PRIVATE argparse::argparse)
target_include_directories(termNote PRIVATE inc/)
target_compile_features(termNote PRIVATE cxx_std_23)
