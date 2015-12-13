# Copyright 2010-2013 Free Software Foundation, Inc.
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
# This file included, use CMake directory variables
########################################################################
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

########################################################################
# Generate serial tags header file
########################################################################

get_filename_component(PMT_SERIAL_TAGS_H
    ${CMAKE_CURRENT_BINARY_DIR}/../../include/pmt/pmt_serial_tags.h ABSOLUTE
)

add_custom_command(
    OUTPUT ${PMT_SERIAL_TAGS_H}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gen-serial-tags.py
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/pmt-serial-tags.scm
    COMMAND ${PYTHON_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/gen-serial-tags.py
        ${CMAKE_CURRENT_SOURCE_DIR}/pmt-serial-tags.scm
        ${PMT_SERIAL_TAGS_H}
)

install(
    FILES ${PMT_SERIAL_TAGS_H}
    DESTINATION ${OC_INCLUDE_DIR}/pmt
    COMPONENT "runtime_devel"
)

include(AddFileDependencies)
ADD_FILE_DEPENDENCIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/pmt_serialize.cc
    ${PMT_SERIAL_TAGS_H}
)

########################################################################
# Generate other pmt stuff
########################################################################
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/pmt_unv_int.h
        ${CMAKE_CURRENT_BINARY_DIR}/qa_pmt_unv.h
        ${CMAKE_CURRENT_BINARY_DIR}/pmt_unv.cc
        ${CMAKE_CURRENT_BINARY_DIR}/qa_pmt_unv.cc
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/generate_unv.py
        ${CMAKE_CURRENT_SOURCE_DIR}/unv_template.h.t
        ${CMAKE_CURRENT_SOURCE_DIR}/unv_template.cc.t
        ${CMAKE_CURRENT_SOURCE_DIR}/unv_qa_template.cc.t
    COMMAND ${PYTHON_EXECUTABLE} ${PYTHON_DASH_B} -c
    \"import os,sys\;srcdir='${CMAKE_CURRENT_SOURCE_DIR}'\;sys.path.append(srcdir)\;os.environ['srcdir']=srcdir\;from generate_unv import main\;main()\"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

set(pmt_sources
  ${CMAKE_CURRENT_BINARY_DIR}/pmt_unv.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/pmt.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/pmt_io.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/pmt_pool.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/pmt_serialize.cc
)

list(APPEND ocvc_pmt_libs
    ${Boost_LIBRARIES}
    ${LOG4CPP_LIBRARIES}
)

add_custom_target(pmt_generated 
  DEPENDS ${PMT_SERIAL_TAGS_H} ${CMAKE_CURRENT_BINARY_DIR}/pmt_unv_int.h)


#Add Windows DLL resource file if using MSVC
if(MSVC)
    include(${CMAKE_SOURCE_DIR}/cmake/Modules/OcVersion.cmake)

    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/ocvc-pmt.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/ocvc-pmt.rc
    @ONLY)

    list(APPEND oc_pmt_sources
        ${CMAKE_CURRENT_BINARY_DIR}/ocvc-pmt.rc
    )
endif(MSVC)


add_library(ocvc-pmt SHARED ${pmt_sources})
target_link_libraries(ocvc-pmt ${ocvc_pmt_libs})

OC_LIBRARY_FOO(ocvc-pmt RUNTIME_COMPONENT "runtime_runtime" DEVEL_COMPONENT "runtime_devel")

add_dependencies(ocvc-pmt
  pmt_generated
)

########################################################################
# Setup tests
########################################################################
if(ENABLE_TESTING)
include(OcTest)

########################################################################
# Append ocvc-runtime test sources
########################################################################
list(APPEND test_ocvc_pmt_sources
  qa_pmt.cc
  qa_pmt_prims.cc
  ${CMAKE_CURRENT_BINARY_DIR}/qa_pmt_unv.cc
)

include_directories(${CPPUNIT_INCLUDE_DIRS})
link_directories(${CPPUNIT_LIBRARY_DIRS})

add_library(test-ocvc-pmt SHARED ${test_ocvc_pmt_sources})
target_link_libraries(test-ocvc-pmt ocvc-runtime ocvc-pmt 
  ${CPPUNIT_LIBRARIES} ${Boost_LIBRARIES} ${LOG4CPP_LIBRARIES})

########################################################################
# Build the test executable
# Set the test environment so the build libs will be found under MSVC.
########################################################################
list(APPEND OC_TEST_TARGET_DEPS test-ocvc-pmt)
add_executable(oc_pmt_test test_pmt.cc)
target_link_libraries(oc_pmt_test test-ocvc-pmt)
OC_ADD_TEST(oc-pmt-test oc_pmt_test)

endif(ENABLE_TESTING)
