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

set(CPACK_PACKAGE_NAME "termNote")
set(CPACK_PACKAGE_VENDOR "muxelplexer")
set(CPACK_PACKAGE_CONTACT "muxelplexer <sebastian@muxel.dev>")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/muxelplexer/termnote")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README.md)
set(CPACK_STRIP_FILES TRUE)
set(CPACK_THREADS 0)

install(TARGETS termNote)
include(CPack)
