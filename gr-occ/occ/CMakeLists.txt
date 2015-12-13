# Copyright 2011 Free Software Foundation, Inc.
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
install(FILES
    opencv_video_source.xml
    opencv_video_write.xml
    opencv_image_sink.xml
    opencv_image_source.xml
    opencv_image_write.xml
    opencv_udp_image_source.xml
    opencv_udp_image_sink.xml
    opencv_convert_color.xml
    opencv_detect_object.xml
    opencv_equalize_histogram.xml
    opencv_rectangle.xml
    opencv_video_sink.xml
    opencv_resize_image.xml
    opencv_http_video_sink.xml DESTINATION share/ocvc/occ/blocks
)
