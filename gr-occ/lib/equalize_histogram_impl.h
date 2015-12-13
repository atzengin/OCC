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

#ifndef INCLUDED_OPENCV_EQUALIZE_HISTOGRAM_IMPL_H
#define INCLUDED_OPENCV_EQUALIZE_HISTOGRAM_IMPL_H

#include <opencv/equalize_histogram.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace oc {
  namespace opencv {

    class equalize_histogram_impl : public equalize_histogram
    {
     private:
      cv::Mat d_img, output_img;	// Image to be processed

     public:
      equalize_histogram_impl();
      ~equalize_histogram_impl();

      // Where all the action really happens
      void forecast (int noutput_items, oc_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       oc_vector_int &ninput_items,
		       oc_vector_const_void_star &input_items,
		       oc_vector_void_star &output_items);
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_EQUALIZE_HISTOGRAM_IMPL_H */

