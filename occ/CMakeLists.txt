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

########################################################################
# Setup dependencies
########################################################################
include(OcPython)

OC_PYTHON_CHECK_MODULE("python >= 2.5"     sys          "sys.version.split()[0] >= '2.5'"           PYTHON_MIN_VER_FOUND)
OC_PYTHON_CHECK_MODULE("Cheetah >= 2.0.0"  Cheetah      "Cheetah.Version >= '2.0.0'"                CHEETAH_FOUND)
OC_PYTHON_CHECK_MODULE("lxml >= 1.3.6"     lxml.etree   "lxml.etree.LXML_VERSION >= (1, 3, 6, 0)"   LXML_FOUND)
OC_PYTHON_CHECK_MODULE("pygtk >= 2.10.0"   gtk          "gtk.pygtk_version >= (2, 10, 0)"           PYGTK_FOUND)
OC_PYTHON_CHECK_MODULE("numpy"             numpy        True                                        NUMPY_FOUND)

########################################################################
# Register component
########################################################################
include(OcComponent)
if(NOT CMAKE_CROSSCOMPILING)
    set(occ_python_deps
        PYTHON_MIN_VER_FOUND
        CHEETAH_FOUND
        LXML_FOUND
        PYGTK_FOUND
        NUMPY_FOUND
    )
endif(NOT CMAKE_CROSSCOMPILING)

OC_REGISTER_COMPONENT("ocvc-companion" ENABLE_OCC
    ENABLE_OCVC_RUNTIME
    ENABLE_PYTHON
    ${occ_python_deps}
)

########################################################################
# Begin conditional configuration
########################################################################
if(ENABLE_OCC)

########################################################################
# Setup CPack components
########################################################################
include(OcPackage)
CPACK_COMPONENT("occ"
    DISPLAY_NAME "OpenCv Companion Companion"
    DESCRIPTION  "Graphical flow graph designer"
    DEPENDS      "runtime_python"
)

########################################################################
# Create and install the occ conf file
########################################################################
file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${OCC_BLOCKS_DIR} blocksdir)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/occ.conf.in
    ${CMAKE_CURRENT_BINARY_DIR}/occ.conf
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/occ.conf
    DESTINATION ${OC_PREFSDIR}
    COMPONENT "occ"
)

OC_PYTHON_INSTALL(
    FILES __init__.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/occ
    COMPONENT "occ"
)

########################################################################
# Appens NSIS commands to set environment variables
########################################################################
if(WIN32)

file(TO_NATIVE_PATH ${OC_PKG_DOC_DIR} OC_DOC_DIR)
string(REPLACE "\\" "\\\\" OC_DOC_DIR ${OC_DOC_DIR})

file(TO_NATIVE_PATH ${OCC_BLOCKS_DIR} OCC_BLOCKS_PATH)
string(REPLACE "\\" "\\\\" OCC_BLOCKS_PATH ${OCC_BLOCKS_PATH})

file(TO_NATIVE_PATH ${OC_PYTHON_DIR} OC_PYTHON_POSTFIX)
string(REPLACE "\\" "\\\\" OC_PYTHON_POSTFIX ${OC_PYTHON_POSTFIX})

CPACK_SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "${CPACK_NSIS_EXTRA_INSTALL_COMMANDS}
    #!include \\\"winmessages.nsh\\\"
    WriteRegStr HKLM ${HLKM_ENV} \\\"OCC_BLOCKS_PATH\\\" \\\"$INSTDIR\\\\${OCC_BLOCKS_PATH}\\\"
    SendMessage \\\${HWND_BROADCAST} \\\${WM_WININICHANGE} 0 \\\"STR:Environment\\\" /TIMEOUT=5000
")

CPACK_SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "${CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS}
    #!include \\\"winmessages.nsh\\\"
    DeleteRegValue HKLM ${HLKM_ENV} \\\"OCC_BLOCKS_PATH\\\"
    SendMessage \\\${HWND_BROADCAST} \\\${WM_WININICHANGE} 0 \\\"STR:Environment\\\" /TIMEOUT=5000
")

endif(WIN32)

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(base)
add_subdirectory(blocks)
add_subdirectory(freedesktop)
add_subdirectory(occ_ocvc)
add_subdirectory(gui)
add_subdirectory(python)
add_subdirectory(scripts)
add_subdirectory(examples)

endif(ENABLE_OCC)
