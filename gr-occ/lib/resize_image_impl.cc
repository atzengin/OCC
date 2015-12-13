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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ocvc/io_signature.h>
#include "resize_image_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    resize_image::sptr
    resize_image::make(int width, int height, double fx, double fy, int interpolation)
    {
      return ocvc::get_initial_sptr
        (new resize_image_impl(width, height, fx, fy, interpolation));
    }

    static const int MIN_IN = 1;	// mininum number of input streams
    static const int MAX_IN = 1;	// maximum number of input streams
    static const int MIN_OUT = 1;	// minimum number of output streams
    static const int MAX_OUT = 1;	// maximum number of output streams

    /*
     * The private constructor
     */
    resize_image_impl::resize_image_impl(int width, int height, double fx, double fy, int interpolation)
      : oc::block("resize_image",
                  oc::io_signature::make(MIN_IN, MAX_IN, sizeof(cv::Mat)),
                  oc::io_signature::make(MIN_OUT, MAX_OUT, sizeof(cv::Mat)))
    {
      d_fx = fx;
      d_fy = fy;
      d_width = width;
      d_height = height;
      d_interpolation = interpolation;
    }

    /*
     * Our virtual destructor.
     */
    resize_image_impl::~resize_image_impl()
    {
      d_img.release();
      d_resizedImg.release();
    }

    void
    resize_image_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = 1;
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    resize_image_impl::general_work (int noutput_items,
                       oc_vector_int &ninput_items,
                       oc_vector_const_void_star &input_items,
                       oc_vector_void_star &output_items)
    {
        cv::Mat *in = (cv::Mat *) input_items[0];
        cv::Mat *out = (cv::Mat *) output_items[0];

        cout<<"Resize : memcopy 1st"<<endl;
        memcpy(&d_img, in, sizeof(d_img));

        cout<<"Resize : image size    : "<<sizeof(d_img)<<endl;
        cout<<"Resize : noutput_items : "<<noutput_items<<endl;

        if(d_img.empty())
        {
            cout<<"Resize : Empty image!!!"<<endl;
            // Tell runtime system how many output items we produced.
            return 0;
        }
        else
        {
            cout<<"Resize : resizing image"<<endl;

            if(d_fx == 0.0 || d_fy == 0.0)
            {
              resize(d_img, d_resizedImg, Size(d_width, d_height), 0, 0, d_interpolation);
            }
            else if(d_width == 0 || d_height == 0)
            {
                  resize(d_img, d_resizedImg, Size(), d_fx, d_fy, d_interpolation);

//                if(d_height == 0 && d_width != 0)
//                {
//                    float scale = d_img.cols / (float)d_width;
//                    d_height = cvRound(d_img.rows / scale);
//                    resize(d_img, d_resizedImg, Size(d_width, d_height), 0, 0, d_interpolation);
//                }
//                else if(d_width == 0 && d_height != 0)
//                {
//                    float scale = d_img.rows / (float)d_height;
//                    d_width = cvRound(d_img.cols / scale);
//                    resize(d_img, d_resizedImg, Size(d_width, d_height), 0, 0, d_interpolation);
//                }
//                else
//                {
//                    resize(d_img, d_resizedImg, Size(), d_fx, d_fy, d_interpolation);
//                }

            }

            if(d_resizedImg.empty())
            {
              cout<<"Resize : image empty"<<endl;
              return 0;
            }
            else
            {
              cout<<"Resize : memcopy 2nd"<<endl;
              memcpy(out, &d_resizedImg, sizeof(d_resizedImg));

              // Tell runtime system how many input items we consumed on
              // each input stream.
              consume_each (1);
              // Tell runtime system how many output items we produced.
              return 1;
            }
        }
      }

  } /* namespace opencv */
} /* namespace oc */

