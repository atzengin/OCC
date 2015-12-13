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
# Setup swig generation
########################################################################
include(OcPython)
include(OcSwig)

set(OC_SWIG_INCLUDE_DIRS
    ${OCVC_RUNTIME_INCLUDE_DIRS}
    ${OCVC_RUNTIME_SWIG_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${LOG4CPP_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

link_directories(${Boost_LIBRARY_DIRS})

set(OC_SWIG_LIBRARIES
    ocvc-pmt
    ocvc-runtime
    ${LOG4CPP_LIBRARIES}
)

###############################################################
#    Build pmt swig 
###############################################################

set(OC_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/pmt_swig_doc.i)
set(OC_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include/pmt 
  ${CMAKE_CURRENT_BINARY_DIR}/../include/pmt)
list(APPEND OC_SWIG_TARGET_DEPS pmt_generated)
OC_SWIG_MAKE(pmt_swig pmt_swig.i)

OC_SWIG_INSTALL(
    TARGETS pmt_swig
    DESTINATION ${OC_PYTHON_DIR}/pmt
    COMPONENT "runtime_python"
)

add_custom_target(pmt_swig DEPENDS ${SWIG_MODULE_pmt_swig_REAL_NAME})

###############################################################
#    Build ocvc-runtime swig 
###############################################################

# Only use if log4cpp is installed
# Define ENABLE_OC_LOG for the .i file to ignore it.
if(ENABLE_OC_LOG)
     SET(OC_SWIG_FLAGS "-DENABLE_OC_LOG")
endif(ENABLE_OC_LOG)

if(ENABLE_OC_CTRLPORT)
  ADD_DEFINITIONS(-DOC_CTRLPORT)
  list(APPEND OC_SWIG_FLAGS -DOC_CTRLPORT)
  list(APPEND OC_SWIG_LIBRARIES ${ICE_LIBRARIES})
  list(APPEND OC_SWIG_INCLUDE_DIRS ${ICE_INCLUDE_DIR})
endif(ENABLE_OC_CTRLPORT)

set(OC_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/runtime_swig_doc.i)
set(OC_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(OC_RUNTIME_SWIG_DOC_FILE ${OC_SWIG_DOC_FILE})
list(APPEND OC_SWIG_TARGET_DEPS pmt_swig)

OC_SWIG_MAKE(runtime_swig runtime_swig.i)

OC_SWIG_INSTALL(
    TARGETS runtime_swig
    DESTINATION ${OC_PYTHON_DIR}/ocvc/gr
    COMPONENT "runtime_python"
)

install(
    FILES
    ocvc_swig_bug_workaround.h
    runtime_swig.i
    ocvc.i
    basic_block.i
    block.i
    block_detail.i
    block_gateway.i
    buffer.i
    complex_vec_test.i
    constants.i
    feval.i
    ocvc.i
    oc_ctrlport.i
    oc_extras.i
    oc_intrusive_ptr.i
    oc_logger.i
    oc_shared_ptr.i
    oc_swig_block_magic.i
    oc_types.i
    hier_block2.i
    io_signature.i
    message.i
    msg_handler.i
    msg_queue.i
    pmt_swig.i
    prefs.i
    realtime.i
    single_threaded_scheduler.i
    sync_block.i
    sync_decimator.i
    sync_interpolator.i
    tagged_stream_block.i
    tags.i
    top_block.i
    ${CMAKE_CURRENT_BINARY_DIR}/runtime_swig_doc.i
    ${CMAKE_CURRENT_BINARY_DIR}/pmt_swig_doc.i
    DESTINATION ${OC_INCLUDE_DIR}/ocvc/swig
    COMPONENT "runtime_swig"
)
