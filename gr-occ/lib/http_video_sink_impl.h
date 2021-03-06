/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_OPENCV_HTTP_VIDEO_SINK_IMPL_H
#define INCLUDED_OPENCV_HTTP_VIDEO_SINK_IMPL_H

#include <opencv/http_video_sink.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "streamer/mjpeg_server.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/swap.hpp>

namespace oc {
  namespace opencv {

    class http_video_sink_impl : public http_video_sink
    {
     private:
      cv::Mat d_img;
      http::server::streamer_ptr stmr;
      http::server::server_ptr s;

     public:
      http_video_sink_impl(const char *ip, int port);
      ~http_video_sink_impl();

      // Where all the action really happens
      void forecast (int noutput_items, oc_vector_int &ninput_items_required);
      
      // Where all the action really happens
      int work(int noutput_items,
	       oc_vector_const_void_star &input_items,
	       oc_vector_void_star &output_items);
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_HTTP_VIDEO_SINK_IMPL_H */

