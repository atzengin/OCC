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

include(OcPython)

OC_PYTHON_INSTALL(PROGRAMS
  volk_math.py
  volk_plot.py
  volk_test_funcs.py
  volk_types.py
  DESTINATION ${OC_PKG_DATA_DIR}/examples/volk_benchmark
  COMPONENT "runtime_python"
)

install(
    FILES README
    DESTINATION ${OC_PKG_DATA_DIR}/examples/volk_benchmark
    COMPONENT "runtime_python"
)
