# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Include swig generation macros
########################################################################
find_package(SWIG)
find_package(PythonLibs 2)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(OcSwig)
include(OcPython)

########################################################################
# Setup swig generation
########################################################################
foreach(incdir ${OCVC_RUNTIME_INCLUDE_DIRS})
    list(APPEND OC_SWIG_INCLUDE_DIRS ${incdir}/ocvc/swig)
endforeach(incdir)

set(OC_SWIG_LIBRARIES ocvc-opencv)
set(OC_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/opencv_swig_doc.i)
set(OC_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)

OC_SWIG_MAKE(opencv_swig opencv_swig.i)

########################################################################
# Install the build swig module
########################################################################
OC_SWIG_INSTALL(TARGETS opencv_swig DESTINATION ${OC_PYTHON_DIR}/opencv)

########################################################################
# Install swig .i files for development
########################################################################
install(
    FILES
    opencv_swig.i
    ${CMAKE_CURRENT_BINARY_DIR}/opencv_swig_doc.i
    DESTINATION ${OC_INCLUDE_DIR}/opencv/swig
)
