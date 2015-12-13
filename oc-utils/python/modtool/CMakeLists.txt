# Copyright 2011 Free Software Foundation, Inc.
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

OC_PYTHON_INSTALL(FILES
    __init__.py
    cmakefile_editor.py
    code_generator.py
    occ_xml_generator.py
    modtool_add.py
    modtool_base.py
    modtool_disable.py
    modtool_help.py
    modtool_info.py
    modtool_makexml.py
    modtool_newmod.py
    modtool_rm.py
    parser_cc_block.py
    templates.py
    util_functions.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/modtool
    COMPONENT "utils"
)

set(OC_PKG_MODTOOL_DATA_DIR ${OC_PKG_DATA_DIR}/modtool)
install(DIRECTORY oc-newmod
    DESTINATION ${OC_PKG_MODTOOL_DATA_DIR}
    COMPONENT "utils"
)


########################################################################
# Create and install the modtool conf file
########################################################################
file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${OC_PKG_MODTOOL_DATA_DIR}/oc-newmod newmoddir)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/modtool.conf.in
    ${CMAKE_CURRENT_BINARY_DIR}/modtool.conf
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/modtool.conf
    DESTINATION ${OC_PREFSDIR}
    COMPONENT "utils"
)

