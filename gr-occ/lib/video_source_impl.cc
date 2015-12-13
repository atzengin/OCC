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
#include "video_source_impl.h"

using namespace cv;
using namespace std;

namespace oc {
namespace opencv {

video_source::sptr
video_source::make(const char *fileName, int type)
{
    return ocvc::get_initial_sptr
            (new video_source_impl(fileName, type));
}

/*
     * The private constructor
     */
video_source_impl::video_source_impl(const char *fileName, int type)
    : oc::block("video_source",
                oc::io_signature::make(0, 0, 0),
                oc::io_signature::make(1, 1, sizeof(cv::Mat)))
{
    if(!type)
    { // Camera input
        stringstream s(fileName);
        int cameraNumber;
        s >> cameraNumber;

        try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
            capture.open(cameraNumber);
        } catch (cv::Exception &e) {}
        if ( !capture.isOpened() )
        {
            cerr << "ERROR: Could not access the camera!" << endl;
            exit(1);
        }
    }
    else
    {
        try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
            capture.open(fileName);
        } catch (cv::Exception &e) {}
        if ( !capture.isOpened() )
        {
            cerr << "ERROR: Could not access the camera!" << endl;
            exit(1);
        }
    }

}

/*
     * Our virtual destructor.
     */
video_source_impl::~video_source_impl()
{
    capture.release();
    d_img.release();
}

int
video_source_impl::general_work (int noutput_items,
                                 oc_vector_int &ninput_items,
                                 oc_vector_const_void_star &input_items,
                                 oc_vector_void_star &output_items)
{
    cv::Mat *out = (cv::Mat *) output_items[0];

    // Do <+signal processing+>
    capture >> d_img;
    //flip(d_img, d_img, -1); // KOTTO CAMERA : flip the image both vert and horz

    if (d_img.empty()) //if not success, break loop
    {
        cout << "Source : Cannot read a frame from video stream" << endl;
        capture.set(CV_CAP_PROP_POS_AVI_RATIO , 0); // if the video is finished, revert to the first frame
        return 0;
    }
    else
    {
        memcpy(out, &d_img, sizeof(d_img));
        //cout<<"Source : Not Empty image!!!"<<endl;
        return 1;
    }
}
} /* namespace opencv */
} /* namespace oc */

