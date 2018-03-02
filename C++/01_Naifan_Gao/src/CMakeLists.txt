PROJECT(Assignment_01)
cmake_minimum_required(VERSION 2.8)

# list of source files
set(assignment_01_files Assignment_01.cpp)

# define the executable
if(WIN32)
  add_executable(assignment_01 WIN32 ${assignment_01_files})
else()
  add_executable(assignment_01 ${assignment_01_files})
endif()

# in Windows + Visual Studio we need this to make it a console application
if(WIN32)
  if(MSVC)
    set_target_properties(assignment_01 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif(MSVC)
endif(WIN32)

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS assignment_01 DESTINATION ${BIN_DIR})
