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

# Added stream code
add_subdirectory(json_spirit)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND opencv_sources
    video_source_impl.cc
    video_write_impl.cc
    image_sink_impl.cc
    image_source_impl.cc
    image_write_impl.cc
    udp_image_source_impl.cc
    udp_image_sink_impl.cc
    convert_color_impl.cc
    detect_object_impl.cc
    equalize_histogram_impl.cc
    rectangle_impl.cc
    video_sink_impl.cc
    resize_image_impl.cc
    http_video_sink_impl.cc )

add_library(ocvc-opencv SHARED 
  ${opencv_sources}
  connection.cpp
  mime_types.cpp
  reply.cpp
  request_handler.cpp
  request_parser.cpp
  server.cpp
  mjpeg_server.cpp)
target_link_libraries(ocvc-opencv ${Boost_LIBRARIES} boost_thread boost_system boost_regex ${OCVC_RUNTIME_LIBRARIES} ${OpenCV_LIBS})
set_target_properties(ocvc-opencv PROPERTIES DEFINE_SYMBOL "ocvc_opencv_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS ocvc-opencv
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
# Test code removed
#include(OcTest)

#include_directories(${CPPUNIT_INCLUDE_DIRS})

#list(APPEND test_opencv_sources
#    ${CMAKE_CURRENT_SOURCE_DIR}/test_opencv.cc
#    ${CMAKE_CURRENT_SOURCE_DIR}/qa_opencv.cc
#)

#add_executable(test-opencv ${test_opencv_sources})
#
#target_link_libraries(
#  test-opencv
#  ${OCVC_RUNTIME_LIBRARIES}
#  ${Boost_LIBRARIES}
#  ${CPPUNIT_LIBRARIES}
#  ocvc-opencv
#)

#OC_ADD_TEST(test_opencv test-opencv)
