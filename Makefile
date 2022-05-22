# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = D:\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Programming\sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Programming\sylar

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	D:\CMake\bin\cmake-gui.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	D:\CMake\bin\cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Programming\sylar\CMakeFiles D:\Programming\sylar\\CMakeFiles\progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Programming\sylar\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named sylar

# Build rule for target.
sylar: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 sylar
.PHONY : sylar

# fast build rule for target.
sylar/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\sylar.dir\build.make CMakeFiles/sylar.dir/build
.PHONY : sylar/fast

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\test.dir\build.make CMakeFiles/test.dir/build
.PHONY : test/fast

sylar/log.obj: sylar/log.cpp.obj
.PHONY : sylar/log.obj

# target to build an object file
sylar/log.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\sylar.dir\build.make CMakeFiles/sylar.dir/sylar/log.cpp.obj
.PHONY : sylar/log.cpp.obj

sylar/log.i: sylar/log.cpp.i
.PHONY : sylar/log.i

# target to preprocess a source file
sylar/log.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\sylar.dir\build.make CMakeFiles/sylar.dir/sylar/log.cpp.i
.PHONY : sylar/log.cpp.i

sylar/log.s: sylar/log.cpp.s
.PHONY : sylar/log.s

# target to generate assembly for a file
sylar/log.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\sylar.dir\build.make CMakeFiles/sylar.dir/sylar/log.cpp.s
.PHONY : sylar/log.cpp.s

tests/test.obj: tests/test.cpp.obj
.PHONY : tests/test.obj

# target to build an object file
tests/test.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\test.dir\build.make CMakeFiles/test.dir/tests/test.cpp.obj
.PHONY : tests/test.cpp.obj

tests/test.i: tests/test.cpp.i
.PHONY : tests/test.i

# target to preprocess a source file
tests/test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\test.dir\build.make CMakeFiles/test.dir/tests/test.cpp.i
.PHONY : tests/test.cpp.i

tests/test.s: tests/test.cpp.s
.PHONY : tests/test.s

# target to generate assembly for a file
tests/test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\test.dir\build.make CMakeFiles/test.dir/tests/test.cpp.s
.PHONY : tests/test.cpp.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... rebuild_cache
	@echo ... sylar
	@echo ... test
	@echo ... sylar/log.obj
	@echo ... sylar/log.i
	@echo ... sylar/log.s
	@echo ... tests/test.obj
	@echo ... tests/test.i
	@echo ... tests/test.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system
