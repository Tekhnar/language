# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/texnar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.6817.32/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/texnar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.6817.32/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/texnar/CLionProjects/language/middle_end

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/texnar/CLionProjects/language/middle_end/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/middle_end.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/middle_end.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/middle_end.dir/flags.make

CMakeFiles/middle_end.dir/main.cpp.o: CMakeFiles/middle_end.dir/flags.make
CMakeFiles/middle_end.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/texnar/CLionProjects/language/middle_end/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/middle_end.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/middle_end.dir/main.cpp.o -c /home/texnar/CLionProjects/language/middle_end/main.cpp

CMakeFiles/middle_end.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/middle_end.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/texnar/CLionProjects/language/middle_end/main.cpp > CMakeFiles/middle_end.dir/main.cpp.i

CMakeFiles/middle_end.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/middle_end.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/texnar/CLionProjects/language/middle_end/main.cpp -o CMakeFiles/middle_end.dir/main.cpp.s

CMakeFiles/middle_end.dir/libraries/my_stack.cpp.o: CMakeFiles/middle_end.dir/flags.make
CMakeFiles/middle_end.dir/libraries/my_stack.cpp.o: ../libraries/my_stack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/texnar/CLionProjects/language/middle_end/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/middle_end.dir/libraries/my_stack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/middle_end.dir/libraries/my_stack.cpp.o -c /home/texnar/CLionProjects/language/middle_end/libraries/my_stack.cpp

CMakeFiles/middle_end.dir/libraries/my_stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/middle_end.dir/libraries/my_stack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/texnar/CLionProjects/language/middle_end/libraries/my_stack.cpp > CMakeFiles/middle_end.dir/libraries/my_stack.cpp.i

CMakeFiles/middle_end.dir/libraries/my_stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/middle_end.dir/libraries/my_stack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/texnar/CLionProjects/language/middle_end/libraries/my_stack.cpp -o CMakeFiles/middle_end.dir/libraries/my_stack.cpp.s

CMakeFiles/middle_end.dir/libraries/MyTree.cpp.o: CMakeFiles/middle_end.dir/flags.make
CMakeFiles/middle_end.dir/libraries/MyTree.cpp.o: ../libraries/MyTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/texnar/CLionProjects/language/middle_end/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/middle_end.dir/libraries/MyTree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/middle_end.dir/libraries/MyTree.cpp.o -c /home/texnar/CLionProjects/language/middle_end/libraries/MyTree.cpp

CMakeFiles/middle_end.dir/libraries/MyTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/middle_end.dir/libraries/MyTree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/texnar/CLionProjects/language/middle_end/libraries/MyTree.cpp > CMakeFiles/middle_end.dir/libraries/MyTree.cpp.i

CMakeFiles/middle_end.dir/libraries/MyTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/middle_end.dir/libraries/MyTree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/texnar/CLionProjects/language/middle_end/libraries/MyTree.cpp -o CMakeFiles/middle_end.dir/libraries/MyTree.cpp.s

# Object files for target middle_end
middle_end_OBJECTS = \
"CMakeFiles/middle_end.dir/main.cpp.o" \
"CMakeFiles/middle_end.dir/libraries/my_stack.cpp.o" \
"CMakeFiles/middle_end.dir/libraries/MyTree.cpp.o"

# External object files for target middle_end
middle_end_EXTERNAL_OBJECTS =

middle_end: CMakeFiles/middle_end.dir/main.cpp.o
middle_end: CMakeFiles/middle_end.dir/libraries/my_stack.cpp.o
middle_end: CMakeFiles/middle_end.dir/libraries/MyTree.cpp.o
middle_end: CMakeFiles/middle_end.dir/build.make
middle_end: CMakeFiles/middle_end.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/texnar/CLionProjects/language/middle_end/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable middle_end"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/middle_end.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/middle_end.dir/build: middle_end

.PHONY : CMakeFiles/middle_end.dir/build

CMakeFiles/middle_end.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/middle_end.dir/cmake_clean.cmake
.PHONY : CMakeFiles/middle_end.dir/clean

CMakeFiles/middle_end.dir/depend:
	cd /home/texnar/CLionProjects/language/middle_end/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/texnar/CLionProjects/language/middle_end /home/texnar/CLionProjects/language/middle_end /home/texnar/CLionProjects/language/middle_end/cmake-build-debug /home/texnar/CLionProjects/language/middle_end/cmake-build-debug /home/texnar/CLionProjects/language/middle_end/cmake-build-debug/CMakeFiles/middle_end.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/middle_end.dir/depend

