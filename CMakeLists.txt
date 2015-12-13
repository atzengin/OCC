# Copyright 2010-2012 Free Software Foundation, Inc.
#
# This file is part of OpenCv Companion
#
# OpenCv Companion is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# OpenCv Companion is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with OpenCv Companion; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. This is bad practice.")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(ocvc CXX C)
enable_testing()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Set the version information here
set(VERSION_INFO_MAJOR_VERSION 3)
set(VERSION_INFO_API_COMPAT    7)
set(VERSION_INFO_MINOR_VERSION 2)
set(VERSION_INFO_MAINT_VERSION git)
include(OcVersion) #setup version info

# Append -O2 optimization flag for Debug builds
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O2")

########################################################################
# Environment setup
########################################################################
IF(NOT DEFINED BOOST_ROOT)
    SET(BOOST_ROOT ${CMAKE_INSTALL_PREFIX})
ENDIF()

if(ENABLE_OC_CTRLPORT)
  set(OC_CTRLPORT True)
endif(ENABLE_OC_CTRLPORT)

########################################################################
# Import executables from a native build (for cross compiling)
# http://www.vtk.org/Wiki/CMake_Cross_Compiling#Using_executables_in_the_build_created_during_the_build
########################################################################
if(IMPORT_EXECUTABLES)
    include(${IMPORT_EXECUTABLES})
endif(IMPORT_EXECUTABLES)

#set file that the native build will fill with exports
set(EXPORT_FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake)
file(WRITE ${EXPORT_FILE}) #blank the file (subdirs will append)

########################################################################
# Compiler specific setup
########################################################################
include(OcMiscUtils) #compiler flag check

if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    OC_ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-fvisibility=hidden HAVE_VISIBILITY_HIDDEN)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    OC_ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-Wsign-compare HAVE_WARN_SIGN_COMPARE)
    OC_ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-Wall HAVE_WARN_ALL)
    OC_ADD_CXX_COMPILER_FLAG_IF_AVAILABLE(-Wno-uninitialized HAVE_WARN_NO_UNINITIALIZED)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
    include_directories(${CMAKE_SOURCE_DIR}/cmake/msvc) #missing headers
    add_definitions(-D_WIN32_WINNT=0x0501) #minimum version required is windows xp
    add_definitions(-DNOMINMAX) #disables stupidity and enables std::min and std::max
    add_definitions( #stop all kinds of compatibility warnings
        -D_SCL_SECURE_NO_WARNINGS
        -D_CRT_SECURE_NO_WARNINGS
        -D_CRT_SECURE_NO_DEPRECATE
        -D_CRT_NONSTDC_NO_DEPRECATE
    )
    add_definitions(-DHAVE_CONFIG_H)
    add_definitions(/MP) #build with multiple processors
    add_definitions(/bigobj) #allow for larger object files
endif(MSVC)

########################################################################
# Install directories
########################################################################
include(OcPlatform) #define LIB_SUFFIX
set(OC_RUNTIME_DIR      bin)
set(OC_LIBRARY_DIR      lib${LIB_SUFFIX})
set(OC_INCLUDE_DIR      include)
set(OC_DATA_DIR         share)
set(OC_PKG_DATA_DIR     ${OC_DATA_DIR}/${CMAKE_PROJECT_NAME})
set(OC_DOC_DIR          ${OC_DATA_DIR}/doc)
set(OC_PKG_DOC_DIR      ${OC_DOC_DIR}/${CMAKE_PROJECT_NAME}-${DOCVER})
set(OC_CONF_DIR         etc)
set(OC_PKG_CONF_DIR     ${OC_CONF_DIR}/${CMAKE_PROJECT_NAME}/conf.d)
set(OC_LIBEXEC_DIR      libexec)
set(OC_PKG_LIBEXEC_DIR  ${OC_LIBEXEC_DIR}/${CMAKE_PROJECT_NAME})
set(OCC_BLOCKS_DIR      ${OC_PKG_DATA_DIR}/occ/blocks)

