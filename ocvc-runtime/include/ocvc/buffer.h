/* -*- c++ -*- */
/*
 * Copyright 2004,2009-2011,2013 Free Software Foundation, Inc.
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

#ifndef INCLUDED_OC_RUNTIME_BUFFER_H
#define INCLUDED_OC_RUNTIME_BUFFER_H

#include <ocvc/api.h>
#include <ocvc/runtime_types.h>
#include <ocvc/tags.h>
#include <boost/weak_ptr.hpp>
#include <ocvc/thread/thread.h>
#include <deque>

namespace oc {
  
  class vmcircbuf;

  /*!
   * \brief Allocate a buffer that holds at least \p nitems of size \p sizeof_item.
   *
   * The total size of the buffer will be rounded up to a system
   * dependent boundary. This is typically the system page size, but
   * under MS windows is 64KB.
   *
   * \param nitems is the minimum number of items the buffer will hold.
   * \param sizeof_item is the size of an item in bytes.
   * \param link is the block that writes to this buffer.
   */
  OC_RUNTIME_API buffer_sptr make_buffer(int nitems, size_t sizeof_item,
                                         block_sptr link=block_sptr());

  /*!
   * \brief Single writer, multiple reader fifo.
   * \ingroup internal
   */
  class OC_RUNTIME_API buffer
  {
  public:
    virtual ~buffer();

    /*!
     * \brief return number of items worth of space available for writing
     */
    int space_available();

    /*!
     * \brief return size of this buffer in items
     */
    int bufsize() const { return d_bufsize; }

    /*!
     * \brief return pointer to write buffer.
     *
     * The return value points at space that can hold at least
     * space_available() items.
     */
    void *write_pointer();

    /*!
     * \brief tell buffer that we wrote \p nitems into it
     */
    void update_write_pointer(int nitems);

    void set_done(bool done);
    bool done() const { return d_done; }

    /*!
     * \brief Return the block that writes to this buffer.
     */
    block_sptr link() { return block_sptr(d_link); }

    size_t nreaders() const { return d_readers.size(); }
    buffer_reader* reader(size_t index) { return d_readers[index]; }

    oc::thread::mutex *mutex() { return &d_mutex; }

    uint64_t nitems_written() { return d_abs_write_offset; }

    size_t get_sizeof_item() { return d_sizeof_item; }

    /*!
     * \brief  Adds a new tag to the buffer.
     *
     * \param tag        the new tag
     */
    void add_item_tag(const tag_t &tag);

    /*!
     * \brief  Removes an existing tag from the buffer.
     *
     * If no such tag is found, does nothing.
     * Note: Doesn't actually physically delete the tag, but
     * marks it as deleted. For the user, this has the same effect:
     * Any subsequent calls to get_tags_in_range() will not return
     * the tag.
     *
     * \param tag        the tag that needs to be removed
     * \param id         the unique ID of the block calling this function
     */
    void remove_item_tag(const tag_t &tag, long id);

    /*!
     * \brief  Removes all tags before \p max_time from buffer
     *
     * \param max_time        the time (item number) to trim up until.
     */
    void prune_tags(uint64_t max_time);

    std::deque<tag_t>::iterator get_tags_begin() { return d_item_tags.begin(); }
    std::deque<tag_t>::iterator get_tags_end() { return d_item_tags.end(); }

    // -------------------------------------------------------------------------

  private:
    friend class buffer_reader;
    friend OC_RUNTIME_API buffer_sptr make_buffer(int nitems, size_t sizeof_item, block_sptr link);
    friend OC_RUNTIME_API buffer_reader_sptr buffer_add_reader(buffer_sptr buf, int nzero_preload, block_sptr link);

  protected:
    char			       *d_base;		// base address of buffer
    unsigned int			d_bufsize;	// in items
  private:
    oc::vmcircbuf		       *d_vmcircbuf;
    size_t	 			d_sizeof_item;	// in bytes
    std::vector<buffer_reader *>	d_readers;
    boost::weak_ptr<block>		d_link;		// block that writes to this buffer

    //
    // The mutex protects d_write_index, d_abs_write_offset, d_done, d_item_tags
    // and the d_read_index's and d_abs_read_offset's in the buffer readers.
    //
    oc::thread::mutex			d_mutex;
    unsigned int			d_write_index;	// in items [0,d_bufsize)
    uint64_t                            d_abs_write_offset; // num items written since the start
    bool				d_done;
    std::deque<tag_t>                d_item_tags;
    uint64_t                            d_last_min_items_read;

    unsigned index_add(unsigned a, unsigned b)
    {
      unsigned s = a + b;

      if(s >= d_bufsize)
        s -= d_bufsize;

      assert(s < d_bufsize);
      return s;
    }

    unsigned index_sub(unsigned a, unsigned b)
    {
      int s = a - b;

      if(s < 0)
        s += d_bufsize;

      assert((unsigned) s < d_bufsize);
      return s;
    }

    virtual bool allocate_buffer(int nitems, size_t sizeof_item);

    /*!
     * \brief constructor is private.  Use oc_make_buffer to create instances.
     *
     * Allocate a buffer that holds at least \p nitems of size \p sizeof_item.
     *
     * \param nitems is the minimum number of items the buffer will hold.
     * \param sizeof_item is the size of an item in bytes.
     * \param link is the block that writes to this buffer.
     *
     * The total size of the buffer will be rounded up to a system
     * dependent boundary.  This is typically the system page size, but
     * under MS windows is 64KB.
     */
    buffer(int nitems, size_t sizeof_item, block_sptr link);

    /*!
     * \brief disassociate \p reader from this buffer
     */
    void drop_reader(buffer_reader *reader);
  };

  /*!
   * \brief Create a new oc::buffer_reader and attach it to buffer \p buf
   * \param buf is the buffer the \p oc::buffer_reader reads from.
   * \param nzero_preload -- number of zero items to "preload" into buffer.
   * \param link is the block that reads from the buffer using this oc::buffer_reader.
   */
  OC_RUNTIME_API buffer_reader_sptr
    buffer_add_reader(buffer_sptr buf, int nzero_preload, block_sptr link=block_sptr());

  //! returns # of buffers currently allocated
  OC_RUNTIME_API long buffer_ncurrently_allocated();


  // ---------------------------------------------------------------------------

  /*!
   * \brief How we keep track of the readers of a oc::buffer.
   * \ingroup internal
   */
  class OC_RUNTIME_API buffer_reader
  {
  public:
    ~buffer_reader();

    /*!
     * \brief Return number of items available for reading.
     */
    int items_available() const;

    /*!
     * \brief Return buffer this reader reads from.
     */
    buffer_sptr buffer() const { return d_buffer; }

    /*!
     * \brief Return maximum number of items that could ever be available for reading.
     * This is used as a sanity check in the scheduler to avoid looping forever.
     */
    int max_possible_items_available() const { return d_buffer->d_bufsize - 1; }

    /*!
     * \brief return pointer to read buffer.
     *
     * The return value points to items_available() number of items
     */
    const void *read_pointer();

    /*
     * \brief tell buffer we read \p items from it
     */
    void update_read_pointer(int nitems);

    void set_done(bool done) { d_buffer->set_done(done); }
    bool done() const { return d_buffer->done(); }

    oc::thread::mutex *mutex() { return d_buffer->mutex(); }

    uint64_t nitems_read() { return d_abs_read_offset; }

    size_t get_sizeof_item() { return d_buffer->get_sizeof_item(); }

    /*!
     * \brief Return the block that reads via this reader.
     *
     */
    block_sptr link() { return block_sptr(d_link); }

    /*!
     * \brief Given a [start,end), returns a vector all tags in the range.
     *
     * Get a vector of tags in given range. Range of counts is from start to end-1.
     *
     * Tags are tuples of:
     *      (item count, source id, key, value)
     *
     * \param v            a vector reference to return tags into
     * \param abs_start    a uint64 count of the start of the range of interest
     * \param abs_end      a uint64 count of the end of the range of interest
     * \param id           the unique ID of the block to make sure already deleted tags are not returned
     */
    void get_tags_in_range(std::vector<tag_t> &v,
                           uint64_t abs_start,
                           uint64_t abs_end,
			   long id);

    // -------------------------------------------------------------------------

  private:
    friend class buffer;
    friend OC_RUNTIME_API buffer_reader_sptr
      buffer_add_reader(buffer_sptr buf, int nzero_preload, block_sptr link);

    buffer_sptr  d_buffer;
    unsigned int d_read_index;       // in items [0,d->buffer.d_bufsize)
    uint64_t     d_abs_read_offset;  // num items seen since the start
    boost::weak_ptr<block> d_link;   // block that reads via this buffer reader

    //! constructor is private.  Use oc::buffer::add_reader to create instances
    buffer_reader(buffer_sptr buffer, unsigned int read_index, block_sptr link);
  };

  //! returns # of buffer_readers currently allocated
  OC_RUNTIME_API long buffer_reader_ncurrently_allocated ();

} /* namespace oc */

#endif /* INCLUDED_OC_RUNTIME_BUFFER_H */
