/* -*- c++ -*- */
/*
 * Copyright 2006 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDED_OC_EXPJ_H
#define INCLUDED_OC_EXPJ_H

#include <ocvc/api.h>
#include <ocvc/sincos.h>
#include <ocvc/types.h>

static inline oc_complex
oc_expj(float phase)
{
  float	t_imag, t_real;
  oc::sincosf(phase, &t_imag, &t_real);
  return oc_complex(t_real, t_imag);
}


#endif /* INCLUDED_OC_EXPJ_H */
