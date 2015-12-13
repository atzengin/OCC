# Copyright 2011-2012 Free Software Foundation, Inc.
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
set(occ_freedesktop_path ${OC_PKG_DATA_DIR}/occ/freedesktop)

install(FILES
    occ-icon-256.png
    occ-icon-128.png
    occ-icon-64.png
    occ-icon-48.png
    occ-icon-32.png
    ocvc-occ.xml
    ocvc-occ.desktop
    DESTINATION ${occ_freedesktop_path}
    COMPONENT "occ"
)

find_program(HAVE_XDG_UTILS xdg-desktop-menu)

if(UNIX AND HAVE_XDG_UTILS)
    set(SRCDIR ${CMAKE_INSTALL_PREFIX}/${occ_freedesktop_path})
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/occ_setup_freedesktop.in
        ${CMAKE_CURRENT_BINARY_DIR}/occ_setup_freedesktop
    @ONLY)
    install(
        PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/occ_setup_freedesktop
        DESTINATION ${OC_PKG_LIBEXEC_DIR} COMPONENT "occ"
    )
endif(UNIX AND HAVE_XDG_UTILS)
