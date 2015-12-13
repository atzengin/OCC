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
#include "http_video_sink_impl.h"

using namespace cv;
using namespace std;
using namespace http::server;

namespace oc {
  namespace opencv {

    http_video_sink::sptr
    http_video_sink::make(const char *ip, int port)
    {
      return ocvc::get_initial_sptr
        (new http_video_sink_impl(ip, port));
    }

    /*
     * The private constructor
     */
    http_video_sink_impl::http_video_sink_impl(const char *ip, int port)
      : oc::sync_block("http_video_sink",
              oc::io_signature::make(1, 1, sizeof(Mat)),
              oc::io_signature::make(0, 0, 0)),
              s(init_streaming_server("192.168.1.25","9090", "streamer", boost::lexical_cast<std::size_t>(1))),
              stmr(new streamer)
    {
    cout<<"HTTP_Sink: Constructor"<<endl;

    std::size_t num_threads = boost::lexical_cast<std::size_t>(1);
    
    // server_ptr s2(init_streaming_server("192.168.1.25","9090", "streamer", num_threads));
    
    //server_ptr temp(init_streaming_server("192.168.1.25","9090", "streamer", num_threads));
    //s = new server_ptr(temp);
    
    //s2.swap(s);
    //boost::swap(s,s2);
    //s2.swap(s);
    
    
    //streamer_ptr stmr2(new streamer);
    
    
    //stmr = stmr2;
    //stmr2.swap(stmr);
    //boost::swap(stmr,stmr2);
    //stmr2.swap(stmr);
    
    register_streamer(s, stmr, "/stream_0");

    cout<<"HTTP_Sink: Constructor Ends"<<endl;
    }

    /*
     * Our virtual destructor.
     */
    http_video_sink_impl::~http_video_sink_impl()
    {
        d_img.release();
    }

    
    void
    http_video_sink_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = 1;
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    http_video_sink_impl::work(int noutput_items,
			  oc_vector_const_void_star &input_items,
			  oc_vector_void_star &output_items)
    {
      cv::Mat *in = (cv::Mat *) input_items[0];


        // Do <+signal processing+>
        memcpy(&d_img, in, sizeof(d_img));

        if(d_img.empty())
        {
            cout<<"HTTP_Sink: Empty image!!!"<<endl;
        }
        else
        {

          cout<<"HTTP_Sink: Work Func"<<endl;
          bool wait = false; //don't wait for there to be more than one webpage looking at us.
          int quality = 80;
          stmr->post_image(d_img, quality, wait);
          //boost::this_thread::sleep(boost::posix_time::milliseconds(100)); //10 fps for ease on my eyes
          consume_each (1);

        }
        // Tell runtime system how many output items we produced.
        return 1;
    }

  } /* namespace opencv */
} /* namespace oc */

