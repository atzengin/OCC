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
#include "image_sink_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    image_sink::sptr
    image_sink::make()
    {
      return ocvc::get_initial_sptr
        (new image_sink_impl());
    }

    /*
     * The private constructor
     */
    image_sink_impl::image_sink_impl()
      : oc::block("image_sink",
              oc::io_signature::make(1, 1, sizeof(cv::Mat)),
              oc::io_signature::make(0, 0, 0))
    {}

    /*
     * Our virtual destructor.
     */
    image_sink_impl::~image_sink_impl()
    {
    }

    void
    image_sink_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    image_sink_impl::general_work (int noutput_items,
                       oc_vector_int &ninput_items,
                       oc_vector_const_void_star &input_items,
                       oc_vector_void_star &output_items)
    {
      cv::Mat *in = (cv::Mat *) input_items[0];
      cout<<"Sink : memcpy"<<endl;
      memcpy(&d_img, in, sizeof(d_img));
      cout<<"Sink : imshow"<<endl;
      
      cout<<"Sink : image size    : "<<sizeof(d_img)<<endl;
      cout<<"Sink : noutput_items : "<<noutput_items<<endl;
      
      if(d_img.empty())
      {
	cout<<"Sink : Empty image!!!"<<endl;
	return 1;
      }
      else
      {
	imshow("Output Image", d_img);
	waitKey(0);
//            destroyWindow("Output Image");

	 consume_each (1);

      }
        
      // Tell runtime system how many output items we produced.
      return 1;
    }

  } /* namespace opencv */
} /* namespace oc */

