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


#ifndef INCLUDED_OPENCV_EQUALIZE_HISTOGRAM_H
#define INCLUDED_OPENCV_EQUALIZE_HISTOGRAM_H

#include <opencv/api.h>
#include <ocvc/block.h>

namespace oc {
  namespace opencv {

    /*!
     * \brief <+description of block+>
     * \ingroup opencv
     *
     */
    class OPENCV_API equalize_histogram : virtual public oc::block
    {
     public:
      typedef boost::shared_ptr<equalize_histogram> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of opencv::equalize_histogram.
       *
       * To avoid accidental use of raw pointers, opencv::equalize_histogram's
       * constructor is in a private implementation
       * class. opencv::equalize_histogram::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_EQUALIZE_HISTOGRAM_H */

