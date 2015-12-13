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


#ifndef INCLUDED_OPENCV_DETECT_OBJECT_H
#define INCLUDED_OPENCV_DETECT_OBJECT_H

#include <opencv/api.h>
#include <ocvc/block.h>

namespace oc {
  namespace opencv {

    /*!
     * \brief <+description of block+>
     * \ingroup opencv
     *
     */
    class OPENCV_API detect_object : virtual public oc::block
    {
     public:
      typedef boost::shared_ptr<detect_object> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of opencv::detect_object.
       *
       * To avoid accidental use of raw pointers, opencv::detect_object's
       * constructor is in a private implementation
       * class. opencv::detect_object::make is the public interface for
       * creating new instances.
       */
      static sptr make(const char *cascadeFilename, int minFeatureSize, int scaledWidth);
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_DETECT_OBJECT_H */

