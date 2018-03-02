cmake_minimum_required(VERSION 2.8.11)

set(NAME QtCalc2)

project(${NAME})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# This variable is used to locate the bin directory where the
# application will be installed
set(CMAKE_INSTALL_PREFIX
    ${PROJECT_SOURCE_DIR}/..
    CACHE PATH "Project bin directory" FORCE)

# you can comment the following line
message("CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")

# set to the proper directory in your machine 
set(Qt5_cmake_DIR /Users/niko/Qt/5.10.0/clang_64/lib/cmake)

# This is needded for CMake to find the Qt libraries
set(CMAKE_PREFIX_PATH
    ${Qt5_cmake_DIR}
    CACHE PATH "Qt5 cmake directory" FORCE)

# you can comment the following line
message ("CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}") 

# alternative way to make CMake find the Qt libraries
# set(Qt5core_DIR    ${Qt5_cmake_DIR}/Qt5core)
# set(Qt5Widgets_DIR ${Qt5_cmake_DIR}/Qt5Widgets)
# set(Qt5Svg_DIR     ${Qt5_cmake_DIR}/Qt5Svg)

# Find the QtWidgets library
find_package(Qt5core)
find_package(Qt5Widgets)
find_package(Qt5Svg)

set(FORMS_DIR ../forms)
set(ASSETS_DIR ../assets)

add_definitions(-DNOMINMAX -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES)

#add current dir to include search path
include_directories(${PROJECT_SOURCE_DIR})

#library list
set(LIB_LIST Qt5::Core Qt5::Widgets Qt5::Svg)

set(HEADERS
  MainWindow.hpp
  AboutDialog.hpp
  AlgebraicTreeExpression.hpp
  AlgebraicTreeNode.hpp
  AlgebraicTreeNumber.hpp
  AlgebraicTreeOperation.hpp
) # HEADERS    

set(SOURCES
  main.cpp
  MainWindow.cpp
  AboutDialog.cpp
  AlgebraicTreeExpression.cpp
  AlgebraicTreeNode.cpp
  AlgebraicTreeNumber.cpp
  AlgebraicTreeOperation.cpp
) # SOURCES

qt5_wrap_ui(FORMS
 ../forms/MainWindow.ui
 ../forms/AboutDialog.ui
) # FORMS

qt5_add_resources(ASSETS
) # ASSETS

if (APPLE)
  add_executable(${NAME} MACOSX_BUNDLE ${APP_ICON}
      ${HEADERS}
      ${SOURCES}
      ${FORMS}
      ${ASSETS}
  ) # add_executable
else(APPLE)
  add_executable(${NAME}
      ${HEADERS}
      ${SOURCES}
      ${FORMS}
      ${ASSETS}
  ) # add_executable
endif(APPLE)

target_compile_features(${NAME} PRIVATE cxx_right_angle_brackets cxx_lambdas)

target_link_libraries(${NAME} ${LIB_LIST})

# install application
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS ${NAME} DESTINATION ${BIN_DIR})
