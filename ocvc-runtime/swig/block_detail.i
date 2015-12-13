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

class oc::block_detail;
typedef boost::shared_ptr<oc::block_detail> oc::block_detail_sptr;
%template(block_detail_sptr) boost::shared_ptr<oc::block_detail>;
%rename(block_detail) oc::make_block_detail;
%ignore oc::block_detail;

oc::block_detail_sptr oc::
oc::make_block_detail(unsigned int ninputs, unsigned int noutputs);

namespace oc {

  class oc::block_detail {
  public:

    ~block_detail ();

    int ninputs() const;
    int noutputs() const;
    bool sink_p() const;
    bool source_p() const;

    void set_input(unsigned int which, oc::buffer_reader_sptr reader);
    oc::buffer_reader_sptr input(unsigned int which);

    void set_output(unsigned int which, oc::buffer_sptr buffer);
    oc::buffer_sptr output(unsigned int which);

  private:
    block_detail(unsigned int ninputs, unsigned int noutputs);
  };

  %rename(block_detail_ncurrently_allocated) block_detail_ncurrently_allocated;
  long block_detail_ncurrently_allocated();
}
