PROJECT(Calc6)
cmake_minimum_required(VERSION 2.8)

# list of source files
set(calc6_files Calc6.cpp AlgebraicTreeNode.hpp AlgebraicTreeNode.cpp AlgebraicTreeExpression.hpp AlgebraicTreeExpression.cpp)

# define the executable
# if(WIN32)
  add_executable(calc6 WIN32 ${calc6_files})
# else()
#   add_executable(calc6 ${calc6_files})
# endif()

# in Windows + Visual Studio we need this to make it a console application
if(WIN32)
  if(MSVC)
    set_target_properties(calc6 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif(MSVC)
endif(WIN32)

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)

install(TARGETS calc6 DESTINATION ${BIN_DIR})
