/* -*- c++ -*- */
/*
 * Copyright 2009 Free Software Foundation, Inc.
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

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <ocvc/constants.h>
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int
main(int argc, char **argv)
{
  po::options_description desc("Program options: ocvc [options]");
  po::variables_map vm;

  desc.add_options()
    ("help,h", "print help message")
    ("prefix", "print ocvc installation prefix")
    ("sysconfdir", "print ocvc system configuration directory")
    ("prefsdir", "print ocvc preferences directory")
    ("builddate", "print ocvc build date (RFC2822 format)")
    ("version,v", "print ocvc version")
    ;

  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if(vm.size() == 0 || vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }

  if(vm.count("prefix"))
    std::cout << oc::prefix() << std::endl;

  if(vm.count("sysconfdir"))
    std::cout << oc::sysconfdir() << std::endl;

  if(vm.count("prefsdir"))
    std::cout << oc::prefsdir() << std::endl;

  if(vm.count("builddate"))
    std::cout << oc::build_date() << std::endl;

  if(vm.count("version"))
    std::cout << oc::version() << std::endl;

  return 0;
}
