/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_OPENCV_CONVERT_COLOR_H
#define INCLUDED_OPENCV_CONVERT_COLOR_H

#include <opencv/api.h>
#include <ocvc/block.h>

namespace oc {
  namespace opencv {

    /*!
     * \brief <+description of block+>
     * \ingroup opencv
     *
     */
    class OPENCV_API convert_color : virtual public oc::block
    {
     public:
      typedef boost::shared_ptr<convert_color> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of opencv::convert_color.
       *
       * To avoid accidental use of raw pointers, opencv::convert_color's
       * constructor is in a private implementation
       * class. opencv::convert_color::make is the public interface for
       * creating new instances.
       */
      static sptr make(int code);
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_CONVERT_COLOR_H */

