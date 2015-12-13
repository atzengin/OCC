/* -*- c++ -*- */
/*
 * Copyright 2004,2013 Free Software Foundation, Inc.
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

class oc::buffer;
typedef boost::shared_ptr<oc::buffer> oc::buffer_sptr;
%template(buffer_sptr) boost::shared_ptr<oc::buffer>;
%rename(buffer) oc::make_buffer;
%ignore oc::buffer;

oc::buffer_sptr 
oc::make_buffer (int nitems, size_t sizeof_item, oc::block_sptr link);

class oc::buffer_reader;
typedef boost::shared_ptr<oc::buffer_reader> oc::buffer_reader_sptr;
%template(buffer_reader_sptr) boost::shared_ptr<oc::buffer_reader>;
%ignore oc::buffer_reader;

%rename(buffer_add_reader) oc::buffer_add_reader;
oc::buffer_reader_sptr
oc::buffer_add_reader (oc::buffer_sptr buf, int nzero_preload, oc::block_sptr link);

namespace oc {

  class oc::buffer
  {
  public:
    ~buffer();

  private:
    buffer(int nitems, size_t sizeof_item, oc::block_sptr link);
  };

  class oc::buffer_reader
  {
  public:
    ~buffer_reader();

  private:
    friend class buffer;
    buffer_reader(oc::buffer_sptr buffer, unsigned int read_index, oc::block_sptr link);
  };

  %rename(buffer_ncurrently_allocated) buffer_ncurrently_allocated;
  long buffer_ncurrently_allocated();

  %rename(buffer_reader_ncurrently_allocated) buffer_reader_ncurrently_allocated;
  long buffer_reader_ncurrently_allocated();
}
