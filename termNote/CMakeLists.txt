add_executable(termNote
    src/file_backend.cpp
    src/main.cpp
    src/notebook.cpp
)

target_include_directories(termNote PRIVATE inc/)
target_compile_features(termNote PRIVATE cxx_std_23)
