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
// If the input image is not grayscale, then convert the BGR or BGRA color image to grayscale.

//Mat gray;
//if (img.channels() == 3) {
//    cvtColor(img, gray, CV_BGR2GRAY);
//}
//else if (img.channels() == 4) {
//    cvtColor(img, gray, CV_BGRA2GRAY);
//}

//else {
//    // Access the input image directly, since it is already grayscale.
//    gray = img;
//}

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ocvc/io_signature.h>
#include "convert_color_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    convert_color::sptr
    convert_color::make(int code)
    {
      return ocvc::get_initial_sptr
        (new convert_color_impl(code));
    }

    static const int MIN_IN = 1;	// mininum number of input streams
    static const int MAX_IN = 1;	// maximum number of input streams
    static const int MIN_OUT = 1;	// minimum number of output streams
    static const int MAX_OUT = 1;	// maximum number of output streams
    
    /*
     * The private constructor
     */
    convert_color_impl::convert_color_impl(int code)
      : oc::block("convert_color",
              oc::io_signature::make(MIN_IN, MAX_IN, sizeof(cv::Mat)),
              oc::io_signature::make(MIN_OUT, MAX_OUT, sizeof(cv::Mat)))
    {
      cvt_code = code;
    }

    /*
     * Our virtual destructor.
     */
    convert_color_impl::~convert_color_impl()
    {
      d_img.release();
      output_img.release();
    }

    void
    convert_color_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = 1;
    }

    int
    convert_color_impl::general_work (int noutput_items,
                       oc_vector_int &ninput_items,
                       oc_vector_const_void_star &input_items,
                       oc_vector_void_star &output_items)
    {
      cv::Mat *in = (cv::Mat *) input_items[0];
      cv::Mat *out = (cv::Mat *) output_items[0];
		
      cout<<"Convert : memcopy 1st"<<endl;
      memcpy(&d_img, in, sizeof(d_img));
      	
      /*
      cout<<"Convert : image size    : "<<sizeof(d_img)<<endl;
      cout<<"Convert : noutput_items : "<<noutput_items<<endl;*/
            
      if(d_img.empty())
      {
	cout<<"Convert : Empty image!!!"<<endl;
	return 0;
      }
      else
      {
	cout<<"Convert : Color space conversion"<<endl;
    
	if (d_img.channels() == 3) {
	  cvtColor(d_img, output_img, cvt_code);
	}
	else if (d_img.channels() == 4) {
	  cvtColor(d_img, output_img, cvt_code);
	}
	else {
	  output_img = d_img;
	}

	if(output_img.empty()) {
	  cout<<"Convert : image empty"<<endl;
	  return 0;
	}
	else
	{
	  cout<<"Convert : memcopy 2nd"<<endl;
	  memcpy(out, &output_img, sizeof(output_img));

	  consume_each (1);
	  return 1;
	  }
      }

    }

  } /* namespace opencv */
} /* namespace oc */

