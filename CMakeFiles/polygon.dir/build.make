# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/george/Desktop/project-algo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/george/Desktop/project-algo

# Include any dependencies generated for this target.
include CMakeFiles/polygon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/polygon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/polygon.dir/flags.make

CMakeFiles/polygon.dir/main.cpp.o: CMakeFiles/polygon.dir/flags.make
CMakeFiles/polygon.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/george/Desktop/project-algo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/polygon.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/polygon.dir/main.cpp.o -c /home/george/Desktop/project-algo/main.cpp

CMakeFiles/polygon.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/polygon.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/george/Desktop/project-algo/main.cpp > CMakeFiles/polygon.dir/main.cpp.i

CMakeFiles/polygon.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/polygon.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/george/Desktop/project-algo/main.cpp -o CMakeFiles/polygon.dir/main.cpp.s

# Object files for target polygon
polygon_OBJECTS = \
"CMakeFiles/polygon.dir/main.cpp.o"

# External object files for target polygon
polygon_EXTERNAL_OBJECTS =

polygon: CMakeFiles/polygon.dir/main.cpp.o
polygon: CMakeFiles/polygon.dir/build.make
polygon: includes/libalgorithms.a
polygon: /usr/lib/x86_64-linux-gnu/libgmpxx.so
polygon: /usr/lib/x86_64-linux-gnu/libmpfr.so
polygon: /usr/lib/x86_64-linux-gnu/libgmp.so
polygon: CMakeFiles/polygon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/george/Desktop/project-algo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable polygon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/polygon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/polygon.dir/build: polygon

.PHONY : CMakeFiles/polygon.dir/build

CMakeFiles/polygon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/polygon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/polygon.dir/clean

CMakeFiles/polygon.dir/depend:
	cd /home/george/Desktop/project-algo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/george/Desktop/project-algo /home/george/Desktop/project-algo /home/george/Desktop/project-algo /home/george/Desktop/project-algo /home/george/Desktop/project-algo/CMakeFiles/polygon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/polygon.dir/depend
