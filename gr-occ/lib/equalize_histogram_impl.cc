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
#include "equalize_histogram_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    equalize_histogram::sptr
    equalize_histogram::make()
    {
      return ocvc::get_initial_sptr
        (new equalize_histogram_impl());
    }

    static const int MIN_IN = 1;	// mininum number of input streams
    static const int MAX_IN = 1;	// maximum number of input streams
    static const int MIN_OUT = 1;	// minimum number of output streams
    static const int MAX_OUT = 1;	// maximum number of output streams

    /*
     * The private constructor
     */
    equalize_histogram_impl::equalize_histogram_impl()
      : oc::block("equalize_histogram",
              oc::io_signature::make(MIN_IN, MAX_IN, sizeof(cv::Mat)),
              oc::io_signature::make(MIN_OUT, MAX_OUT, sizeof(cv::Mat)))
    {}

    /*
     * Our virtual destructor.
     */
    equalize_histogram_impl::~equalize_histogram_impl()
    {
      d_img.release();
      output_img.release();
    }

    void
    equalize_histogram_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = 1;
    }

    int
    equalize_histogram_impl::general_work (int noutput_items,
                       oc_vector_int &ninput_items,
                       oc_vector_const_void_star &input_items,
                       oc_vector_void_star &output_items)
    {
      cv::Mat *in = (cv::Mat *) input_items[0];
      cv::Mat *out = (cv::Mat *) output_items[0];
		
      cout<<"EqHist : memcopy 1st"<<endl;
      memcpy(&d_img, in, sizeof(d_img));

      if(d_img.empty())
      {
	  cout<<"EqHist : Empty image!!!"<<endl;
	  return 0;
      }
      else
      {

	cout<<"EqHist : Equalizing Histogram"<<endl;

	cv::equalizeHist(d_img, output_img);

	if(output_img.empty())
	{
	    cout<<"EqHist : image empty"<<endl;
	    return 0;
	}
	else
	{
	  cout<<"EqHist : memcopy 2nd"<<endl;
	  memcpy(out, &output_img, sizeof(output_img));

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

