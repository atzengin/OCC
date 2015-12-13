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

#ifndef INCLUDED_OPENCV_DETECT_OBJECT_IMPL_H
#define INCLUDED_OPENCV_DETECT_OBJECT_IMPL_H

#include <opencv/detect_object.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    class detect_object_impl : public detect_object
    {
     private:
      Mat d_img, d_img_orig;	// Image to be processed
      CascadeClassifier classifier;
      Rect objectRect, output_objectRect;
      int desiredObjectWidth;
      int desiredObjectHeight;
      int desiredScaledWidth;
      int flags;
      Size minFeatureRect;
      float searchScaleFactor;
      int minNeighbors;

    public:
      detect_object_impl(const char *cascadeFilename, int minFeatureSize, int scaledWidth);
      ~detect_object_impl();

      // Where all the action really happens
      void forecast (int noutput_items, oc_vector_int &ninput_items_required);

      // Search for objects such as faces in the image using the given parameters, storing the multiple cv::Rects into 'objects'.
      // Can use Haar cascades or LBP cascades for Face Detection, or even eye, mouth, or car detection.
      // Input is temporarily shrunk to 'scaledWidth' for much faster detection, since 200 is enough to find faces.
      void detectObjectsCustom(const Mat &img, const Mat &img_orig, CascadeClassifier &cascade, vector<Rect> &objects, int scaledWidth, int flags, Size minFeatureSize, float searchScaleFactor, int minNeighbors);
      
      int general_work(int noutput_items,
		       oc_vector_int &ninput_items,
		       oc_vector_const_void_star &input_items,
		       oc_vector_void_star &output_items);
    };

  } // namespace opencv
} // namespace oc

#endif /* INCLUDED_OPENCV_DETECT_OBJECT_IMPL_H */

