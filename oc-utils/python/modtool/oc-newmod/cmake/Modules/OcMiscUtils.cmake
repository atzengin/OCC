# Copyright 2010-2011 Free Software Foundation, Inc.
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

if(DEFINED __INCLUDED_OC_MISC_UTILS_CMAKE)
    return()
endif()
set(__INCLUDED_OC_MISC_UTILS_CMAKE TRUE)

########################################################################
# Set global variable macro.
# Used for subdirectories to export settings.
# Example: include and library paths.
########################################################################
function(OC_SET_GLOBAL var)
    set(${var} ${ARGN} CACHE INTERNAL "" FORCE)
endfunction(OC_SET_GLOBAL)

########################################################################
# Set the pre-processor definition if the condition is true.
#  - def the pre-processor definition to set and condition name
########################################################################
function(OC_ADD_COND_DEF def)
    if(${def})
        add_definitions(-D${def})
    endif(${def})
endfunction(OC_ADD_COND_DEF)

########################################################################
# Check for a header and conditionally set a compile define.
#  - hdr the relative path to the header file
#  - def the pre-processor definition to set
########################################################################
function(OC_CHECK_HDR_N_DEF hdr def)
    include(CheckIncludeFileCXX)
    CHECK_INCLUDE_FILE_CXX(${hdr} ${def})
    OC_ADD_COND_DEF(${def})
endfunction(OC_CHECK_HDR_N_DEF)

########################################################################
# Include subdirectory macro.
# Sets the CMake directory variables,
# includes the subdirectory CMakeLists.txt,
# resets the CMake directory variables.
#
# This macro includes subdirectories rather than adding them
# so that the subdirectory can affect variables in the level above.
# This provides a work-around for the lack of convenience libraries.
# This way a subdirectory can append to the list of library sources.
########################################################################
macro(OC_INCLUDE_SUBDIRECTORY subdir)
    #insert the current directories on the front of the list
    list(INSERT _cmake_source_dirs 0 ${CMAKE_CURRENT_SOURCE_DIR})
    list(INSERT _cmake_binary_dirs 0 ${CMAKE_CURRENT_BINARY_DIR})

    #set the current directories to the names of the subdirs
    set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
    set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/${subdir})

    #include the subdirectory CMakeLists to run it
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)

    #reset the value of the current directories
    list(GET _cmake_source_dirs 0 CMAKE_CURRENT_SOURCE_DIR)
    list(GET _cmake_binary_dirs 0 CMAKE_CURRENT_BINARY_DIR)

    #pop the subdir names of the front of the list
    list(REMOVE_AT _cmake_source_dirs 0)
    list(REMOVE_AT _cmake_binary_dirs 0)
endmacro(OC_INCLUDE_SUBDIRECTORY)

########################################################################
# Check if a compiler flag works and conditionally set a compile define.
#  - flag the compiler flag to check for
#  - have the variable to set with result
########################################################################
macro(OC_ADD_CXX_COMPILER_FLAG_IF_AVAILABLE flag have)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG(${flag} ${have})
    if(${have})
        add_definitions(${flag})
    endif(${have})
endmacro(OC_ADD_CXX_COMPILER_FLAG_IF_AVAILABLE)

########################################################################
# Generates the .la libtool file
# This appears to generate libtool files that cannot be used by auto*.
# Usage OC_LIBTOOL(TARGET [target] DESTINATION [dest])
# Notice: there is not COMPONENT option, these will not get distributed.
########################################################################
function(OC_LIBTOOL)
    if(NOT DEFINED GENERATE_LIBTOOL)
        set(GENERATE_LIBTOOL OFF) #disabled by default
    endif()

    if(GENERATE_LIBTOOL)
        include(CMakeParseArgumentsCopy)
        CMAKE_PARSE_ARGUMENTS(OC_LIBTOOL "" "TARGET;DESTINATION" "" ${ARGN})

        find_program(LIBTOOL libtool)
        if(LIBTOOL)
            include(CMakeMacroLibtoolFile)
            CREATE_LIBTOOL_FILE(${OC_LIBTOOL_TARGET} /${OC_LIBTOOL_DESTINATION})
        endif(LIBTOOL)
    endif(GENERATE_LIBTOOL)