# Special exception if prefix is /usr so we don't make a /usr/etc.
string(COMPARE EQUAL ${CMAKE_INSTALL_PREFIX} "/usr" isusr)
if(isusr)
  set(SYSCONFDIR          "/${OC_CONF_DIR}" CACHE PATH "System configuration directory")
else(isusr)
  set(SYSCONFDIR          "${CMAKE_INSTALL_PREFIX}/${OC_CONF_DIR}" CACHE PATH "System configuration directory" FORCE)
endif(isusr)

set(OC_PREFSDIR         ${SYSCONFDIR}/${CMAKE_PROJECT_NAME}/conf.d)

OPTION(ENABLE_PERFORMANCE_COUNTERS "Enable block performance counters" OFF)
if(ENABLE_PERFORMANCE_COUNTERS)
  message(STATUS "ADDING PERF COUNTERS")
  SET(OC_PERFORMANCE_COUNTERS True)
  add_definitions(-DOC_PERFORMANCE_COUNTERS)
else(ENABLE_PERFORMANCE_COUNTERS)
  SET(OC_PERFORMANCE_COUNTERS False)
  message(STATUS "NO PERF COUNTERS")
endif(ENABLE_PERFORMANCE_COUNTERS)

########################################################################
# Variables replaced when configuring the package config files
########################################################################
file(TO_NATIVE_PATH "${CMAKE_INSTALL_PREFIX}"           prefix)
file(TO_NATIVE_PATH "\${prefix}"                        exec_prefix)
file(TO_NATIVE_PATH "\${exec_prefix}/${OC_LIBRARY_DIR}" libdir)
file(TO_NATIVE_PATH "\${prefix}/${OC_INCLUDE_DIR}"      includedir)
file(TO_NATIVE_PATH "${SYSCONFDIR}"                     SYSCONFDIR)
file(TO_NATIVE_PATH "${OC_PREFSDIR}"                    OC_PREFSDIR)

########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

########################################################################
# Enable python component
########################################################################
find_package(PythonLibs 2)
find_package(SWIG)

if(SWIG_FOUND)
    message(STATUS "Minimum SWIG version required is 1.3.31")
    set(SWIG_VERSION_CHECK FALSE)
    if("${SWIG_VERSION}" VERSION_GREATER "1.3.30")
        set(SWIG_VERSION_CHECK TRUE)
    endif()
endif(SWIG_FOUND)

include(OcComponent)
OC_REGISTER_COMPONENT("python-support" ENABLE_PYTHON
    PYTHONLIBS_FOUND
    SWIG_FOUND
    SWIG_VERSION_CHECK
)

find_package(CppUnit)
OC_REGISTER_COMPONENT("testing-support" ENABLE_TESTING
    CPPUNIT_FOUND
)

########################################################################
# Add optional dlls specified in DLL_PATHS
########################################################################
foreach(path ${DLL_PATHS})
    file(GLOB _dlls "${path}/*.dll")
    list(APPEND ALL_DLL_FILES ${_dlls})
endforeach(path)
if(DEFINED ALL_DLL_FILES)
    include(OcPackage)
    CPACK_COMPONENT("extra_dlls"
        DISPLAY_NAME "Extra DLLs"
        DESCRIPTION  "Extra DLLs for runtime dependency requirements"
    )
    message(STATUS "")
    message(STATUS "Including the following dlls into the install:")
    foreach(_dll ${ALL_DLL_FILES})
        message(STATUS "  ${_dll}")
    endforeach(_dll)
    install(FILES ${ALL_DLL_FILES} DESTINATION ${OC_RUNTIME_DIR} COMPONENT "extra_dlls")
endif()

########################################################################
# Setup volk as a subproject
########################################################################
include(OcComponent)
OC_REGISTER_COMPONENT("volk" ENABLE_VOLK)

set(VOLK_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/volk/include
    ${CMAKE_CURRENT_BINARY_DIR}/volk/include
)

if(ENABLE_VOLK)

include(OcPackage)
CPACK_SET(CPACK_COMPONENT_GROUP_VOLK_DESCRIPTION "Vector optimized library of kernels")

