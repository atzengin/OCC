/* -*- c++ -*- */
/*
 * Copyright 2004,2013 Free Software Foundation, Inc.
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
#include <config.h>
#endif

#include <qa_fxpt.h>
#include <ocvc/fxpt.h>
#include <cppunit/TestAssert.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

static const float SIN_COS_TOLERANCE = 1e-5;

void
qa_fxpt::t0()
{
  CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI/2, oc::fxpt::fixed_to_float(0x40000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,    oc::fxpt::fixed_to_float(0x00000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-M_PI,  oc::fxpt::fixed_to_float(0x80000000), SIN_COS_TOLERANCE);

  if(0) {
    /*
     * These are disabled because of some precision issues.
     *
     * Different compilers seem to have different opinions on whether
     * the calulations are done single or double (or extended)
     * precision.  Any of the answers are fine for our real purpose, but
     * sometimes the answer is off by a few bits at the bottom.
     * Hence, the disabled check.
     */
    CPPUNIT_ASSERT_EQUAL((oc_int32)0x40000000, oc::fxpt::float_to_fixed(M_PI/2));
    CPPUNIT_ASSERT_EQUAL((oc_int32)0,          oc::fxpt::float_to_fixed(0));
    CPPUNIT_ASSERT_EQUAL((oc_int32)0x80000000, oc::fxpt::float_to_fixed(-M_PI));
  }
}

void
qa_fxpt::t1()
{
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0,           oc::fxpt::sin(0x00000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.707106781, oc::fxpt::sin(0x20000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1,           oc::fxpt::sin(0x40000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.707106781, oc::fxpt::sin(0x60000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0,           oc::fxpt::sin(0x7fffffff), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0,           oc::fxpt::sin(0x80000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0,           oc::fxpt::sin(0x80000001), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1,           oc::fxpt::sin(-0x40000000), SIN_COS_TOLERANCE);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.707106781, oc::fxpt::sin(-0x20000000), SIN_COS_TOLERANCE);

  for(float p = -M_PI; p < M_PI; p += 2 * M_PI / 3600) {
    float expected = sin(p);
    float actual = oc::fxpt::sin(oc::fxpt::float_to_fixed (p));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, SIN_COS_TOLERANCE);
  }
}

void
qa_fxpt::t2()
{
  for(float p = -M_PI; p < M_PI; p += 2 * M_PI / 3600) {
    float expected = cos(p);
    float actual = oc::fxpt::cos(oc::fxpt::float_to_fixed(p));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, SIN_COS_TOLERANCE);
  }
}

void
qa_fxpt::t3()
{
  for(float p = -M_PI; p < M_PI; p += 2 * M_PI / 3600) {
    float expected_sin = sin(p);
    float expected_cos = cos(p);
    float actual_sin;
    float actual_cos;
    oc::fxpt::sincos(oc::fxpt::float_to_fixed (p), &actual_sin, &actual_cos);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_sin, actual_sin, SIN_COS_TOLERANCE);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_cos, actual_cos, SIN_COS_TOLERANCE);
  }
}
