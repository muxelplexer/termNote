cmake_minimum_required(VERSION 3.12)
project(termNote)


set(COMMON 
	"src/termNote/NoteManager.cpp"
	"src/termNote/Note.cpp"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(termNote src/main.cpp ${COMMON})
target_include_directories(termNote PRIVATE include)
target_link_libraries(${PROJECT_NAME} stdc++fs)

install(TARGETS termNote DESTINATION bin)
