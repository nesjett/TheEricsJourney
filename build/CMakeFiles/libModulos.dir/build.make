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
CMAKE_SOURCE_DIR = /home/nestor/Desktop/TheEricsJourney

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nestor/Desktop/TheEricsJourney/build

# Include any dependencies generated for this target.
include CMakeFiles/libModulos.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libModulos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libModulos.dir/flags.make

CMakeFiles/libModulos.dir/src/private/Engine.cpp.o: CMakeFiles/libModulos.dir/flags.make
CMakeFiles/libModulos.dir/src/private/Engine.cpp.o: ../src/private/Engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nestor/Desktop/TheEricsJourney/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libModulos.dir/src/private/Engine.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libModulos.dir/src/private/Engine.cpp.o -c /home/nestor/Desktop/TheEricsJourney/src/private/Engine.cpp

CMakeFiles/libModulos.dir/src/private/Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libModulos.dir/src/private/Engine.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nestor/Desktop/TheEricsJourney/src/private/Engine.cpp > CMakeFiles/libModulos.dir/src/private/Engine.cpp.i

CMakeFiles/libModulos.dir/src/private/Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libModulos.dir/src/private/Engine.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nestor/Desktop/TheEricsJourney/src/private/Engine.cpp -o CMakeFiles/libModulos.dir/src/private/Engine.cpp.s

CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.requires:

.PHONY : CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.requires

CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.provides: CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.requires
	$(MAKE) -f CMakeFiles/libModulos.dir/build.make CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.provides.build
.PHONY : CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.provides

CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.provides.build: CMakeFiles/libModulos.dir/src/private/Engine.cpp.o


CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o: CMakeFiles/libModulos.dir/flags.make
CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o: ../src/private/Pawn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nestor/Desktop/TheEricsJourney/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o -c /home/nestor/Desktop/TheEricsJourney/src/private/Pawn.cpp

CMakeFiles/libModulos.dir/src/private/Pawn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libModulos.dir/src/private/Pawn.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nestor/Desktop/TheEricsJourney/src/private/Pawn.cpp > CMakeFiles/libModulos.dir/src/private/Pawn.cpp.i

CMakeFiles/libModulos.dir/src/private/Pawn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libModulos.dir/src/private/Pawn.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nestor/Desktop/TheEricsJourney/src/private/Pawn.cpp -o CMakeFiles/libModulos.dir/src/private/Pawn.cpp.s

CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.requires:

.PHONY : CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.requires

CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.provides: CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.requires
	$(MAKE) -f CMakeFiles/libModulos.dir/build.make CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.provides.build
.PHONY : CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.provides

CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.provides.build: CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o


CMakeFiles/libModulos.dir/src/private/Actor.cpp.o: CMakeFiles/libModulos.dir/flags.make
CMakeFiles/libModulos.dir/src/private/Actor.cpp.o: ../src/private/Actor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nestor/Desktop/TheEricsJourney/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/libModulos.dir/src/private/Actor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libModulos.dir/src/private/Actor.cpp.o -c /home/nestor/Desktop/TheEricsJourney/src/private/Actor.cpp

CMakeFiles/libModulos.dir/src/private/Actor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libModulos.dir/src/private/Actor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nestor/Desktop/TheEricsJourney/src/private/Actor.cpp > CMakeFiles/libModulos.dir/src/private/Actor.cpp.i

CMakeFiles/libModulos.dir/src/private/Actor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libModulos.dir/src/private/Actor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nestor/Desktop/TheEricsJourney/src/private/Actor.cpp -o CMakeFiles/libModulos.dir/src/private/Actor.cpp.s

CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.requires:

.PHONY : CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.requires

CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.provides: CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.requires
	$(MAKE) -f CMakeFiles/libModulos.dir/build.make CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.provides.build
.PHONY : CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.provides

CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.provides.build: CMakeFiles/libModulos.dir/src/private/Actor.cpp.o


CMakeFiles/libModulos.dir/src/private/game.cpp.o: CMakeFiles/libModulos.dir/flags.make
CMakeFiles/libModulos.dir/src/private/game.cpp.o: ../src/private/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nestor/Desktop/TheEricsJourney/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/libModulos.dir/src/private/game.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libModulos.dir/src/private/game.cpp.o -c /home/nestor/Desktop/TheEricsJourney/src/private/game.cpp

CMakeFiles/libModulos.dir/src/private/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libModulos.dir/src/private/game.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nestor/Desktop/TheEricsJourney/src/private/game.cpp > CMakeFiles/libModulos.dir/src/private/game.cpp.i

CMakeFiles/libModulos.dir/src/private/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libModulos.dir/src/private/game.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nestor/Desktop/TheEricsJourney/src/private/game.cpp -o CMakeFiles/libModulos.dir/src/private/game.cpp.s

CMakeFiles/libModulos.dir/src/private/game.cpp.o.requires:

.PHONY : CMakeFiles/libModulos.dir/src/private/game.cpp.o.requires

