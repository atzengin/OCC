/* -*- c++ -*- */
/*
 * Copyright 2006,2009,2013 Free Software Foundation, Inc.
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

#ifndef INCLUDED_OC_CONSTANTS_H
#define INCLUDED_OC_CONSTANTS_H

#include <ocvc/api.h>
#include <string>

namespace oc {

  /*!
   * \brief return SYSCONFDIR. Typically ${CMAKE_INSTALL_PREFIX}/etc or /etc
   */
  OC_RUNTIME_API const std::string prefix();

  /*!
   * \brief return SYSCONFDIR. Typically ${CMAKE_INSTALL_PREFIX}/etc or /etc
   */
  OC_RUNTIME_API const std::string sysconfdir();

  /*!
   * \brief return preferences file directory. Typically ${SYSCONFDIR}/etc/conf.d
   */
  OC_RUNTIME_API const std::string prefsdir();

  /*!
   * \brief return date/time of build, as set when 'cmake' is run
   */
  OC_RUNTIME_API const std::string build_date();

  /*!
   * \brief return version string defined by cmake (OcVersion.cmake)
   */
  OC_RUNTIME_API const std::string version();

} /* namespace oc */

#endif /* INCLUDED_OC_CONSTANTS_H */
