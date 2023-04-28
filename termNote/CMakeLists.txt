add_executable(termNote
    src/main.cpp
)

target_include_directories(termNote PRIVATE inc/)
target_compile_features(termNote PRIVATE cxx_std_23)
