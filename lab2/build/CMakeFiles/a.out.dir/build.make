# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/vladislav/Desktop/KPI/progbase2/labs/lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vladislav/Desktop/KPI/progbase2/labs/lab2/build

# Include any dependencies generated for this target.
include CMakeFiles/a.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.out.dir/flags.make

CMakeFiles/a.out.dir/csv.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/csv.c.o: ../csv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladislav/Desktop/KPI/progbase2/labs/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/a.out.dir/csv.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/a.out.dir/csv.c.o   -c /home/vladislav/Desktop/KPI/progbase2/labs/lab2/csv.c

CMakeFiles/a.out.dir/csv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/csv.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vladislav/Desktop/KPI/progbase2/labs/lab2/csv.c > CMakeFiles/a.out.dir/csv.c.i

CMakeFiles/a.out.dir/csv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/csv.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vladislav/Desktop/KPI/progbase2/labs/lab2/csv.c -o CMakeFiles/a.out.dir/csv.c.s

CMakeFiles/a.out.dir/csv.c.o.requires:

.PHONY : CMakeFiles/a.out.dir/csv.c.o.requires

CMakeFiles/a.out.dir/csv.c.o.provides: CMakeFiles/a.out.dir/csv.c.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/csv.c.o.provides.build
.PHONY : CMakeFiles/a.out.dir/csv.c.o.provides

CMakeFiles/a.out.dir/csv.c.o.provides.build: CMakeFiles/a.out.dir/csv.c.o


CMakeFiles/a.out.dir/list.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/list.c.o: ../list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladislav/Desktop/KPI/progbase2/labs/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/a.out.dir/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/a.out.dir/list.c.o   -c /home/vladislav/Desktop/KPI/progbase2/labs/lab2/list.c

CMakeFiles/a.out.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vladislav/Desktop/KPI/progbase2/labs/lab2/list.c > CMakeFiles/a.out.dir/list.c.i

CMakeFiles/a.out.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vladislav/Desktop/KPI/progbase2/labs/lab2/list.c -o CMakeFiles/a.out.dir/list.c.s

CMakeFiles/a.out.dir/list.c.o.requires:

.PHONY : CMakeFiles/a.out.dir/list.c.o.requires

CMakeFiles/a.out.dir/list.c.o.provides: CMakeFiles/a.out.dir/list.c.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/list.c.o.provides.build
.PHONY : CMakeFiles/a.out.dir/list.c.o.provides

CMakeFiles/a.out.dir/list.c.o.provides.build: CMakeFiles/a.out.dir/list.c.o


CMakeFiles/a.out.dir/main.c.o: CMakeFiles/a.out.dir/flags.make
CMakeFiles/a.out.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladislav/Desktop/KPI/progbase2/labs/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/a.out.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/a.out.dir/main.c.o   -c /home/vladislav/Desktop/KPI/progbase2/labs/lab2/main.c

CMakeFiles/a.out.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a.out.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vladislav/Desktop/KPI/progbase2/labs/lab2/main.c > CMakeFiles/a.out.dir/main.c.i

CMakeFiles/a.out.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a.out.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vladislav/Desktop/KPI/progbase2/labs/lab2/main.c -o CMakeFiles/a.out.dir/main.c.s

CMakeFiles/a.out.dir/main.c.o.requires:

.PHONY : CMakeFiles/a.out.dir/main.c.o.requires

CMakeFiles/a.out.dir/main.c.o.provides: CMakeFiles/a.out.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/main.c.o.provides.build
.PHONY : CMakeFiles/a.out.dir/main.c.o.provides

CMakeFiles/a.out.dir/main.c.o.provides.build: CMakeFiles/a.out.dir/main.c.o


# Object files for target a.out
a_out_OBJECTS = \
"CMakeFiles/a.out.dir/csv.c.o" \
"CMakeFiles/a.out.dir/list.c.o" \
"CMakeFiles/a.out.dir/main.c.o"

# External object files for target a.out
a_out_EXTERNAL_OBJECTS =

../a.out: CMakeFiles/a.out.dir/csv.c.o
../a.out: CMakeFiles/a.out.dir/list.c.o
../a.out: CMakeFiles/a.out.dir/main.c.o
../a.out: CMakeFiles/a.out.dir/build.make
../a.out: CMakeFiles/a.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vladislav/Desktop/KPI/progbase2/labs/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ../a.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a.out.dir/build: ../a.out

.PHONY : CMakeFiles/a.out.dir/build

CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/csv.c.o.requires
CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/list.c.o.requires
CMakeFiles/a.out.dir/requires: CMakeFiles/a.out.dir/main.c.o.requires

.PHONY : CMakeFiles/a.out.dir/requires

CMakeFiles/a.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.out.dir/clean

CMakeFiles/a.out.dir/depend:
	cd /home/vladislav/Desktop/KPI/progbase2/labs/lab2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vladislav/Desktop/KPI/progbase2/labs/lab2 /home/vladislav/Desktop/KPI/progbase2/labs/lab2 /home/vladislav/Desktop/KPI/progbase2/labs/lab2/build /home/vladislav/Desktop/KPI/progbase2/labs/lab2/build /home/vladislav/Desktop/KPI/progbase2/labs/lab2/build/CMakeFiles/a.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a.out.dir/depend

