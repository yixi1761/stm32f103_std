# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/57/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/57/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ansel/c_parctice/ywbox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ansel/c_parctice/ywbox/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ywbox.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ywbox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ywbox.dir/flags.make

CMakeFiles/ywbox.dir/main.c.o: CMakeFiles/ywbox.dir/flags.make
CMakeFiles/ywbox.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ansel/c_parctice/ywbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ywbox.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ywbox.dir/main.c.o   -c /home/ansel/c_parctice/ywbox/main.c

CMakeFiles/ywbox.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ywbox.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ansel/c_parctice/ywbox/main.c > CMakeFiles/ywbox.dir/main.c.i

CMakeFiles/ywbox.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ywbox.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ansel/c_parctice/ywbox/main.c -o CMakeFiles/ywbox.dir/main.c.s

CMakeFiles/ywbox.dir/src/voltameter.c.o: CMakeFiles/ywbox.dir/flags.make
CMakeFiles/ywbox.dir/src/voltameter.c.o: ../src/voltameter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ansel/c_parctice/ywbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ywbox.dir/src/voltameter.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ywbox.dir/src/voltameter.c.o   -c /home/ansel/c_parctice/ywbox/src/voltameter.c

CMakeFiles/ywbox.dir/src/voltameter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ywbox.dir/src/voltameter.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ansel/c_parctice/ywbox/src/voltameter.c > CMakeFiles/ywbox.dir/src/voltameter.c.i

CMakeFiles/ywbox.dir/src/voltameter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ywbox.dir/src/voltameter.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ansel/c_parctice/ywbox/src/voltameter.c -o CMakeFiles/ywbox.dir/src/voltameter.c.s

CMakeFiles/ywbox.dir/src/io_check_ctl.c.o: CMakeFiles/ywbox.dir/flags.make
CMakeFiles/ywbox.dir/src/io_check_ctl.c.o: ../src/io_check_ctl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ansel/c_parctice/ywbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ywbox.dir/src/io_check_ctl.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ywbox.dir/src/io_check_ctl.c.o   -c /home/ansel/c_parctice/ywbox/src/io_check_ctl.c

CMakeFiles/ywbox.dir/src/io_check_ctl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ywbox.dir/src/io_check_ctl.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ansel/c_parctice/ywbox/src/io_check_ctl.c > CMakeFiles/ywbox.dir/src/io_check_ctl.c.i

CMakeFiles/ywbox.dir/src/io_check_ctl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ywbox.dir/src/io_check_ctl.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ansel/c_parctice/ywbox/src/io_check_ctl.c -o CMakeFiles/ywbox.dir/src/io_check_ctl.c.s

CMakeFiles/ywbox.dir/src/led_display.c.o: CMakeFiles/ywbox.dir/flags.make
CMakeFiles/ywbox.dir/src/led_display.c.o: ../src/led_display.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ansel/c_parctice/ywbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ywbox.dir/src/led_display.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ywbox.dir/src/led_display.c.o   -c /home/ansel/c_parctice/ywbox/src/led_display.c

CMakeFiles/ywbox.dir/src/led_display.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ywbox.dir/src/led_display.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ansel/c_parctice/ywbox/src/led_display.c > CMakeFiles/ywbox.dir/src/led_display.c.i

CMakeFiles/ywbox.dir/src/led_display.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ywbox.dir/src/led_display.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ansel/c_parctice/ywbox/src/led_display.c -o CMakeFiles/ywbox.dir/src/led_display.c.s

CMakeFiles/ywbox.dir/src/temperature.c.o: CMakeFiles/ywbox.dir/flags.make
CMakeFiles/ywbox.dir/src/temperature.c.o: ../src/temperature.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ansel/c_parctice/ywbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ywbox.dir/src/temperature.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ywbox.dir/src/temperature.c.o   -c /home/ansel/c_parctice/ywbox/src/temperature.c

CMakeFiles/ywbox.dir/src/temperature.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ywbox.dir/src/temperature.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ansel/c_parctice/ywbox/src/temperature.c > CMakeFiles/ywbox.dir/src/temperature.c.i

CMakeFiles/ywbox.dir/src/temperature.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ywbox.dir/src/temperature.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ansel/c_parctice/ywbox/src/temperature.c -o CMakeFiles/ywbox.dir/src/temperature.c.s

# Object files for target ywbox
ywbox_OBJECTS = \
"CMakeFiles/ywbox.dir/main.c.o" \
"CMakeFiles/ywbox.dir/src/voltameter.c.o" \
"CMakeFiles/ywbox.dir/src/io_check_ctl.c.o" \
"CMakeFiles/ywbox.dir/src/led_display.c.o" \
"CMakeFiles/ywbox.dir/src/temperature.c.o"

# External object files for target ywbox
ywbox_EXTERNAL_OBJECTS =

ywbox: CMakeFiles/ywbox.dir/main.c.o
ywbox: CMakeFiles/ywbox.dir/src/voltameter.c.o
ywbox: CMakeFiles/ywbox.dir/src/io_check_ctl.c.o
ywbox: CMakeFiles/ywbox.dir/src/led_display.c.o
ywbox: CMakeFiles/ywbox.dir/src/temperature.c.o
ywbox: CMakeFiles/ywbox.dir/build.make
ywbox: CMakeFiles/ywbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ansel/c_parctice/ywbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable ywbox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ywbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ywbox.dir/build: ywbox

.PHONY : CMakeFiles/ywbox.dir/build

CMakeFiles/ywbox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ywbox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ywbox.dir/clean

CMakeFiles/ywbox.dir/depend:
	cd /home/ansel/c_parctice/ywbox/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ansel/c_parctice/ywbox /home/ansel/c_parctice/ywbox /home/ansel/c_parctice/ywbox/cmake-build-debug /home/ansel/c_parctice/ywbox/cmake-build-debug /home/ansel/c_parctice/ywbox/cmake-build-debug/CMakeFiles/ywbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ywbox.dir/depend

