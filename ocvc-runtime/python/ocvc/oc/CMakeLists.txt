# Copyright 2012 Free Software Foundation, Inc.
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
include(OcPython)

OC_PYTHON_INSTALL(FILES
    __init__.py
    tag_utils.py
    gateway.py
    oc_threading.py
    oc_threading_23.py
    oc_threading_24.py
    hier_block2.py
    top_block.py
    pubsub.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/gr
    COMPONENT "runtime_python"
)

########################################################################
# Handle the unit tests
########################################################################
if(ENABLE_TESTING)
  set(OC_TEST_TARGET_DEPS "")
  set(OC_TEST_LIBRARY_DIRS "")
  set(OC_TEST_PYTHON_DIRS
    ${CMAKE_BINARY_DIR}/gruel/src/python
    ${CMAKE_BINARY_DIR}/ocvc-runtime/python
    )
  include(OcTest)
  file(GLOB py_qa_test_files "qa_*.py")
  foreach(py_qa_test_file ${py_qa_test_files})
    get_filename_component(py_qa_test_name ${py_qa_test_file} NAME_WE)
    OC_ADD_TEST(${py_qa_test_name} ${PYTHON_EXECUTABLE} ${PYTHON_DASH_B} ${py_qa_test_file})
  endforeach(py_qa_test_file)
endif(ENABLE_TESTING)
