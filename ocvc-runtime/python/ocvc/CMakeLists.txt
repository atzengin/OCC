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

add_subdirectory(oc)
add_subdirectory(gru)

if(ENABLE_OC_CTRLPORT)
  add_subdirectory(ctrlport)
endif(ENABLE_OC_CTRLPORT)

OC_PYTHON_INSTALL(FILES
    __init__.py
    eng_notation.py
    eng_option.py
    oc_unittest.py
    oc_xmlrunner.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc
    COMPONENT "runtime_python"
)
