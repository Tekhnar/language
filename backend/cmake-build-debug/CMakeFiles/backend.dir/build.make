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
CMAKE_SOURCE_DIR = /home/texnar/CLionProjects/language/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/texnar/CLionProjects/language/backend/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/backend.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/backend.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/backend.dir/flags.make

CMakeFiles/backend.dir/main.cpp.o: CMakeFiles/backend.dir/flags.make
CMakeFiles/backend.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/texnar/CLionProjects/language/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/backend.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/backend.dir/main.cpp.o -c /home/texnar/CLionProjects/language/backend/main.cpp

CMakeFiles/backend.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backend.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/texnar/CLionProjects/language/backend/main.cpp > CMakeFiles/backend.dir/main.cpp.i

CMakeFiles/backend.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backend.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/texnar/CLionProjects/language/backend/main.cpp -o CMakeFiles/backend.dir/main.cpp.s

CMakeFiles/backend.dir/libraries/my_stack.cpp.o: CMakeFiles/backend.dir/flags.make
CMakeFiles/backend.dir/libraries/my_stack.cpp.o: ../libraries/my_stack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/texnar/CLionProjects/language/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/backend.dir/libraries/my_stack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/backend.dir/libraries/my_stack.cpp.o -c /home/texnar/CLionProjects/language/backend/libraries/my_stack.cpp

CMakeFiles/backend.dir/libraries/my_stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backend.dir/libraries/my_stack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/texnar/CLionProjects/language/backend/libraries/my_stack.cpp > CMakeFiles/backend.dir/libraries/my_stack.cpp.i

CMakeFiles/backend.dir/libraries/my_stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backend.dir/libraries/my_stack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/texnar/CLionProjects/language/backend/libraries/my_stack.cpp -o CMakeFiles/backend.dir/libraries/my_stack.cpp.s

CMakeFiles/backend.dir/libraries/MyTree.cpp.o: CMakeFiles/backend.dir/flags.make
CMakeFiles/backend.dir/libraries/MyTree.cpp.o: ../libraries/MyTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/texnar/CLionProjects/language/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/backend.dir/libraries/MyTree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/backend.dir/libraries/MyTree.cpp.o -c /home/texnar/CLionProjects/language/backend/libraries/MyTree.cpp

CMakeFiles/backend.dir/libraries/MyTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backend.dir/libraries/MyTree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/texnar/CLionProjects/language/backend/libraries/MyTree.cpp > CMakeFiles/backend.dir/libraries/MyTree.cpp.i

CMakeFiles/backend.dir/libraries/MyTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backend.dir/libraries/MyTree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/texnar/CLionProjects/language/backend/libraries/MyTree.cpp -o CMakeFiles/backend.dir/libraries/MyTree.cpp.s

CMakeFiles/backend.dir/libraries/connect_asm.cpp.o: CMakeFiles/backend.dir/flags.make
CMakeFiles/backend.dir/libraries/connect_asm.cpp.o: ../libraries/connect_asm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/texnar/CLionProjects/language/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/backend.dir/libraries/connect_asm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/backend.dir/libraries/connect_asm.cpp.o -c /home/texnar/CLionProjects/language/backend/libraries/connect_asm.cpp

CMakeFiles/backend.dir/libraries/connect_asm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backend.dir/libraries/connect_asm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/texnar/CLionProjects/language/backend/libraries/connect_asm.cpp > CMakeFiles/backend.dir/libraries/connect_asm.cpp.i

CMakeFiles/backend.dir/libraries/connect_asm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backend.dir/libraries/connect_asm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/texnar/CLionProjects/language/backend/libraries/connect_asm.cpp -o CMakeFiles/backend.dir/libraries/connect_asm.cpp.s

# Object files for target backend
backend_OBJECTS = \
"CMakeFiles/backend.dir/main.cpp.o" \
"CMakeFiles/backend.dir/libraries/my_stack.cpp.o" \
"CMakeFiles/backend.dir/libraries/MyTree.cpp.o" \
"CMakeFiles/backend.dir/libraries/connect_asm.cpp.o"

# External object files for target backend
backend_EXTERNAL_OBJECTS =

backend: CMakeFiles/backend.dir/main.cpp.o
backend: CMakeFiles/backend.dir/libraries/my_stack.cpp.o
backend: CMakeFiles/backend.dir/libraries/MyTree.cpp.o
backend: CMakeFiles/backend.dir/libraries/connect_asm.cpp.o
backend: CMakeFiles/backend.dir/build.make
backend: CMakeFiles/backend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/texnar/CLionProjects/language/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable backend"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/backend.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/backend.dir/build: backend

.PHONY : CMakeFiles/backend.dir/build

CMakeFiles/backend.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/backend.dir/cmake_clean.cmake
.PHONY : CMakeFiles/backend.dir/clean

CMakeFiles/backend.dir/depend:
	cd /home/texnar/CLionProjects/language/backend/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/texnar/CLionProjects/language/backend /home/texnar/CLionProjects/language/backend /home/texnar/CLionProjects/language/backend/cmake-build-debug /home/texnar/CLionProjects/language/backend/cmake-build-debug /home/texnar/CLionProjects/language/backend/cmake-build-debug/CMakeFiles/backend.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/backend.dir/depend
