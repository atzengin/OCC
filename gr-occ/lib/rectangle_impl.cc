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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ocvc/io_signature.h>
#include "rectangle_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    rectangle::sptr
    rectangle::make()
    {
      return ocvc::get_initial_sptr
        (new rectangle_impl());
    }

    static const int MIN_IN = 2;	// mininum number of input streams
    static const int MAX_IN = 2;	// maximum number of input streams
    static const int MIN_OUT = 1;	// minimum number of output streams
    static const int MAX_OUT = 1;	// maximum number of output streams

    /*
     * The private constructor
     */
    rectangle_impl::rectangle_impl()
      : oc::block("rectangle",
              oc::io_signature::make2(MIN_IN, MAX_IN, sizeof(cv::Mat), sizeof(cv::Rect)),
              oc::io_signature::make(MIN_OUT, MAX_OUT, sizeof(cv::Mat)))
    {

    }

    /*
     * Our virtual destructor.
     */
    rectangle_impl::~rectangle_impl()
    {
    }

    void
    rectangle_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = 1;
    }

    int
    rectangle_impl::general_work (int noutput_items,
                       oc_vector_int &ninput_items,
                       oc_vector_const_void_star &input_items,
                       oc_vector_void_star &output_items)
    {
      cv::Mat *in = (cv::Mat *) input_items[0];
      cv::Rect *rect = (cv::Rect *) input_items[1];
      cv::Mat *out = (cv::Mat *) output_items[0];

      cout<<"Rectangle : memcopy 1st"<<endl;
      memcpy(&d_img, in, sizeof(d_img));
      memcpy(&objectRect, rect, sizeof(objectRect));

      if(d_img.empty())
      {
          cout<<"Rectangle : Empty image!!!"<<endl;
          return 0;
      }
      else
      {
          // Check if an object was detected.
          if (objectRect.width > 0)
          {
              cv::rectangle(d_img, objectRect, CV_RGB(255, 255, 0), 2, CV_AA);

              cout<<"Rectangle : memcopy 2nd"<<endl;
              memcpy(out, &d_img, sizeof(output_img));

              consume_each (1);
              return 1;
          }
//          else
//          {
//              if (oldRect.width > 0) cv::rectangle(d_img, oldRect, CV_RGB(255, 255, 0), 2, CV_AA);

//              cout<<"Rectangle : memcopy 3rd"<<endl;
//              memcpy(out, &d_img, sizeof(output_img));

//              consume_each (1);
//              return 1;
//          }

      }
    }

  } /* namespace opencv */
} /* namespace oc */

