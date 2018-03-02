PROJECT(Assignment_02)
cmake_minimum_required(VERSION 2.8)

# list of source files
set(assignment_02_1_files Assignment_02_1.cpp)
set(assignment_02_2_files Assignment_02_2.cpp)
set(assignment_02_3_files Assignment_02_3.cpp)

# define the executable
if(WIN32)
  add_executable(assignment_02_1 WIN32 ${assignment_02_1_files})
  add_executable(assignment_02_2 WIN32 ${assign ment_02_2_files})
  add_executable(assignment_02_3 WIN32 ${assignment_02_3_files})
else()
  add_executable(assignment_02_1 ${assignment_02_1_files})
  add_executable(assignment_02_2 ${assignment_02_2_files})
  add_executable(assignment_02_3 ${assignment_02_3_files})
endif()

# in Windows + Visual Studio we need this to make it a console application
if(WIN32)
  if(MSVC)
    set_target_properties(assignment_02_1 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_02_2 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    set_target_properties(assignment_02_3 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif(MSVC)
endif(WIN32)

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS assignment_02_1 assignment_02_2 assignment_02_3
        DESTINATION ${BIN_DIR})
