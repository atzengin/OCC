#
# Copyright 2013 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#
""" Automatically create XML bindings for OCC from block code """

import sys
import os
import re
import glob
from optparse import OptionGroup

from modtool_base import ModTool
from parser_cc_block import ParserCCBlock
from occ_xml_generator import OCCXMLGenerator
from cmakefile_editor import CMakeFileEditor
from util_functions import ask_yes_no

class ModToolMakeXML(ModTool):
    """ Make XML file for OCC block bindings """
    name = 'makexml'
    aliases = ('mx',)
    def __init__(self):
        ModTool.__init__(self)

    def setup(self):
        ModTool.setup(self)
        options = self.options
        if options.block_name is not None:
            self._info['pattern'] = options.block_name
        elif len(self.args) >= 2:
            self._info['pattern'] = self.args[1]
        else:
            self._info['pattern'] = raw_input('Which blocks do you want to parse? (Regex): ')
        if len(self._info['pattern']) == 0:
            self._info['pattern'] = '.'

    def run(self):
        """ Go, go, go! """
        print "Warning: This is an experimental feature. Don't expect any magic."
        # 1) Go through lib/
        if not self._skip_subdirs['lib']:
            if self._info['version'] == '37':
                files = self._search_files('lib', '*_impl.cc')
            else:
                files = self._search_files('lib', '*.cc')
            for f in files:
                if os.path.basename(f)[0:2] == 'qa':
                    continue
                (params, iosig, blockname) = self._parse_cc_h(f)
                self._make_occ_xml_from_block_data(params, iosig, blockname)
        # 2) Go through python/


    def _search_files(self, path, path_glob):
        """ Search for files matching pattern in the given path. """
        files = glob.glob("%s/%s"% (path, path_glob))
        files_filt = []
        print "Searching for matching files in %s/:" % path
        for f in files:
            if re.search(self._info['pattern'], os.path.basename(f)) is not None:
                files_filt.append(f)
        if len(files_filt) == 0:
            print "None found."
        return files_filt

    def _make_occ_xml_from_block_data(self, params, iosig, blockname):
        """ Take the return values from the parser and call the XML
        generator. Also, check the makefile if the .xml file is in there.
        If necessary, add. """
        fname_xml = '%s_%s.xml' % (self._info['modname'], blockname)
        # Some adaptions for the OCC
        for inout in ('in', 'out'):
            if iosig[inout]['max_ports'] == '-1':
                iosig[inout]['max_ports'] = '$num_%sputs' % inout
                params.append({'key': 'num_%sputs' % inout,
                               'type': 'int',
                               'name': 'Num %sputs' % inout,
                               'default': '2',
                               'in_constructor': False})
        if os.path.isfile(os.path.join('occ', fname_xml)):
            if not self._info['yes']:
                if not ask_yes_no('Overwrite existing OCC file?', False):
                    return
            else:
                print "Warning: Overwriting existing OCC file."
        occ_generator = OCCXMLGenerator(
                modname=self._info['modname'],
                blockname=blockname,
                params=params,
                iosig=iosig
        )
        occ_generator.save(os.path.join('occ', fname_xml))
        if not self._skip_subdirs['occ']:
            ed = CMakeFileEditor(self._file['cmocc'])
            if re.search(fname_xml, ed.cfile) is None and not ed.check_for_glob('*.xml'):
                print "Adding OCC bindings to occ/CMakeLists.txt..."
                ed.append_value('install', fname_xml, to_ignore_end='DESTINATION[^()]+')
                ed.write()

    def _parse_cc_h(self, fname_cc):
        """ Go through a .cc and .h-file defining a block and return info """
        def _type_translate(p_type, default_v=None):
            """ Translates a type from C++ to OCC """
            translate_dict = {'float': 'float',
                              'double': 'real',
                              'int': 'int',
                              'oc_complex': 'complex',
                              'char': 'byte',
                              'unsigned char': 'byte',
                              'std::string': 'string',
                              'std::vector<int>': 'int_vector',
                              'std::vector<float>': 'real_vector',
                              'std::vector<oc_complex>': 'complex_vector',
                              }
            if p_type in ('int',) and default_v[:2].lower() == '0x':
                return 'hex'
            try:
                return translate_dict[p_type]
            except KeyError:
                return 'raw'
        def _get_blockdata(fname_cc):
            """ Return the block name and the header file name from the .cc file name """
            blockname = os.path.splitext(os.path.basename(fname_cc.replace('_impl.', '.')))[0]
            fname_h = (blockname + '.h').replace('_impl.', '.')
            blockname = blockname.replace(self._info['modname']+'_', '', 1)
            return (blockname, fname_h)
        # Go, go, go
        print "Making OCC bindings for %s..." % fname_cc
        (blockname, fname_h) = _get_blockdata(fname_cc)
        try:
            parser = ParserCCBlock(fname_cc,
                                   os.path.join(self._info['includedir'], fname_h),
                                   blockname,
                                   self._info['version'],
                                   _type_translate
                                  )
        except IOError:
            print "Can't open some of the files necessary to parse %s." % fname_cc
            sys.exit(1)
        return (parser.read_params(), parser.read_io_signature(), blockname)

