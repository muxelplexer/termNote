if (WITH_TESTS)
    add_library(notiz SHARED
        src/file_backend.cpp
        src/notebook.cpp
        src/note.cpp
    )
else()
    add_library(notiz STATIC
        src/file_backend.cpp
        src/notebook.cpp
        src/note.cpp
    )

endif()

target_include_directories(notiz PUBLIC inc/)
target_compile_features(notiz PRIVATE cxx_std_23)
