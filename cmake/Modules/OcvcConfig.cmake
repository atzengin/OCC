# Copyright 2013 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

INCLUDE(FindPkgConfig)
INCLUDE(FindPackageHandleStandardArgs)

# if OC_REQUIRED_COMPONENTS is not defined, it will be set to the following list (all of them)
if(NOT OC_REQUIRED_COMPONENTS)
  set(OC_REQUIRED_COMPONENTS RUNTIME ANALOG BLOCKS DIGITAL FFT FILTER PMT)
endif()

set(OCVC_ALL_LIBRARIES "")
set(OCVC_ALL_INCLUDE_DIRS "")

MACRO(LIST_CONTAINS var value)
  SET(${var})
  FOREACH(value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} TRUE)
    ENDIF(${value} STREQUAL ${value2})
  ENDFOREACH(value2)
ENDMACRO(LIST_CONTAINS)

function(OC_MODULE EXTVAR PCNAME INCFILE LIBFILE)

    LIST_CONTAINS(REQUIRED_MODULE ${EXTVAR} ${OC_REQUIRED_COMPONENTS})
    if(NOT REQUIRED_MODULE)
        #message("Ignoring GNU Radio Module ${EXTVAR}")
        return()
    endif()

    message("Checking for GNU Radio Module: ${EXTVAR}")

    # check for .pc hints
    PKG_CHECK_MODULES(PC_OCVC_${EXTVAR} ${PCNAME})

    set(INCVAR_NAME "OCVC_${EXTVAR}_INCLUDE_DIRS")
    set(LIBVAR_NAME "OCVC_${EXTVAR}_LIBRARIES")
    set(PC_INCDIR ${PC_OCVC_${EXTVAR}_INCLUDEDIR})
    set(PC_LIBDIR ${PC_OCVC_${EXTVAR}_LIBDIR})

    # look for include files
    FIND_PATH(
        ${INCVAR_NAME}
        NAMES ${INCFILE}
        HINTS $ENV{OCVC_RUNTIME_DIR}/include
            ${PC_INCDIR}
            ${CMAKE_INSTALL_PREFIX}/include
        PATHS /usr/local/include
              /usr/include
    )

    # look for libs
    FIND_LIBRARY(
        ${LIBVAR_NAME}
        NAMES ${LIBFILE}
        HINTS $ENV{OCVC_RUNTIME_DIR}/lib
            ${PC_LIBDIR}
            ${CMAKE_INSTALL_PREFIX}/lib/
            ${CMAKE_INSTALL_PREFIX}/lib64/
        PATHS /usr/local/lib
              /usr/local/lib64
              /usr/lib
              /usr/lib64
    )

    # show results
    message(" * INCLUDES=${OCVC_${EXTVAR}_INCLUDE_DIRS}")
    message(" * LIBS=${OCVC_${EXTVAR}_LIBRARIES}")

    # append to all includes and libs list
    LIST(APPEND OCVC_ALL_INCLUDE_DIRS ${OCVC_${EXTVAR}_INCLUDE_DIRS})
    LIST(APPEND OCVC_ALL_LIBRARIES ${OCVC_${EXTVAR}_LIBRARIES})

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(OCVC_${EXTVAR} DEFAULT_MSG OCVC_${EXTVAR}_LIBRARIES OCVC_${EXTVAR}_INCLUDE_DIRS)
    message("OCVC_${EXTVAR}_FOUND = ${OCVC_${EXTVAR}_FOUND}")
    set(OCVC_${EXTVAR}_FOUND ${OCVC_${EXTVAR}_FOUND} PARENT_SCOPE)

    # generate an error if the module is missing
    if(NOT OCVC_${EXTVAR}_FOUND)
       message(FATAL_ERROR "Required GNU Radio Component: ${EXTVAR} missing!")
    endif()

    MARK_AS_ADVANCED(OCVC_${EXTVAR}_LIBRARIES OCVC_${EXTVAR}_INCLUDE_DIRS)

endfunction()

OC_MODULE(RUNTIME ocvc-runtime ocvc/top_block.h ocvc-runtime)
OC_MODULE(ANALOG ocvc-analog ocvc/analog/api.h ocvc-analog)
OC_MODULE(ATSC ocvc-atsc ocvc/atsc/api.h ocvc-atsc)
OC_MODULE(AUDIO ocvc-audio ocvc/audio/api.h ocvc-audio)
OC_MODULE(BLOCKS ocvc-blocks ocvc/blocks/api.h ocvc-blocks)
OC_MODULE(CHANNELS ocvc-channels ocvc/channels/api.h ocvc-channels)
OC_MODULE(DIGITAL ocvc-digital ocvc/digital/api.h ocvc-digital)
OC_MODULE(FCD ocvc-fcd ocvc/fcd_api.h ocvc-fcd)
OC_MODULE(FEC ocvc-fec ocvc/fec/api.h ocvc-fec)
OC_MODULE(FFT ocvc-fft ocvc/fft/api.h ocvc-fft)
OC_MODULE(FILTER ocvc-filter ocvc/filter/api.h ocvc-filter)
OC_MODULE(NOAA ocvc-noaa ocvc/noaa/api.h ocvc-noaa)
OC_MODULE(PAGER ocvc-pager ocvc/pager/api.h ocvc-pager)
OC_MODULE(QTGUI ocvc-qtgui ocvc/qtgui/api.h ocvc-qtgui)
OC_MODULE(TRELLIS ocvc-trellis ocvc/trellis/api.h ocvc-trellis)
OC_MODULE(UHD ocvc-uhd ocvc/uhd/api.h ocvc-uhd)
OC_MODULE(VOCODER ocvc-vocoder ocvc/vocoder/api.h ocvc-vocoder)
OC_MODULE(WAVELET ocvc-wavelet ocvc/wavelet/api.h ocvc-wavelet)
OC_MODULE(WXGUI ocvc-wxgui ocvc/wxgui/api.h ocvc-wxgui)
OC_MODULE(PMT ocvc-runtime pmt/pmt.h ocvc-pmt)
