INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_OPENCV opencv)

FIND_PATH(
    OPENCV_INCLUDE_DIRS
    NAMES opencv/api.h
    HINTS $ENV{OPENCV_DIR}/include
        ${PC_OPENCV_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREEFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    OPENCV_LIBRARIES
    NAMES ocvc-opencv
    HINTS $ENV{OPENCV_DIR}/lib
        ${PC_OPENCV_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OPENCV DEFAULT_MSG OPENCV_LIBRARIES OPENCV_INCLUDE_DIRS)
MARK_AS_ADVANCED(OPENCV_LIBRARIES OPENCV_INCLUDE_DIRS)

