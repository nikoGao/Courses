PROJECT(assignment_04)
cmake_minimum_required(VERSION 2.8)

# list of source files
set(assignment_04_1_files assignment_04_1.cpp)
set(assignment_04_2_files assignment_04_2.cpp)
# set(assignment_04_3_files assignment_04_3.cpp)
set(assignment_04_3_files myStringFunctions.cpp myStringFunctions.hpp assignment_04_3.cpp)

# define the executable
if(WIN32)
  add_executable(assignment_04_1 WIN32 ${assignment_04_1_files})
  add_executable(assignment_04_2 WIN32 ${assignment_03_2_files})
  add_executable(assignment_04_3 WIN32 ${assignment_04_3_files})
else()
  add_executable(assignment_04_1 ${assignment_04_1_files})
  add_executable(assignment_04_2 ${assignment_04_2_files})
  add_executable(assignment_04_3 ${assignment_04_3_files})
endif()

# in Windows + Visual Studio we need this to make it a console application
if(WIN32)
  if(MSVC)
    set_target_properties(assignment_04_1 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_04_2 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_04_3 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif(MSVC)
endif(WIN32)

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS
	 assignment_04_1
	 assignment_04_2
	 assignment_04_3
        DESTINATION ${BIN_DIR})
