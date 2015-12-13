# Copyright 2010-2011,2013 Free Software Foundation, Inc.
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
# Setup the include and linker paths
########################################################################
include_directories(
  ${OCVC_RUNTIME_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

link_directories(
  ${Boost_LIBRARY_DIRS}
)

########################################################################
# Setup executables
########################################################################
add_executable(ocvc-config-info ocvc-config-info.cc)
target_link_libraries(ocvc-config-info ocvc-runtime ${Boost_LIBRARIES})
install(
    TARGETS ocvc-config-info
    DESTINATION ${OC_RUNTIME_DIR}
    COMPONENT "runtime_runtime"
)
