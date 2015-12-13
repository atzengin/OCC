# Copyright 2013 Free Software Foundation, Inc.
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
# Setup dependencies
########################################################################
include(OcBoost)
include(OcPython)

########################################################################
# Setup compatibility checks and defines
########################################################################
include(${CMAKE_CURRENT_SOURCE_DIR}/ConfigChecks.cmake)
OC_CHECK_LINUX_SCHED_AVAIL()

########################################################################
# Register component
########################################################################
include(OcComponent)
OC_REGISTER_COMPONENT("ocvc-runtime" ENABLE_OCVC_RUNTIME
    Boost_FOUND
    ENABLE_VOLK
    PYTHONINTERP_FOUND
)

OC_SET_GLOBAL(OCVC_RUNTIME_INCLUDE_DIRS
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/ocvc-runtime/include
    ${CMAKE_BINARY_DIR}/ocvc-runtime/include
)

OC_SET_GLOBAL(OCVC_RUNTIME_SWIG_INCLUDE_DIRS
    ${OCVC_RUNTIME_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/ocvc-runtime/swig
    ${CMAKE_BINARY_DIR}/ocvc-runtime/swig
)

get_filename_component(OCVC_RUNTIME_PYTHONPATH
    ${CMAKE_SOURCE_DIR}/python ABSOLUTE
)
OC_SET_GLOBAL(OCVC_RUNTIME_PYTHONPATH ${OCVC_RUNTIME_PYTHONPATH})

########################################################################
# Register controlport component
########################################################################

FIND_PACKAGE(ICE-3.5)  # check for ICE 3.5
if(NOT ICE_FOUND)
  message(STATUS "ICE 3.5 not found. Looking for 3.4")
  FIND_PACKAGE(ICE) # checks for version 3.4
endif(NOT ICE_FOUND)
FIND_PACKAGE(SWIG)

if(SWIG_FOUND)
    set(SWIG_VERSION_CHECK FALSE)
    if("${SWIG_VERSION}" VERSION_GREATER "2.0.0")
        set(SWIG_VERSION_CHECK TRUE)
    else("${SWIG_VERSION}" VERSION_GREATER "2.0.0")
      message(STATUS "")
      message(STATUS "Ctrlport requires SWIG version >= 2.0")
    endif()
endif(SWIG_FOUND)

OC_REGISTER_COMPONENT("oc-ctrlport" ENABLE_OC_CTRLPORT
    Boost_FOUND
    SWIG_FOUND
    SWIG_VERSION_CHECK
    ICE_FOUND
    ENABLE_OCVC_RUNTIME
)

########################################################################
# Begin conditional configuration
########################################################################
if(ENABLE_OCVC_RUNTIME)

get_filename_component(OC_RUNTIME_PYTHONPATH
    ${CMAKE_CURRENT_SOURCE_DIR}/python ABSOLUTE
)
OC_SET_GLOBAL(OC_RUNTIME_PYTHONPATH ${OC_RUNTIME_PYTHONPATH})

########################################################################
# Setup CPack components
########################################################################
include(OcPackage)
CPACK_SET(CPACK_COMPONENT_GROUP_RUNTIME_DESCRIPTION "OpenCv Companion Runtime")

CPACK_COMPONENT("runtime_runtime"
    GROUP        "Runtime"
    DISPLAY_NAME "Runtime"
    DESCRIPTION  "Dynamic link libraries"
    DEPENDS      "runtime_runtime"
)

CPACK_COMPONENT("runtime_devel"
    GROUP        "Runtime"
    DISPLAY_NAME "Development"
    DESCRIPTION  "C++ headers, package config, import libraries"
    DEPENDS      "runtime_devel"
)

CPACK_COMPONENT("runtime_python"
    GROUP        "Runtime"
    DISPLAY_NAME "Python"
    DESCRIPTION  "Python modules for runtime"
    DEPENDS      "runtime_python;runtime_runtime"
)

CPACK_COMPONENT("runtime_swig"
    GROUP        "Runtime"
    DISPLAY_NAME "SWIG"
    DESCRIPTION  "SWIG development .i files"
    DEPENDS      "runtime_swig;runtime_python;runtime_devel"
)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ocvc-runtime.conf.in
    ${CMAKE_CURRENT_BINARY_DIR}/ocvc-runtime.conf
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/ocvc-runtime.conf
    DESTINATION ${OC_PREFSDIR}
    COMPONENT "runtime_runtime"
)

if(ENABLE_OC_LOG AND HAVE_LOG4CPP)
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/oc_log_default.conf
    DESTINATION ${OC_CONF_DIR}/ocvc
    COMPONENT "runtime_runtime"
)
endif(ENABLE_OC_LOG AND HAVE_LOG4CPP)

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(apps)
#add_subdirectory(doc)
if(ENABLE_PYTHON)
     add_subdirectory(swig)
     add_subdirectory(python)
#    add_subdirectory(occ)
    add_subdirectory(examples)
endif(ENABLE_PYTHON)

########################################################################
# Create Pkg Config File
########################################################################
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ocvc-runtime.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/ocvc-runtime.pc
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/ocvc-runtime.pc
    DESTINATION ${OC_LIBRARY_DIR}/pkgconfig
    COMPONENT "runtime_devel"
)

########################################################################
# Setup ControlPort preferences file and installation information
########################################################################
if(ENABLE_OC_CTRLPORT)

SET(OC_PKG_CTRL_EXAMPLES_DIR ${OC_PKG_DATA_DIR}/examples/ctrlport)

SET(OC_PKG_CTRL_SLICE_DIR ${OC_PKG_DATA_DIR}/ctrlport)
file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${OC_PKG_CTRL_SLICE_DIR} slicedir)

install(
    FILES ctrlport.conf.example
    DESTINATION ${SYSCONFDIR}/${CMAKE_PROJECT_NAME}
    COMPONENT "ocvc_runtime"
)

endif(ENABLE_OC_CTRLPORT)

endif(ENABLE_OCVC_RUNTIME)
