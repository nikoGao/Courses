PROJECT(Calc7)
cmake_minimum_required(VERSION 2.8)

# list of source files
set(calc7_files
AlgebraicTreeExpression.cpp
AlgebraicTreeExpression.hpp
AlgebraicTreeNode.cpp
AlgebraicTreeNode.hpp
AlgebraicTreeNumber.cpp
AlgebraicTreeNumber.hpp
AlgebraicTreeOperation.cpp
AlgebraicTreeOperation.hpp
CMakeLists.txt
Calc7.cpp
)

# define the executable
# if(WIN32)
  add_executable(calc7 WIN32 ${calc7_files})
# else()
#   add_executable(calc7 ${calc7_files})
# endif()

# in Windows + Visual Studio we need this to make it a console application
if(WIN32)
  if(MSVC)
    set_target_properties(calc7 PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif(MSVC)
endif(WIN32)

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)

install(TARGETS calc7 DESTINATION ${BIN_DIR})

