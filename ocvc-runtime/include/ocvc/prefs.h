/* -*- c++ -*- */
/*
 * Copyright 2006,2013 Free Software Foundation, Inc.
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

#ifndef INCLUDED_OC_PREFS_H
#define INCLUDED_OC_PREFS_H

#include <ocvc/api.h>
#include <string>
#include <map>
#include <ocvc/thread/thread.h>

namespace oc {

  typedef std::map< std::string, std::map<std::string, std::string> > config_map_t;
  typedef std::map< std::string, std::map<std::string, std::string> >::iterator config_map_itr;
  typedef std::map<std::string, std::string> config_map_elem_t;
  typedef std::map<std::string, std::string>::iterator config_map_elem_itr;

  /*!
   * \brief Base class for representing user preferences a la windows INI files.
   * \ingroup misc
   *
   * The real implementation is in Python, and is accessable from C++
   * via the magic of SWIG directors.
   */
  class OC_RUNTIME_API prefs
  {
  public:
    static prefs *singleton();
    static void set_singleton(prefs *p);

    prefs();
    virtual ~prefs();

    /*!
     * \brief Returns the configuration options as a string.
     */
    std::string to_string();

    /*!
     * \brief Saves the configuration settings to
     * ${HOME}/.ocvc/config.conf.
     *
     * WARNING: this will overwrite your current config.conf file.
     */
    void save();

    /*!
     * \brief Does \p section exist?
     */
    virtual bool has_section(const std::string &section);

    /*!
     * \brief Does \p option exist?
     */
    virtual bool has_option(const std::string &section,
                            const std::string &option);

    /*!
     * \brief If option exists return associated value; else
     * default_val.
     */
    virtual const std::string get_string(const std::string &section,
                                         const std::string &option,
                                         const std::string &default_val);

    /*!
     * \brief Set or add a string \p option to \p section with value
     * \p val.
     */
    virtual void set_string(const std::string &section,
                            const std::string &option,
                            const std::string &val);

    /*!
     * \brief If option exists and value can be converted to bool,
     * return it; else default_val.
     */
    virtual bool get_bool(const std::string &section,
                          const std::string &option,
                          bool default_val);

    /*!
     * \brief Set or add a bool \p option to \p section with value \p val.
     */
    virtual void set_bool(const std::string &section,
                          const std::string &option,
                          bool val);

    /*!
     * \brief If option exists and value can be converted to long,
     * return it; else default_val.
     */
    virtual long get_long(const std::string &section,
                          const std::string &option,
                          long default_val);

    /*!
     * \brief Set or add a long \p option to \p section with value \p val.
     */
    virtual void set_long(const std::string &section,
                          const std::string &option,
                          long val);

    /*!
     * \brief If option exists and value can be converted to double,
     * return it; else default_val.
     */
    virtual double get_double(const std::string &section,
                              const std::string &option,
                              double default_val);

    /*!
     * \brief Set or add a double \p option to \p section with value \p val.
     */
    virtual void set_double(const std::string &section,
                            const std::string &option,
                            double val);

  protected:
    virtual std::vector<std::string> _sys_prefs_filenames();
    virtual void _read_files();
    virtual void _convert_to_map(const std::string &conf);
    virtual char * option_to_env(std::string section, std::string option);

  private:
    oc::thread::mutex d_mutex;
    config_map_t d_config_map;
  };

} /* namespace oc */

#endif /* INCLUDED_OC_PREFS_H */
