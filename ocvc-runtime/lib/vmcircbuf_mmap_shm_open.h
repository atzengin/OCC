/* -*- c++ -*- */
/*
 * Copyright 2003,2013 Free Software Foundation, Inc.
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

#ifndef OC_VMCIRCBUF_MMAP_SHM_OPEN_H
#define OC_VMCIRCBUF_MMAP_SHM_OPEN_H

#include <ocvc/api.h>
#include "vmcircbuf.h"

namespace oc {

  /*!
   * \brief concrete class to implement circular buffers with mmap and shm_open
   * \ingroup internal
   */
  class OC_RUNTIME_API vmcircbuf_mmap_shm_open : public oc::vmcircbuf
  {
  public:
    vmcircbuf_mmap_shm_open(int size);
    virtual ~vmcircbuf_mmap_shm_open();
  };

  /*!
   * \brief concrete factory for circular buffers built using mmap and shm_open
   */
  class OC_RUNTIME_API vmcircbuf_mmap_shm_open_factory : public oc::vmcircbuf_factory
  {
  private:
    static oc::vmcircbuf_factory *s_the_factory;

  public:
    static oc::vmcircbuf_factory *singleton();

    virtual const char *name() const { return "oc::vmcircbuf_mmap_shm_open_factory"; }

    /*!
     * \brief return granularity of mapping, typically equal to page size
     */
    virtual int granularity();

    /*!
     * \brief return a oc::vmcircbuf, or 0 if unable.
     *
     * Call this to create a doubly mapped circular buffer.
     */
    virtual oc::vmcircbuf *make(int size);
  };

} /* namespace oc */

#endif /* OC_VMCIRCBUF_MMAP_SHM_OPEN_H */
