# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug

# Utility rule file for common_autogen.

# Include the progress variables for this target.
include common/CMakeFiles/common_autogen.dir/progress.make

common/CMakeFiles/common_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target common"
	cd /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug/common && /snap/clion/139/bin/cmake/linux/bin/cmake -E cmake_autogen /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug/common/CMakeFiles/common_autogen.dir/AutogenInfo.json Debug

common_autogen: common/CMakeFiles/common_autogen
common_autogen: common/CMakeFiles/common_autogen.dir/build.make

.PHONY : common_autogen

# Rule to build all files generated by this target.
common/CMakeFiles/common_autogen.dir/build: common_autogen

.PHONY : common/CMakeFiles/common_autogen.dir/build

common/CMakeFiles/common_autogen.dir/clean:
	cd /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug/common && $(CMAKE_COMMAND) -P CMakeFiles/common_autogen.dir/cmake_clean.cmake
.PHONY : common/CMakeFiles/common_autogen.dir/clean

common/CMakeFiles/common_autogen.dir/depend:
	cd /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/common /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug/common /home/juankristal/Desktop/taller/TP_FINAL/Wolfenstein3D/cmake-build-debug/common/CMakeFiles/common_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : common/CMakeFiles/common_autogen.dir/depend

