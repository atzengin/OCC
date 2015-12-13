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
#include "detect_object_impl.h"

using namespace cv;
using namespace std;

namespace oc {
  namespace opencv {

    detect_object::sptr
    detect_object::make(const char *cascadeFilename, int minFeatureSize, int scaledWidth)
    {
      return ocvc::get_initial_sptr
        (new detect_object_impl(cascadeFilename, minFeatureSize, scaledWidth));
    }

    static const int MIN_IN = 2;	// mininum number of input streams
    static const int MAX_IN = 2;	// maximum number of input streams
    static const int MIN_OUT = 1;	// minimum number of output streams
    static const int MAX_OUT = 1;	// maximum number of output streams

    /*
     * The private constructor
     */
    detect_object_impl::detect_object_impl(const char *cascadeFilename, int minFeatureSize, int scaledWidth)
      : oc::block("detect_object",
              oc::io_signature::make2(MIN_IN, MAX_IN, sizeof(cv::Mat), sizeof(cv::Mat)),
              oc::io_signature::make(MIN_OUT, MAX_OUT, sizeof(cv::Rect)))
    {
      // Load the Object Detection cascade classifier xml file.
      // Surround the OpenCV call by a try/catch block so we can give a useful error message!
      try
      {
        classifier.load(cascadeFilename);
      }
      catch (cv::Exception &e)
      {
        cerr << "ERROR: Could not load Object Detection cascade classifier [" << cascadeFilename << "]!" << endl;
      }

      if ( classifier.empty() )
      {
        cerr << "ERROR: Could not load Object Detection cascade classifier [" << cascadeFilename << "]!" << endl;
      }
      else
      {
        cout << "Loaded the Object Detection cascade classifier [" << cascadeFilename << "]." << endl;
        flags = CASCADE_FIND_BIGGEST_OBJECT;
        minFeatureRect = Size(minFeatureSize, minFeatureSize);
        searchScaleFactor = 1.1f;
        minNeighbors = 4;
        desiredScaledWidth = scaledWidth;
        desiredObjectWidth = 70;
        desiredObjectHeight = 70; // Deal with these later!
      }
    }

    /*
     * Our virtual destructor.
     */
    detect_object_impl::~detect_object_impl()
    {
      // release all images, classifiers etc.
      d_img.release();
    }

    void
    detect_object_impl::forecast (int noutput_items, oc_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = 1;
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    
    // Can use Haar cascades or LBP cascades for Face Detection, or even eye, mouth, or car detection.
    // Input is temporarily shrunk to 'scaledWidth' for much faster detection, since 200 is enough to find faces.
    void detect_object_impl::detectObjectsCustom(const Mat &img, const Mat &img_orig, CascadeClassifier &cascade, vector<Rect> &objects, int scaledWidth, int flags, Size minFeatureSize, float searchScaleFactor, int minNeighbors)
    {
//        float scale = img_orig.cols / (float)scaledWidth;
//        // Detect objects in the small grayscale image.
        cascade.detectMultiScale(img, objects, searchScaleFactor, minNeighbors, flags, minFeatureSize);

//        // Enlarge the results if the image was temporarily shrunk before detection.
//        if (img_orig.cols > scaledWidth) {
//            for (int i = 0; i < (int)objects.size(); i++ ) {
//                objects[i].x = cvRound(objects[i].x * scale);
//                objects[i].y = cvRound(objects[i].y * scale);
//                objects[i].width = cvRound(objects[i].width * scale);
//                objects[i].height = cvRound(objects[i].height * scale);
//            }
//        }

        // Make sure the object is completely within the image, in case it was on a border.
        for (int i = 0; i < (int)objects.size(); i++ ) {
            if (objects[i].x < 0)
                objects[i].x = 0;
            if (objects[i].y < 0)
                objects[i].y = 0;
            if (objects[i].x + objects[i].width > img_orig.cols)
                objects[i].x = img_orig.cols - objects[i].width;
            if (objects[i].y + objects[i].height > img_orig.rows)
                objects[i].y = img_orig.rows - objects[i].height;
        }

        // Return with the detected Object rectangles stored in "objects".
    }
    
    
int
detect_object_impl::general_work (int noutput_items,
                   oc_vector_int &ninput_items,
                   oc_vector_const_void_star &input_items,
                   oc_vector_void_star &output_items)
{
    cv::Mat *in = (cv::Mat *) input_items[0];
    cv::Mat *orig = (cv::Mat *) input_items[1];
    cv::Rect *out = (cv::Rect *) output_items[0];

    cout<<"Detect Object : memcopy 1st"<<endl;
    memcpy(&d_img, in, sizeof(d_img));
    memcpy(&d_img_orig, orig, sizeof(d_img_orig));

    if(d_img.empty())
    {
        cout<<"Detect Object : Empty image!!!"<<endl;
        // Tell runtime system how many output items we produced.
        return 0;
    }
    else
    {
        cout<<"Detect Object : Detection"<<endl;

        // Perform Object or Face Detection, looking for just 1 object (the biggest in the image).
        vector<Rect> objects;
        Rect largestObject;

        detectObjectsCustom(d_img, d_img_orig, classifier, objects, desiredScaledWidth, flags, minFeatureRect, searchScaleFactor, minNeighbors);

        if (objects.size() > 0)
        {
            // Return the only detected object.
            largestObject = (Rect)objects.at(0);
        }
        else
        {
            // Return an invalid rect.
            largestObject = Rect(-1,-1,-1,-1);
        }

        //objectRect.copyTo(output_objectRect);
        output_objectRect = largestObject;

        if(output_objectRect.width < 1)
        {
            cout<<"Detect Object : image empty"<<endl;
            return 0;
        }
        else
        {
            cout<<"Detect Object : memcopy 2nd"<<endl;
            memcpy(out, &output_objectRect, sizeof(output_objectRect));
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

