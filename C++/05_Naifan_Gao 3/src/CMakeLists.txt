PROJECT(Assignment_05)
cmake_minimum_required(VERSION 2.8)

# list of source files
set(assignment_05_files AlgebraicTreeNode.cpp AlgebraicTreeNode.hpp Calc5.cpp)

# define the executable
if(WIN32)
  add_executable(calc5 WIN32 ${assignment_05_files})
else()
  add_executable(calc5 ${assignment_05_files})
endif()

# in Windows + Visual Studio we need this to make it a console application
if(WIN32)
  if(MSVC)
    set_target_properties(calc5 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif(MSVC)
endif(WIN32)

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS calc5 DESTINATION ${BIN_DIR})
