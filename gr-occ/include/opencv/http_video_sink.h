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


#ifndef INCLUDED_OPENCV_HTTP_VIDEO_SINK_H
#define INCLUDED_OPENCV_HTTP_VIDEO_SINK_H

#include <opencv/api.h>
#include <ocvc/sync_block.h>

namespace oc {
  namespace opencv {

    /*!
     * \brief <+description of block+>
     * \ingroup opencv
     *
     */
    class OPENCV_API http_video_sink : virtual public oc::sync_block
    {
     public:
      typedef boost::shared_ptr<http_video_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of opencv::http_video_sink.
       *
       * To avoid accidental use of raw pointers, opencv::http_video_sink's
       * constructor is in a private implementation
       * class. opencv::http_video_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(const char *ip="0.0.0.0", int port=9090);
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_HTTP_VIDEO_SINK_H */

