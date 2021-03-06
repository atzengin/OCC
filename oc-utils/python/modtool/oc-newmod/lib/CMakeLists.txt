# Copyright 2011,2012 Free Software Foundation, Inc.
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

########################################################################
# Setup library
########################################################################
include(OcPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND howto_sources
)

add_library(ocvc-howto SHARED ${howto_sources})
target_link_libraries(ocvc-howto ${Boost_LIBRARIES} ${OCVC_RUNTIME_LIBRARIES})
set_target_properties(ocvc-howto PROPERTIES DEFINE_SYMBOL "ocvc_howto_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS ocvc-howto
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(OcTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_howto_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_howto.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_howto.cc
)

add_executable(test-howto ${test_howto_sources})

target_link_libraries(
  test-howto
  ${OCVC_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  ocvc-howto
)

OC_ADD_TEST(test_howto test-howto)