CPACK_COMPONENT("volk_runtime"
    GROUP        "Volk"
    DISPLAY_NAME "Runtime"
    DESCRIPTION  "Dynamic link libraries"
)

CPACK_COMPONENT("volk_devel"
    GROUP        "Volk"
    DISPLAY_NAME "Development"
    DESCRIPTION  "C++ headers, package config, import libraries"
)


add_subdirectory(volk)
endif(ENABLE_VOLK)

# Handle oc_log enable/disable
OC_LOGGING()

########################################################################
# Distribute the README file
########################################################################
install(
    FILES README README.hacking
    DESTINATION ${OC_PKG_DOC_DIR}
    COMPONENT "docs"
)

########################################################################
# The following dependency libraries are needed by all gr modules:
########################################################################
list(APPEND OC_TEST_TARGET_DEPS volk ocvc-runtime)
list(APPEND OC_TEST_PYTHON_DIRS
    ${CMAKE_BINARY_DIR}/ocvc-runtime/python
    ${CMAKE_SOURCE_DIR}/ocvc-runtime/python
    ${CMAKE_BINARY_DIR}/ocvc-runtime/swig
)

# Note that above we put the binary ocvc-runtime/python directory
# before the source directory. This is due to a quirk with ControlPort
# and how slice generates files and names. We want the QA and
# installed code to import the same names, so we have to grab from the
# binary directory first.

########################################################################
# Add subdirectories (in order of deps)
########################################################################
#add_subdirectory(docs)
add_subdirectory(ocvc-runtime)
#add_subdirectory(oc-blocks)
add_subdirectory(occ)
#add_subdirectory(oc-fec)
#add_subdirectory(oc-fft)
#add_subdirectory(oc-filter)
#add_subdirectory(oc-analog)
#add_subdirectory(oc-digital)
#add_subdirectory(oc-atsc)
#add_subdirectory(oc-audio)
#add_subdirectory(oc-comedi)
#add_subdirectory(oc-channels)
#add_subdirectory(oc-noaa)
#add_subdirectory(oc-pager)
#add_subdirectory(oc-qtgui)
#add_subdirectory(oc-trellis)
#add_subdirectory(oc-uhd)
add_subdirectory(oc-utils)
#add_subdirectory(oc-video-sdl)
#add_subdirectory(oc-vocoder)
#add_subdirectory(oc-fcd)
#add_subdirectory(oc-wavelet)
#add_subdirectory(oc-wxgui)

# Install our Cmake modules into $prefix/lib/cmake/ocvc
# See "Package Configuration Files" on page:
#    http://www.cmake.org/Wiki/CMake/Tutorials/Packaging

configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/Modules/OcvcConfigVersion.cmake.in
  ${CMAKE_BINARY_DIR}/cmake/Modules/OcvcConfigVersion.cmake
@ONLY)

SET(cmake_configs
  ${CMAKE_SOURCE_DIR}/cmake/Modules/OcvcConfig.cmake
  ${CMAKE_BINARY_DIR}/cmake/Modules/OcvcConfigVersion.cmake
)

if(NOT CMAKE_MODULES_DIR)
   set(CMAKE_MODULES_DIR lib${LIB_SUFFIX}/cmake/ocvc)
endif(NOT CMAKE_MODULES_DIR)

# Install all other cmake files into same directory
file(GLOB cmake_others "cmake/Modules/*.cmake")
list(REMOVE_ITEM cmake_others
    "${CMAKE_SOURCE_DIR}/cmake/Modules/FindOcvc.cmake"
)

install(
  FILES ${cmake_configs} ${cmake_others}
  DESTINATION ${CMAKE_MODULES_DIR}
  COMPONENT "runtime_devel"
)

#finalize cpack after subdirs processed
include(OcPackage)
CPACK_FINALIZE()

########################################################################
# Print summary
########################################################################
OC_PRINT_COMPONENT_SUMMARY()
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

# Create a config.h with some definitions to export to other projects.
CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

# Install config.h in include/ocvc
install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
    DESTINATION ${OC_INCLUDE_DIR}/ocvc
    COMPONENT "runtime_devel"
)
