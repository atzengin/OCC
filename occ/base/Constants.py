"""
Copyright 2008, 2009 Free Software Foundation, Inc.
This file is part of GNU Radio

OpenCV Companion is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

OpenCV Companion is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
"""

import os

#data files
DATA_DIR = os.path.dirname(__file__)
FLOW_GRAPH_DTD = os.path.join(DATA_DIR, 'flow_graph.dtd')
BLOCK_TREE_DTD = os.path.join(DATA_DIR, 'block_tree.dtd')
