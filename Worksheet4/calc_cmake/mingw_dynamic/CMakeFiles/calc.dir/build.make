# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\mingw_dynamic

# Include any dependencies generated for this target.
include CMakeFiles/calc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/calc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/calc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/calc.dir/flags.make

CMakeFiles/calc.dir/calc.cpp.obj: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/calc.cpp.obj: ../calc.cpp
CMakeFiles/calc.dir/calc.cpp.obj: CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\mingw_dynamic\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/calc.dir/calc.cpp.obj"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/calc.dir/calc.cpp.obj -MF CMakeFiles\calc.dir\calc.cpp.obj.d -o CMakeFiles\calc.dir\calc.cpp.obj -c C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\calc.cpp

CMakeFiles/calc.dir/calc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/calc.cpp.i"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\calc.cpp > CMakeFiles\calc.dir\calc.cpp.i

CMakeFiles/calc.dir/calc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/calc.cpp.s"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\calc.cpp -o CMakeFiles\calc.dir\calc.cpp.s

# Object files for target calc
calc_OBJECTS = \
"CMakeFiles/calc.dir/calc.cpp.obj"

# External object files for target calc
calc_EXTERNAL_OBJECTS =

calc.exe: CMakeFiles/calc.dir/calc.cpp.obj
calc.exe: CMakeFiles/calc.dir/build.make
calc.exe: libmaths.dll.a
calc.exe: CMakeFiles/calc.dir/linklibs.rsp
calc.exe: CMakeFiles/calc.dir/objects1.rsp
calc.exe: CMakeFiles/calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\mingw_dynamic\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable calc.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\calc.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/calc.dir/build: calc.exe
.PHONY : CMakeFiles/calc.dir/build

CMakeFiles/calc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\calc.dir\cmake_clean.cmake
.PHONY : CMakeFiles/calc.dir/clean

CMakeFiles/calc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\mingw_dynamic C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\mingw_dynamic C:\Users\WALLE\2021_20234390\Worksheet4\calc_cmake\mingw_dynamic\CMakeFiles\calc.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/calc.dir/depend

