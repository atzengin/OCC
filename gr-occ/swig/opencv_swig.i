/* -*- c++ -*- */

#define OPENCV_API

%include "ocvc.i"			// the common stuff

//load generated python docstrings
%include "opencv_swig_doc.i"

%{
#include "opencv/video_source.h"
#include "opencv/video_write.h"
#include "opencv/image_sink.h"
#include "opencv/image_source.h"
#include "opencv/image_write.h"
#include "opencv/udp_image_source.h"
#include "opencv/udp_image_sink.h"
#include "opencv/convert_color.h"
#include "opencv/detect_object.h"
#include "opencv/equalize_histogram.h"
#include "opencv/rectangle.h"
#include "opencv/video_sink.h"
#include "opencv/resize_image.h"
#include "opencv/http_video_sink.h"
%}

%include "opencv/video_source.h"
OC_SWIG_BLOCK_MAGIC2(opencv, video_source);
%include "opencv/video_write.h"
OC_SWIG_BLOCK_MAGIC2(opencv, video_write);

%include "opencv/image_write.h"
OC_SWIG_BLOCK_MAGIC2(opencv, image_write);
%include "opencv/image_sink.h"
OC_SWIG_BLOCK_MAGIC2(opencv, image_sink);
%include "opencv/image_source.h"
OC_SWIG_BLOCK_MAGIC2(opencv, image_source);
%include "opencv/udp_image_source.h"
OC_SWIG_BLOCK_MAGIC2(opencv, udp_image_source);
%include "opencv/udp_image_sink.h"
OC_SWIG_BLOCK_MAGIC2(opencv, udp_image_sink);
%include "opencv/convert_color.h"
OC_SWIG_BLOCK_MAGIC2(opencv, convert_color);
%include "opencv/detect_object.h"
OC_SWIG_BLOCK_MAGIC2(opencv, detect_object);
%include "opencv/equalize_histogram.h"
OC_SWIG_BLOCK_MAGIC2(opencv, equalize_histogram);
%include "opencv/rectangle.h"
OC_SWIG_BLOCK_MAGIC2(opencv, rectangle);

%include "opencv/video_sink.h"
OC_SWIG_BLOCK_MAGIC2(opencv, video_sink);

%include "opencv/resize_image.h"
OC_SWIG_BLOCK_MAGIC2(opencv, resize_image);
%include "opencv/http_video_sink.h"
OC_SWIG_BLOCK_MAGIC2(opencv, http_video_sink);
