# Copyright 2011,2013 Free Software Foundation, Inc.
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

include(OcPython)

########################################################################
# Install python files
########################################################################
OC_PYTHON_INSTALL(FILES
    __init__.py
    pmt_to_python.py
    DESTINATION ${OC_PYTHON_DIR}/pmt
    COMPONENT "runtime_python"
)

########################################################################
# Setup unit tests
########################################################################
if(ENABLE_TESTING)
include(OcTest)
file(GLOB py_qa_test_files "qa_*.py")
foreach(py_qa_test_file ${py_qa_test_files})
    get_filename_component(py_qa_test_name ${py_qa_test_file} NAME_WE)
    set(OC_TEST_PYTHON_DIRS
        ${CMAKE_BINARY_DIR}/ocvc-runtime/python
        ${CMAKE_BINARY_DIR}/ocvc-runtime/swig
    )
    set(OC_TEST_TARGET_DEPS ocvc-runtime)
    OC_ADD_TEST(${py_qa_test_name} ${PYTHON_EXECUTABLE} ${PYTHON_DASH_B} ${py_qa_test_file})
endforeach(py_qa_test_file)
endif(ENABLE_TESTING)
