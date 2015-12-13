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

# SIMPLE
install(
    FILES
    simple/variable_config.occ
    DESTINATION ${OC_PKG_DATA_DIR}/examples/occ/simple
    COMPONENT "occ"
)

# XMLRPC
install(
    FILES
    xmlrpc/readme.txt
    xmlrpc/xmlrpc_client.occ
    xmlrpc/xmlrpc_client_script.py
    xmlrpc/xmlrpc_server.occ
    DESTINATION ${OC_PKG_DATA_DIR}/examples/occ/xmlrpc
    COMPONENT "occ"
)
