# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/joris_a/rendu/cpp/cpp_indie_studio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joris_a/rendu/cpp/cpp_indie_studio

# Include any dependencies generated for this target.
include CMakeFiles/cpp_indie_studio.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpp_indie_studio.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpp_indie_studio.dir/flags.make

CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o: CMakeFiles/cpp_indie_studio.dir/flags.make
CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joris_a/rendu/cpp/cpp_indie_studio/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o -c /home/joris_a/rendu/cpp/cpp_indie_studio/src/main.cpp

CMakeFiles/cpp_indie_studio.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_indie_studio.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joris_a/rendu/cpp/cpp_indie_studio/src/main.cpp > CMakeFiles/cpp_indie_studio.dir/src/main.cpp.i

CMakeFiles/cpp_indie_studio.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_indie_studio.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joris_a/rendu/cpp/cpp_indie_studio/src/main.cpp -o CMakeFiles/cpp_indie_studio.dir/src/main.cpp.s

CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.requires

CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.provides: CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/cpp_indie_studio.dir/build.make CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.provides

CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.provides.build: CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o


# Object files for target cpp_indie_studio
cpp_indie_studio_OBJECTS = \
"CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o"

# External object files for target cpp_indie_studio
cpp_indie_studio_EXTERNAL_OBJECTS =

cpp_indie_studio: CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o
cpp_indie_studio: CMakeFiles/cpp_indie_studio.dir/build.make
cpp_indie_studio: CMakeFiles/cpp_indie_studio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joris_a/rendu/cpp/cpp_indie_studio/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpp_indie_studio"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpp_indie_studio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpp_indie_studio.dir/build: cpp_indie_studio

.PHONY : CMakeFiles/cpp_indie_studio.dir/build

CMakeFiles/cpp_indie_studio.dir/requires: CMakeFiles/cpp_indie_studio.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/cpp_indie_studio.dir/requires

CMakeFiles/cpp_indie_studio.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpp_indie_studio.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpp_indie_studio.dir/clean

CMakeFiles/cpp_indie_studio.dir/depend:
	cd /home/joris_a/rendu/cpp/cpp_indie_studio && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joris_a/rendu/cpp/cpp_indie_studio /home/joris_a/rendu/cpp/cpp_indie_studio /home/joris_a/rendu/cpp/cpp_indie_studio /home/joris_a/rendu/cpp/cpp_indie_studio /home/joris_a/rendu/cpp/cpp_indie_studio/CMakeFiles/cpp_indie_studio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpp_indie_studio.dir/depend

