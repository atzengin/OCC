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
#include "image_source_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    image_source::sptr
    image_source::make(const char *filename, int type)
    {
      return ocvc::get_initial_sptr
        (new image_source_impl(filename, type));
    }

    /*
     * The private constructor
     */
    image_source_impl::image_source_impl(const char *filename, int type)
      : oc::block("image_source",
              oc::io_signature::make(0,0,0),
              oc::io_signature::make(1, 1, sizeof(cv::Mat)))
    {
      d_img = imread(filename, 1);
      if(!d_img.data)
      {
	throw std::runtime_error ("Can't open image file");
      }
    }

    /*
     * Our virtual destructor.
     */
    image_source_impl::~image_source_impl()
    {
      capture.release();
      d_img.release();
    }

    void
    image_source_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    image_source_impl::general_work (int noutput_items,
                       oc_vector_int &ninput_items,
                       oc_vector_const_void_star &input_items,
                       oc_vector_void_star &output_items)
    {
      cv::Mat *out = (cv::Mat *) output_items[0];
      static int i=0;
      
      cout<<"Source : image size    : "<<sizeof(d_img)<<endl;
      cout<<"Source : noutput_items : "<<noutput_items<<endl;
      
      cout<<"Source : memcpy"<<endl;
      if(d_img.empty())
      {
	  cout<<"Source : image empty!!!"<<endl;
	  return 0;
      }
      else
      {
	  memcpy(out, &d_img, sizeof(d_img));
	  i++;
	  cout<<"Source : Not Empty image!!!"<<endl;
	  if (i > 1) return -1;
	  else return 1;
      }
    }

  } /* namespace opencv */
} /* namespace oc */

