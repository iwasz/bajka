cmake_minimum_required(VERSION 2.6)
project(libuvc)

SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local") 
SET (CMAKE_PREFIX_PATH "/home/iwasz/local")

find_library(LIBUSB_LIBRARY_NAMES usb-1.0
	PATHS /opt/local/lib)

find_path(LIBUSB_INCLUDE_DIR libusb-1.0/libusb.h
	PATHS /opt/local/include)

include (FindPkgConfig)
pkg_check_modules (LIBUSB REQUIRED "libusb-1.0")
INCLUDE_DIRECTORIES (${LIBUSB_INCLUDE_DIRS})
link_directories(${LIBUSB_LIBRARY_DIRS})

SET(CMAKE_C_FLAGS_DEBUG "-g -DUVC_DEBUGGING")

include_directories(${libuvc_SOURCE_DIR}/include)

add_library(uvc SHARED src/ctrl.c src/device.c src/diag.c
                       src/frame.c src/init.c src/stream.c
                       src/misc.c)

TARGET_LINK_LIBRARIES (uvc ${LIBUSB_LIBRARIES})

add_executable(test src/test.c)
target_link_libraries(test uvc ${LIBUSB_LIBRARIES} opencv_highgui opencv_core)

install(TARGETS uvc
  LIBRARY DESTINATION lib
)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/utlist.h"
  DESTINATION include)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/libuvc/libuvc.h"
  DESTINATION include/libuvc)

