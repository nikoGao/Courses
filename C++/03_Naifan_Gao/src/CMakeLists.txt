PROJECT(Assignment_03)
cmake_minimum_required(VERSION 2.8)

# list of source files
set(assignment_03_1_files Assignment_03_1.cpp)
set(assignment_03_2_files Assignment_03_2.cpp)
set(assignment_03_3_files Assignment_03_3.cpp)
set(assignment_03_4_files Assignment_03_4.cpp)
set(assignment_03_5_files Assignment_03_5.cpp)

# define the executable
if(WIN32)
  add_executable(assignment_03_1 WIN32 ${assignment_03_1_files})
  add_executable(assignment_03_2 WIN32 ${assign ment_03_2_files})
  add_executable(assignment_03_3 WIN32 ${assignment_03_3_files})
  add_executable(assignment_03_4 WIN32 ${assignment_03_4_files})
  add_executable(assignment_03_5 WIN32 ${assignment_03_5_files})
else()
  add_executable(assignment_03_1 ${assignment_03_1_files})
  add_executable(assignment_03_2 ${assignment_03_2_files})
  add_executable(assignment_03_3 ${assignment_03_3_files})
  add_executable(assignment_03_4 ${assignment_03_4_files})
  add_executable(assignment_03_5 ${assignment_03_5_files})
endif()

# in Windows + Visual Studio we need this to make it a console application
if(WIN32)
  if(MSVC)
    set_target_properties(assignment_03_1 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_03_2 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_03_3 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_03_4 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_03_5 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif(MSVC)
endif(WIN32)

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS
	 assignment_03_1
	 assignment_03_2
	 assignment_03_3
	 assignment_03_4
	 assignment_03_5
        DESTINATION ${BIN_DIR})
