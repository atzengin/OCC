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

#ifndef QA_OC_VMCIRCBUF_H
#define QA_OC_VMCIRCBUF_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class qa_vmcircbuf : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(qa_vmcircbuf);
  CPPUNIT_TEST(test_all);
  CPPUNIT_TEST_SUITE_END();

private:
  void test_all();
};

#endif /* QA_OC_VMCIRCBUF_H */
