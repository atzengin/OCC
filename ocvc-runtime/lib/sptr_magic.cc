/* -*- c++ -*- */
/*
 * Copyright 2008,2009,2013 Free Software Foundation, Inc.
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <ocvc/sptr_magic.h>
#include <ocvc/hier_block2.h>
#include <map>
#include <stdexcept>

#include <ocvc/thread/thread.h>

namespace ocvc {

  static oc::thread::mutex s_mutex;
  typedef std::map<oc::basic_block*, oc::basic_block_sptr> sptr_map;
  static sptr_map s_map;

  void
  detail::sptr_magic::create_and_stash_initial_sptr(oc::hier_block2 *p)
  {
    oc::basic_block_sptr sptr(p);
    oc::thread::scoped_lock guard(s_mutex);
    s_map.insert(sptr_map::value_type(static_cast<oc::basic_block *>(p), sptr));
  }

  oc::basic_block_sptr
  detail::sptr_magic::fetch_initial_sptr(oc::basic_block *p)
  {
    /*
     * If p isn't a subclass of oc::hier_block2, just create the
     * shared ptr and return it.
     */
    oc::hier_block2 *hb2 = dynamic_cast<oc::hier_block2 *>(p);
    if(!hb2) {
      return oc::basic_block_sptr(p);
    }

    /*
     * p is a subclass of oc::hier_block2, thus we've already created the shared pointer
     * and stashed it away.  Fish it out and return it.
     */
    oc::thread::scoped_lock guard(s_mutex);
    sptr_map::iterator pos = s_map.find(static_cast<oc::basic_block *>(p));
    if(pos == s_map.end())
      throw std::invalid_argument("sptr_magic: invalid pointer!");

    oc::basic_block_sptr sptr = pos->second;
    s_map.erase(pos);
    return sptr;
  }
};
