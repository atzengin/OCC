# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of OpenCv Companion
#
# OpenCv Companion is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# OpenCv Companion is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with OpenCv Companion; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
OC_PYTHON_INSTALL(FILES
    Block.py
    Colors.py
    Constants.py
    Connection.py
    Element.py
    FlowGraph.py
    Param.py
    Platform.py
    Port.py
    Utils.py
    ActionHandler.py
    Actions.py
    Bars.py
    BlockTreeWindow.py
    Dialogs.py
    DrawingArea.py
    FileDialogs.py
    MainWindow.py
    Messages.py
    NotebookPage.py
    PropsDialog.py
    Preferences.py
    StateCache.py
    __init__.py
    DESTINATION ${OC_PYTHON_DIR}/ocvc/occ/gui
    COMPONENT "occ"
)
