# Copyright 2011,2012 Free Software Foundation, Inc.
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

########################################################################
# Register component
########################################################################
include(OcComponent)
OC_REGISTER_COMPONENT("oc-utils" ENABLE_OC_UTILS
    ENABLE_OCVC_RUNTIME
    ENABLE_PYTHON
)

########################################################################
# Begin conditional configuration
########################################################################
if(ENABLE_OC_UTILS)

########################################################################
# Setup CPack components
########################################################################
include(OcPackage)
CPACK_COMPONENT("utils"
    DISPLAY_NAME "Utils"
    DESCRIPTION  "Misc ocvc python utilities"
    DEPENDS      "runtime_python"
)

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(python/utils)
add_subdirectory(python/modtool)


endif(ENABLE_OC_UTILS)
