# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\job_install\cl_mymechine\cl\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\job_install\cl_mymechine\cl\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\myModule\moduleLearn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\myModule\moduleLearn\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/atomic_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/atomic_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/atomic_test.dir/flags.make

CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.obj: CMakeFiles/atomic_test.dir/flags.make
CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.obj: ../mutiThreadProgramming/atomic_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\myModule\moduleLearn\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.obj"
	D:\job_install\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\atomic_test.dir\mutiThreadProgramming\atomic_test.cpp.obj -c E:\myModule\moduleLearn\mutiThreadProgramming\atomic_test.cpp

CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.i"
	D:\job_install\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\myModule\moduleLearn\mutiThreadProgramming\atomic_test.cpp > CMakeFiles\atomic_test.dir\mutiThreadProgramming\atomic_test.cpp.i

CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.s"
	D:\job_install\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\myModule\moduleLearn\mutiThreadProgramming\atomic_test.cpp -o CMakeFiles\atomic_test.dir\mutiThreadProgramming\atomic_test.cpp.s

# Object files for target atomic_test
atomic_test_OBJECTS = \
"CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.obj"

# External object files for target atomic_test
atomic_test_EXTERNAL_OBJECTS =

atomic_test.exe: CMakeFiles/atomic_test.dir/mutiThreadProgramming/atomic_test.cpp.obj
atomic_test.exe: CMakeFiles/atomic_test.dir/build.make
atomic_test.exe: CMakeFiles/atomic_test.dir/linklibs.rsp
atomic_test.exe: CMakeFiles/atomic_test.dir/objects1.rsp
atomic_test.exe: CMakeFiles/atomic_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\myModule\moduleLearn\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable atomic_test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\atomic_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/atomic_test.dir/build: atomic_test.exe

.PHONY : CMakeFiles/atomic_test.dir/build

CMakeFiles/atomic_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\atomic_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/atomic_test.dir/clean

CMakeFiles/atomic_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\myModule\moduleLearn E:\myModule\moduleLearn E:\myModule\moduleLearn\cmake-build-debug E:\myModule\moduleLearn\cmake-build-debug E:\myModule\moduleLearn\cmake-build-debug\CMakeFiles\atomic_test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/atomic_test.dir/depend

