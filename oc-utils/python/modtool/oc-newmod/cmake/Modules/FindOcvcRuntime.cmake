INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_OCVC_RUNTIME ocvc-runtime)

if(PC_OCVC_RUNTIME_FOUND)
  # look for include files
  FIND_PATH(
    OCVC_RUNTIME_INCLUDE_DIRS
    NAMES ocvc/top_block.h
    HINTS $ENV{OCVC_RUNTIME_DIR}/include
          ${PC_OCVC_RUNTIME_INCLUDE_DIRS}
          ${CMAKE_INSTALL_PREFIX}/include
    PATHS /usr/local/include
          /usr/include
    )

  # look for libs
  FIND_LIBRARY(
    OCVC_RUNTIME_LIBRARIES
    NAMES ocvc-runtime
    HINTS $ENV{OCVC_RUNTIME_DIR}/lib
          ${PC_OCVC_RUNTIME_LIBDIR}
          ${CMAKE_INSTALL_PREFIX}/lib/
          ${CMAKE_INSTALL_PREFIX}/lib64/
    PATHS /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
    )

  set(OCVC_RUNTIME_FOUND ${PC_OCVC_RUNTIME_FOUND})
endif(PC_OCVC_RUNTIME_FOUND)

INCLUDE(FindPackageHandleStandardArgs)
# do not check OCVC_RUNTIME_INCLUDE_DIRS, is not set when default include path us used.
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OCVC_RUNTIME DEFAULT_MSG OCVC_RUNTIME_LIBRARIES)
MARK_AS_ADVANCED(OCVC_RUNTIME_LIBRARIES OCVC_RUNTIME_INCLUDE_DIRS)
