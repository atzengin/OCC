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
#include "video_write_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    video_write::sptr
    video_write::make()
    {
      return ocvc::get_initial_sptr
        (new video_write_impl());
    }

    /*
     * The private constructor
     */
    video_write_impl::video_write_impl()
      : oc::block("video_write",
              oc::io_signature::make(1, 1, sizeof(cv::Mat)),
              oc::io_signature::make(0, 0, 0))
    {
      const string filename = "output.avi";
      Size S = Size(640,480);
      videowriter.open(filename, CV_FOURCC('M','J','P','G'), 30.0, S, true);
      
      
      if (!videowriter.isOpened())  // if not success, exit program
      {
	cout << "Write : Cannot open the output file" << endl;
      }
    }

    /*
     * Our virtual destructor.
     */
    video_write_impl::~video_write_impl()
    {
      d_img.release();
    }

    void
    video_write_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    video_write_impl::general_work (int noutput_items,
                       oc_vector_int &ninput_items,
                       oc_vector_const_void_star &input_items,
                       oc_vector_void_star &output_items)
    {
      cv::Mat *in = (cv::Mat *) input_items[0];

        // Do <+signal processing+>
        memcpy(&d_img, in, sizeof(d_img));
        if(d_img.empty())
        {
            cout<<"Write: Empty image!!!"<<endl;
        }
        else
        {
	  //videowriter << d_img;
	  videowriter.write(d_img);
          cout<<"Write: Image written to video file!!!"<<endl;
	  waitKey(1);
	  
          consume_each (1);
        }

        // Tell runtime system how many output items we produced.
        return 1;
    }

  } /* namespace opencv */
} /* namespace oc */

