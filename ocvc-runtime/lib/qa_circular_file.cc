/* -*- c++ -*- */
/*
 * Copyright 2002,2013 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "qa_circular_file.h"
#include "circular_file.h"
#include <cppunit/TestAssert.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

static const char *test_file = "qa_oc_circular_file.data";
static const int BUFFER_SIZE = 8192;
static const int NWRITE = 8192 * 9 / 8;

void
qa_circular_file::t1()
{
#ifdef HAVE_MMAP
  oc::circular_file *cf_writer;
  oc::circular_file *cf_reader;

  // write the data...
  cf_writer = new oc::circular_file(test_file, true,
                                    BUFFER_SIZE * sizeof(short));

  short sd;
  for(int i = 0; i < NWRITE; i++) {
    sd = i;
    cf_writer->write(&sd, sizeof (sd));
  }

  delete cf_writer;

  // now read it back...
  cf_reader = new oc::circular_file(test_file);
  for(int i = 0; i < BUFFER_SIZE; i++) {
    int n = cf_reader->read (&sd, sizeof(sd));
    CPPUNIT_ASSERT_EQUAL((int) sizeof (sd), n);
    CPPUNIT_ASSERT_EQUAL(NWRITE - BUFFER_SIZE + i, (int)sd);
  }

  int n = cf_reader->read(&sd, sizeof(sd));
  CPPUNIT_ASSERT_EQUAL(0, n);

  delete cf_reader;
  unlink(test_file);
#endif // HAVE_MMAP
}

