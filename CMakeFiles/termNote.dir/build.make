# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/terodom/workspace/programming/cpp/termNote

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/terodom/workspace/programming/cpp/termNote

# Include any dependencies generated for this target.
include CMakeFiles/termNote.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/termNote.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/termNote.dir/flags.make

CMakeFiles/termNote.dir/src/main.cpp.o: CMakeFiles/termNote.dir/flags.make
CMakeFiles/termNote.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/terodom/workspace/programming/cpp/termNote/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/termNote.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/termNote.dir/src/main.cpp.o -c /home/terodom/workspace/programming/cpp/termNote/src/main.cpp

CMakeFiles/termNote.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/termNote.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/terodom/workspace/programming/cpp/termNote/src/main.cpp > CMakeFiles/termNote.dir/src/main.cpp.i

CMakeFiles/termNote.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/termNote.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/terodom/workspace/programming/cpp/termNote/src/main.cpp -o CMakeFiles/termNote.dir/src/main.cpp.s

CMakeFiles/termNote.dir/src/note.cpp.o: CMakeFiles/termNote.dir/flags.make
CMakeFiles/termNote.dir/src/note.cpp.o: src/note.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/terodom/workspace/programming/cpp/termNote/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/termNote.dir/src/note.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/termNote.dir/src/note.cpp.o -c /home/terodom/workspace/programming/cpp/termNote/src/note.cpp

CMakeFiles/termNote.dir/src/note.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/termNote.dir/src/note.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/terodom/workspace/programming/cpp/termNote/src/note.cpp > CMakeFiles/termNote.dir/src/note.cpp.i

CMakeFiles/termNote.dir/src/note.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/termNote.dir/src/note.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/terodom/workspace/programming/cpp/termNote/src/note.cpp -o CMakeFiles/termNote.dir/src/note.cpp.s

# Object files for target termNote
termNote_OBJECTS = \
"CMakeFiles/termNote.dir/src/main.cpp.o" \
"CMakeFiles/termNote.dir/src/note.cpp.o"

# External object files for target termNote
termNote_EXTERNAL_OBJECTS =

bin/termNote: CMakeFiles/termNote.dir/src/main.cpp.o
bin/termNote: CMakeFiles/termNote.dir/src/note.cpp.o
bin/termNote: CMakeFiles/termNote.dir/build.make
bin/termNote: CMakeFiles/termNote.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/terodom/workspace/programming/cpp/termNote/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/termNote"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/termNote.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/termNote.dir/build: bin/termNote

.PHONY : CMakeFiles/termNote.dir/build

CMakeFiles/termNote.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/termNote.dir/cmake_clean.cmake
.PHONY : CMakeFiles/termNote.dir/clean

CMakeFiles/termNote.dir/depend:
	cd /home/terodom/workspace/programming/cpp/termNote && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/terodom/workspace/programming/cpp/termNote /home/terodom/workspace/programming/cpp/termNote /home/terodom/workspace/programming/cpp/termNote /home/terodom/workspace/programming/cpp/termNote /home/terodom/workspace/programming/cpp/termNote/CMakeFiles/termNote.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/termNote.dir/depend

