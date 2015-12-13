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

########################################################################
# Install python files and apps
########################################################################
include(OcPython)

OC_PYTHON_INSTALL(
    FILES
    plot_data.py
    plot_fft_base.py
    plot_psd_base.py
    pyqt_plot.py
    pyqt_filter.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc
    COMPONENT "utils"
)

OC_PYTHON_INSTALL(
    PROGRAMS
    oc_modtool
    oc_plot_char
    oc_plot_const
    oc_plot_fft
    oc_plot_fft_c
    oc_plot_fft_f
    oc_plot_psd
    oc_plot_psd_c
    oc_plot_psd_f
    oc_plot_float
    oc_plot_int
    oc_plot_iq
    oc_plot_short
    oc_plot_qt
    oc_read_file_metadata
    occc
    DESTINATION ${OC_RUNTIME_DIR}
    COMPONENT "utils"
)
