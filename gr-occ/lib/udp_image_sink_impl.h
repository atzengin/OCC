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

#ifndef INCLUDED_OPENCV_UDP_IMAGE_SINK_IMPL_H
#define INCLUDED_OPENCV_UDP_IMAGE_SINK_IMPL_H

#include <opencv/udp_image_sink.h>
#include <boost/asio.hpp>

namespace oc {
  namespace opencv {

    class udp_image_sink_impl : public udp_image_sink
    {
     private:
        size_t d_itemsize;

              int    d_payload_size;    // maximum transmission unit (packet length)
              bool   d_eof;             // send zero-length packet on disconnect
              bool   d_connected;       // are we connected?
              oc::thread::mutex  d_mutex;    // protects d_socket and d_connected

              boost::asio::ip::udp::socket *d_socket;          // handle to socket
              boost::asio::ip::udp::endpoint d_endpoint;
              boost::asio::io_service d_io_service;

     public:
      udp_image_sink_impl(size_t itemsize,
                          const std::string &host, int port,
                          int payload_size, bool eof);
      ~udp_image_sink_impl();

      int payload_size() { return d_payload_size; }

      void connect(const std::string &host, int port);
      void disconnect();

      // Where all the action really happens
      int work(int noutput_items,
	       oc_vector_const_void_star &input_items,
	       oc_vector_void_star &output_items);
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_UDP_IMAGE_SINK_IMPL_H */

