/* -*- c++ -*- */
/*
 * Copyright 2008,2013 Free Software Foundation, Inc.
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef INCLUDED_OC_RUNTIME_SPTR_MAGIC_H
#define INCLUDED_OC_RUNTIME_SPTR_MAGIC_H

#include <ocvc/api.h>
#include <boost/shared_ptr.hpp>

namespace oc {
  class basic_block;
  class hier_block2;
}

namespace ocvc {
  namespace detail {

    class OC_RUNTIME_API sptr_magic
    {
    public:
      static boost::shared_ptr<oc::basic_block> fetch_initial_sptr(oc::basic_block *p);
      static void create_and_stash_initial_sptr(oc::hier_block2 *p);
    };
  };

  /*
   * \brief New!  Improved!  Standard method to get/create the
   * boost::shared_ptr for a block.
   */
  template<class T>
  boost::shared_ptr<T>
  get_initial_sptr(T *p)
  {
    return boost::dynamic_pointer_cast<T, oc::basic_block>
      (detail::sptr_magic::fetch_initial_sptr(p));
  }
}

#endif /* INCLUDED_OC_RUNTIME_SPTR_MAGIC_H */