CMakeFiles/libModulos.dir/src/private/game.cpp.o.provides: CMakeFiles/libModulos.dir/src/private/game.cpp.o.requires
	$(MAKE) -f CMakeFiles/libModulos.dir/build.make CMakeFiles/libModulos.dir/src/private/game.cpp.o.provides.build
.PHONY : CMakeFiles/libModulos.dir/src/private/game.cpp.o.provides

CMakeFiles/libModulos.dir/src/private/game.cpp.o.provides.build: CMakeFiles/libModulos.dir/src/private/game.cpp.o


CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o: CMakeFiles/libModulos.dir/flags.make
CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o: ../src/private/Projectile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nestor/Desktop/TheEricsJourney/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o -c /home/nestor/Desktop/TheEricsJourney/src/private/Projectile.cpp

CMakeFiles/libModulos.dir/src/private/Projectile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libModulos.dir/src/private/Projectile.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nestor/Desktop/TheEricsJourney/src/private/Projectile.cpp > CMakeFiles/libModulos.dir/src/private/Projectile.cpp.i

CMakeFiles/libModulos.dir/src/private/Projectile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libModulos.dir/src/private/Projectile.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nestor/Desktop/TheEricsJourney/src/private/Projectile.cpp -o CMakeFiles/libModulos.dir/src/private/Projectile.cpp.s

CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.requires:

.PHONY : CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.requires

CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.provides: CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.requires
	$(MAKE) -f CMakeFiles/libModulos.dir/build.make CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.provides.build
.PHONY : CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.provides

CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.provides.build: CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o


CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o: CMakeFiles/libModulos.dir/flags.make
CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o: ../src/private/Enemy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nestor/Desktop/TheEricsJourney/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o -c /home/nestor/Desktop/TheEricsJourney/src/private/Enemy.cpp

CMakeFiles/libModulos.dir/src/private/Enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libModulos.dir/src/private/Enemy.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nestor/Desktop/TheEricsJourney/src/private/Enemy.cpp > CMakeFiles/libModulos.dir/src/private/Enemy.cpp.i

CMakeFiles/libModulos.dir/src/private/Enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libModulos.dir/src/private/Enemy.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nestor/Desktop/TheEricsJourney/src/private/Enemy.cpp -o CMakeFiles/libModulos.dir/src/private/Enemy.cpp.s

CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.requires:

.PHONY : CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.requires

CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.provides: CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.requires
	$(MAKE) -f CMakeFiles/libModulos.dir/build.make CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.provides.build
.PHONY : CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.provides

CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.provides.build: CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o


# Object files for target libModulos
libModulos_OBJECTS = \
"CMakeFiles/libModulos.dir/src/private/Engine.cpp.o" \
"CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o" \
"CMakeFiles/libModulos.dir/src/private/Actor.cpp.o" \
"CMakeFiles/libModulos.dir/src/private/game.cpp.o" \
"CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o" \
"CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o"

# External object files for target libModulos
libModulos_EXTERNAL_OBJECTS =

liblibModulos.a: CMakeFiles/libModulos.dir/src/private/Engine.cpp.o
liblibModulos.a: CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o
liblibModulos.a: CMakeFiles/libModulos.dir/src/private/Actor.cpp.o
liblibModulos.a: CMakeFiles/libModulos.dir/src/private/game.cpp.o
liblibModulos.a: CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o
liblibModulos.a: CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o
liblibModulos.a: CMakeFiles/libModulos.dir/build.make
liblibModulos.a: CMakeFiles/libModulos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nestor/Desktop/TheEricsJourney/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library liblibModulos.a"
	$(CMAKE_COMMAND) -P CMakeFiles/libModulos.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libModulos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libModulos.dir/build: liblibModulos.a

.PHONY : CMakeFiles/libModulos.dir/build

CMakeFiles/libModulos.dir/requires: CMakeFiles/libModulos.dir/src/private/Engine.cpp.o.requires
CMakeFiles/libModulos.dir/requires: CMakeFiles/libModulos.dir/src/private/Pawn.cpp.o.requires
CMakeFiles/libModulos.dir/requires: CMakeFiles/libModulos.dir/src/private/Actor.cpp.o.requires
CMakeFiles/libModulos.dir/requires: CMakeFiles/libModulos.dir/src/private/game.cpp.o.requires
CMakeFiles/libModulos.dir/requires: CMakeFiles/libModulos.dir/src/private/Projectile.cpp.o.requires
CMakeFiles/libModulos.dir/requires: CMakeFiles/libModulos.dir/src/private/Enemy.cpp.o.requires

.PHONY : CMakeFiles/libModulos.dir/requires

CMakeFiles/libModulos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libModulos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libModulos.dir/clean

CMakeFiles/libModulos.dir/depend:
	cd /home/nestor/Desktop/TheEricsJourney/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nestor/Desktop/TheEricsJourney /home/nestor/Desktop/TheEricsJourney /home/nestor/Desktop/TheEricsJourney/build /home/nestor/Desktop/TheEricsJourney/build /home/nestor/Desktop/TheEricsJourney/build/CMakeFiles/libModulos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libModulos.dir/depend

