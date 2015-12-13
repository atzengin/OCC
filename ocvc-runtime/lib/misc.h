/* -*- c++ -*- */
/*
 * Copyright 2005,2013 Free Software Foundation, Inc.
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

#ifndef INCLUDED_OC_MISC_H
#define INCLUDED_OC_MISC_H

#include <ocvc/api.h>
#include <ocvc/types.h>

namespace oc {

  OC_RUNTIME_API unsigned int
  rounduppow2(unsigned int n);

  // FIXME should be template
  OC_RUNTIME_API void zero_vector(std::vector<float> &v);
  OC_RUNTIME_API void zero_vector(std::vector<double> &v);
  OC_RUNTIME_API void zero_vector(std::vector<int> &v);
  OC_RUNTIME_API void zero_vector(std::vector<oc_complex> &v);

} /* namespace oc */

#endif /* INCLUDED_OC_MISC_H */
