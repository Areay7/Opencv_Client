# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/areay7/QtCode/Qt_Sql/Opencv_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/areay7/QtCode/Qt_Sql/Opencv_test/build

# Utility rule file for Opencv_test_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/Opencv_test_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Opencv_test_autogen.dir/progress.make

CMakeFiles/Opencv_test_autogen: Opencv_test_autogen/timestamp

Opencv_test_autogen/timestamp: /Users/areay7/Qt/6.5.3/macos/./libexec/moc
Opencv_test_autogen/timestamp: /Users/areay7/Qt/6.5.3/macos/./libexec/uic
Opencv_test_autogen/timestamp: CMakeFiles/Opencv_test_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/areay7/QtCode/Qt_Sql/Opencv_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target Opencv_test"
	/Applications/CMake.app/Contents/bin/cmake -E cmake_autogen /Users/areay7/QtCode/Qt_Sql/Opencv_test/build/CMakeFiles/Opencv_test_autogen.dir/AutogenInfo.json ""
	/Applications/CMake.app/Contents/bin/cmake -E touch /Users/areay7/QtCode/Qt_Sql/Opencv_test/build/Opencv_test_autogen/timestamp

Opencv_test_autogen: CMakeFiles/Opencv_test_autogen
Opencv_test_autogen: Opencv_test_autogen/timestamp
Opencv_test_autogen: CMakeFiles/Opencv_test_autogen.dir/build.make
.PHONY : Opencv_test_autogen

# Rule to build all files generated by this target.
CMakeFiles/Opencv_test_autogen.dir/build: Opencv_test_autogen
.PHONY : CMakeFiles/Opencv_test_autogen.dir/build

CMakeFiles/Opencv_test_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Opencv_test_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Opencv_test_autogen.dir/clean

CMakeFiles/Opencv_test_autogen.dir/depend:
	cd /Users/areay7/QtCode/Qt_Sql/Opencv_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/areay7/QtCode/Qt_Sql/Opencv_test /Users/areay7/QtCode/Qt_Sql/Opencv_test /Users/areay7/QtCode/Qt_Sql/Opencv_test/build /Users/areay7/QtCode/Qt_Sql/Opencv_test/build /Users/areay7/QtCode/Qt_Sql/Opencv_test/build/CMakeFiles/Opencv_test_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Opencv_test_autogen.dir/depend

