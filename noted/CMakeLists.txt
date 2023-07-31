find_package(argparse CONFIG REQUIRED)

add_executable(noted
    src/main.cpp
)

target_link_libraries(noted PRIVATE notiz argparse::argparse)
target_include_directories(noted PRIVATE inc/)
target_compile_features(noted PRIVATE cxx_std_23)
