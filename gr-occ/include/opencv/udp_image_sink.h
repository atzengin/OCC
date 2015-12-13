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


#ifndef INCLUDED_OPENCV_UDP_IMAGE_SINK_H
#define INCLUDED_OPENCV_UDP_IMAGE_SINK_H

#include <opencv/api.h>
#include <ocvc/sync_block.h>

namespace oc {
  namespace opencv {

    /*!
     * \brief <+description of block+>
     * \ingroup opencv
     *
     */
    class OPENCV_API udp_image_sink : virtual public oc::sync_block
    {
     public:
      typedef boost::shared_ptr<udp_image_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of opencv::udp_image_sink.
       *
       * To avoid accidental use of raw pointers, opencv::udp_image_sink's
       * constructor is in a private implementation
       * class. opencv::udp_image_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t itemsize,
                       const std::string &host, int port,
                       int payload_size=1472, bool eof=true);

      /*! \brief return the PAYLOAD_SIZE of the socket */
      virtual int payload_size() = 0;

      /*! \brief Change the connection to a new destination
       *
       * \param host         The name or IP address of the receiving host; use
       *                     NULL or None to break the connection without closing
       * \param port         Destination port to connect to on receiving host
       *
       * Calls disconnect() to terminate any current connection first.
       */
      virtual void connect(const std::string &host, int port) = 0;

      /*! \brief Send zero-length packet (if eof is requested) then stop sending
       *
       * Zero-byte packets can be interpreted as EOF by gr_udp_source.
       * Note that disconnect occurs automatically when the sink is
       * destroyed, but not when its top_block stops.*/
      virtual void disconnect() = 0;

    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_UDP_IMAGE_SINK_H */

