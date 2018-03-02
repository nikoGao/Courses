# Install script for directory: /Users/niko/Documents/Courses/C++/05_Naifan_Gao/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/niko/Documents/Courses/C++/05_Naifan_Gao")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin" TYPE EXECUTABLE FILES "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/Debug/calc5")
    if(EXISTS "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin" TYPE EXECUTABLE FILES "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/Release/calc5")
    if(EXISTS "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin" TYPE EXECUTABLE FILES "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/MinSizeRel/calc5")
    if(EXISTS "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin" TYPE EXECUTABLE FILES "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/RelWithDebInfo/calc5")
    if(EXISTS "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/niko/Documents/Courses/C++/05_Naifan_Gao/bin/calc5")
      endif()
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
