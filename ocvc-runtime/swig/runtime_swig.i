/* -*- c++ -*- */
/*
 * Copyright 2013 Free Software Foundation, Inc.
 *
 * This file is part of OpenCv Companion
 *
 * OpenCv Companion is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * OpenCv Companion is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenCv Companion; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#define OC_RUNTIME_API

#ifndef SWIGIMPORTED
%include "runtime_swig_doc.i"
%module(directors="1") ocvc_runtime
#endif

%feature("autodoc", "1");		// generate python docstrings

#define SW_RUNTIME
%include "ocvc.i"				// the common stuff

%{
#include <ocvc/runtime_types.h>
%}

%include <ocvc/runtime_types.h>

%{
#include <ocvc/block.h>
#include <ocvc/block_detail.h>
#include <ocvc/buffer.h>
#include <ocvc/constants.h>
#include <ocvc/endianness.h>
#include <ocvc/feval.h>
#include <ocvc/hier_block2.h>
#include <ocvc/io_signature.h>
#include <ocvc/message.h>
#include <ocvc/msg_handler.h>
#include <ocvc/msg_queue.h>
#include <ocvc/prefs.h>
#include <ocvc/realtime.h>
#include <ocvc/sync_block.h>
#include <ocvc/sync_decimator.h>
#include <ocvc/sync_interpolator.h>
#include <ocvc/tags.h>
#include <ocvc/tagged_stream_block.h>
#include <ocvc/top_block.h>
#include <ocvc/logger.h>
%}

%constant int sizeof_char 	= sizeof(char);
%constant int sizeof_short	= sizeof(short);
%constant int sizeof_int	= sizeof(int);
%constant int sizeof_float	= sizeof(float);
%constant int sizeof_double	= sizeof(double);
%constant int sizeof_oc_complex	= sizeof(oc_complex);

%include <ocvc/endianness.h>
%include "basic_block.i"
%include "block.i"
%include "block_detail.i"
%include "buffer.i"
%include "constants.i"
%include "feval.i"
%include "hier_block2.i"
%include "io_signature.i"
%include "message.i"
%include "msg_handler.i"
%include "msg_queue.i"
%include "prefs.i"
%include "realtime.i"
%include "sync_block.i"
%include "sync_decimator.i"
%include "sync_interpolator.i"
%include "tagged_stream_block.i"
%include "tags.i"
%include "top_block.i"
%include "block_gateway.i"
%include "oc_logger.i"
%include "oc_swig_block_magic.i"
%include "oc_ctrlport.i"
