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

#ifndef INCLUDED_OC_RUNTIME_SYNC_BLOCK_H
#define INCLUDED_OC_RUNTIME_SYNC_BLOCK_H

#include <ocvc/api.h>
#include <ocvc/block.h>

namespace oc {

  /*!
   * \brief synchronous 1:1 input to output with history
   * \ingroup base_blk
   *
   * Override work to provide the signal processing implementation.
   */
  class OC_RUNTIME_API sync_block : public block
  {
  protected:
    sync_block(void) {} // allows pure virtual interface sub-classes
    sync_block(const std::string &name,
               oc::io_signature::sptr input_signature,
               oc::io_signature::sptr output_signature);

  public:
    /*!
     * \brief just like oc::block::general_work, only this arranges to
     * call consume_each for you
     *
     * The user must override work to define the signal processing code
     */
    virtual int work(int noutput_items,
                     oc_vector_const_void_star &input_items,
                     oc_vector_void_star &output_items) = 0;

    // oc::sync_block overrides these to assist work
    void forecast(int noutput_items, oc_vector_int &ninput_items_required);
    int general_work(int noutput_items,
                     oc_vector_int &ninput_items,
                     oc_vector_const_void_star &input_items,
                     oc_vector_void_star &output_items);

    int fixed_rate_ninput_to_noutput(int ninput);
    int fixed_rate_noutput_to_ninput(int noutput);
  };

} /* namespace oc */

#endif /* INCLUDED_OC_RUNTIME_SYNC_BLOCK_H */