endfunction(OC_LIBTOOL)

########################################################################
# Do standard things to the library target
# - set target properties
# - make install rules
# Also handle ocvc custom naming conventions w/ extras mode.
########################################################################
function(OC_LIBRARY_FOO target)
    #parse the arguments for component names
    include(CMakeParseArgumentsCopy)
    CMAKE_PARSE_ARGUMENTS(OC_LIBRARY "" "RUNTIME_COMPONENT;DEVEL_COMPONENT" "" ${ARGN})

    #set additional target properties
    set_target_properties(${target} PROPERTIES SOVERSION ${LIBVER})

    #install the generated files like so...
    install(TARGETS ${target}
        LIBRARY DESTINATION ${OC_LIBRARY_DIR} COMPONENT ${OC_LIBRARY_RUNTIME_COMPONENT} # .so/.dylib file
        ARCHIVE DESTINATION ${OC_LIBRARY_DIR} COMPONENT ${OC_LIBRARY_DEVEL_COMPONENT}   # .lib file
        RUNTIME DESTINATION ${OC_RUNTIME_DIR} COMPONENT ${OC_LIBRARY_RUNTIME_COMPONENT} # .dll file
    )

    #extras mode enabled automatically on linux
    if(NOT DEFINED LIBRARY_EXTRAS)
        set(LIBRARY_EXTRAS ${LINUX})
    endif()

    #special extras mode to enable alternative naming conventions
    if(LIBRARY_EXTRAS)

        #create .la file before changing props
        OC_LIBTOOL(TARGET ${target} DESTINATION ${OC_LIBRARY_DIR})

        #give the library a special name with ultra-zero soversion
        set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_NAME ${target}-${LIBVER} SOVERSION "0.0.0")
        set(target_name lib${target}-${LIBVER}.so.0.0.0)

        #custom command to generate symlinks
        add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${target_name} ${CMAKE_CURRENT_BINARY_DIR}/lib${target}.so
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${target_name} ${CMAKE_CURRENT_BINARY_DIR}/lib${target}-${LIBVER}.so.0
            COMMAND ${CMAKE_COMMAND} -E touch ${target_name} #so the symlinks point to something valid so cmake 2.6 will install
        )

        #and install the extra symlinks
        install(
            FILES
            ${CMAKE_CURRENT_BINARY_DIR}/lib${target}.so
            ${CMAKE_CURRENT_BINARY_DIR}/lib${target}-${LIBVER}.so.0
            DESTINATION ${OC_LIBRARY_DIR} COMPONENT ${OC_LIBRARY_RUNTIME_COMPONENT}
        )

    endif(LIBRARY_EXTRAS)
endfunction(OC_LIBRARY_FOO)

########################################################################
# Create a dummy custom command that depends on other targets.
# Usage:
#   OC_GEN_TARGET_DEPS(unique_name target_deps <target1> <target2> ...)
#   ADD_CUSTOM_COMMAND(<the usual args> ${target_deps})
#
# Custom command cant depend on targets, but can depend on executables,
# and executables can depend on targets. So this is the process:
########################################################################
function(OC_GEN_TARGET_DEPS name var)
    file(
        WRITE ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp.in
        "int main(void){return 0;}\n"
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp
    )
    add_executable(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp)
    if(ARGN)
        add_dependencies(${name} ${ARGN})
    endif(ARGN)

    if(CMAKE_CROSSCOMPILING)
        set(${var} "DEPENDS;${name}" PARENT_SCOPE) #cant call command when cross
    else()
        set(${var} "DEPENDS;${name};COMMAND;${name}" PARENT_SCOPE)
    endif()
endfunction(OC_GEN_TARGET_DEPS)
