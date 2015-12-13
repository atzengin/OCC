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

EXECUTE_PROCESS(
  COMMAND ${ICE_SLICE2PY} -I${CMAKE_SOURCE_DIR}/ocvc-runtime/lib/controlport
          --output-dir=${CMAKE_BINARY_DIR}/ocvc-runtime/python
          ${CMAKE_SOURCE_DIR}/ocvc-runtime/lib/controlport/ocvc.ice
)

EXECUTE_PROCESS(
  COMMAND ${ICE_SLICE2PY} -I${CMAKE_SOURCE_DIR}/ocvc-runtime/lib/controlport
          --output-dir=${CMAKE_BINARY_DIR}/ocvc-runtime/python
          ${CMAKE_SOURCE_DIR}/ocvc-runtime/lib/controlport/frontend.ice
)

EXECUTE_PROCESS(
  COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/ocvc-runtime/python/ocvc/__init__.py
)

OC_PYTHON_INSTALL(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py
    ${CMAKE_CURRENT_SOURCE_DIR}/IceRadioClient.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/ctrlport/
    COMPONENT "runtime_python"
)

# We don't want to install these in the root Python directory, but we
# aren't given a choice based on the way slice2py generates the
# information.
OC_PYTHON_INSTALL(
    FILES
    ${CMAKE_BINARY_DIR}/ocvc-runtime/python/ocvc_ice.py
    ${CMAKE_BINARY_DIR}/ocvc-runtime/python/frontend_ice.py
    DESTINATION ${OC_PYTHON_DIR}
    COMPONENT "runtime_python"
)

OC_PYTHON_INSTALL(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/OCvC/__init__.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/ctrlport/OCvC
    COMPONENT "runtime_python"
)

OC_PYTHON_INSTALL(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/OCvC/Booter/__init__.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/ctrlport/OCvC/Booter
    COMPONENT "runtime_python"
)

OC_PYTHON_INSTALL(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/OCvC/Frontend/__init__.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/ctrlport/OCvC/Frontend
    COMPONENT "runtime_python"
)

install(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/icon.png
    DESTINATION ${OC_PYTHON_DIR}/ocvc/ctrlport
    COMPONENT "runtime_python"
)

OC_PYTHON_INSTALL(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/OcDataPlotter.py
    ${CMAKE_CURRENT_SOURCE_DIR}/monitor.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/ctrlport/
    COMPONENT "runtime_python"
)

OC_PYTHON_INSTALL(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/oc-ctrlport-monitor
    ${CMAKE_CURRENT_SOURCE_DIR}/oc-perf-monitorx
    ${CMAKE_CURRENT_SOURCE_DIR}/oc-ctrlport-curses
    DESTINATION ${OC_RUNTIME_DIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE 
    COMPONENT "runtime_python"
)
