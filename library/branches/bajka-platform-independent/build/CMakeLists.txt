# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

project (bajka)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if (CMAKE_BUILD_TYPE)
    if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
        message(FATAL_ERROR "CMAKE_BUILD_TYPE must be one of '' (None) or 'Release'")
    endif()
    
    SET (RELEASE true)
elseif()
    SET (RELEASE false)        
endif() 

SET (CMAKE_C_FLAGS "-g -fPIC -Wall -O0 -Winvalid-pch -ffunction-sections -fdata-sections")
SET (CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
SET (CMAKE_C_FLAGS_RELEASE "-g0 -fPIC -Wall -O3 -Winvalid-pch -ffunction-sections -fdata-sections -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

if (ANDROID)
    ADD_DEFINITIONS (-DANDROID)
else()
    ADD_DEFINITIONS (-DLINUX)
endif()

SET (CMAKE_VERBOSE_MAKEFILE 0)
SET (WITH_CHIPMUNK          OFF CACHE BOOL "")
SET (WITH_PNG               ON CACHE BOOL "")
SET (WITH_JPEG              OFF CACHE BOOL "")
SET (WITH_FREETYPE          ON CACHE BOOL "")
SET (WITH_CORE_STRING       OFF CACHE BOOL "")

if (WITH_CORE_STRING)
    add_definitions (-DWITH_CORE_STRING)
endif ()

if (WITH_CHIPMUNK)
    ADD_DEFINITIONS (-DWITH_CHIPMUNK)
endif()

if (WITH_PNG)
    ADD_DEFINITIONS (-DWITH_PNG)
endif()

if (WITH_JPEG)
    ADD_DEFINITIONS (-DWITH_JPEG)
endif()

if (WITH_FREETYPE)
    ADD_DEFINITIONS (-DWITH_FREETYPE)
endif()

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/../src/"
    DESTINATION "include/bajka" 
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*.svn*" EXCLUDE
    PATTERN "*test*" EXCLUDE)

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/pc/"
    DESTINATION "lib/pkgconfig"
    FILES_MATCHING PATTERN "*.pc"
    PATTERN "*.svn*" EXCLUDE)

if (NOT ANDROID)     
    SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local") 
    SET (CMAKE_PREFIX_PATH "/home/iwasz/local")
    INCLUDE_DIRECTORIES ("/home/iwasz/local/include")
    link_directories("/home/iwasz/local/lib")
endif()

#Boost
find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include (FindPkgConfig)
pkg_check_modules (TILIAE REQUIRED "tiliae")
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

pkg_check_modules (JANSSON REQUIRED "jansson")
INCLUDE_DIRECTORIES (${JANSSON_INCLUDE_DIRS})
link_directories(${JANSSON_LIBRARY_DIRS})

if (WITH_PNG)
    pkg_check_modules (PNG REQUIRED "libpng")
    INCLUDE_DIRECTORIES (${PNG_INCLUDE_DIRS})
    link_directories(${PNG_LIBRARY_DIRS})
endif ()

if (WITH_JPEG)
    FIND_PACKAGE (JPEG)
    INCLUDE_DIRECTORIES (${JPEG_INCLUDE_DIR})
endif ()    

if (WITH_FREETYPE)
    pkg_check_modules (FREETYPE REQUIRED "freetype2")
    INCLUDE_DIRECTORIES (${FREETYPE_INCLUDE_DIRS})
    link_directories(${FREETYPE_LIBRARY_DIRS})
endif ()

IF(NOT ANDROID)
    # Find GL
    include (FindOpenGL)
    INCLUDE_DIRECTORIES (${OPENGL_INCLUDE_DIR})
    
    # Chipmunk
    INCLUDE_DIRECTORIES ("/usr/local/include/chipmunk")
    INCLUDE_DIRECTORIES ("/home/iwasz/local/include/chipmunk")
ELSE()        
    # TODO - jakoś automagicznie znaleźć się nie da?
    INCLUDE_DIRECTORIES ("/home/iwasz/local/share/android-toolchain/arm-linux-androideabi/include/chipmunk")
    link_directories($ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/lib)    
ENDIF()

# Sources
AUX_SOURCE_DIRECTORY (../src/view SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/draw SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/resource SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/animation SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/openGl SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/graphicFile SOURCES)

if (WITH_FREETYPE) 
    AUX_SOURCE_DIRECTORY (../src/view/freetype SOURCES)
endif ()

AUX_SOURCE_DIRECTORY (../src/events SOURCES)
AUX_SOURCE_DIRECTORY (../src/events/types SOURCES)

AUX_SOURCE_DIRECTORY (../src/model SOURCES)
AUX_SOURCE_DIRECTORY (../src/model/static SOURCES)

if (WITH_CHIPMUNK)
    AUX_SOURCE_DIRECTORY (../src/model/physics SOURCES)
endif ()

AUX_SOURCE_DIRECTORY (../src/model/layout SOURCES)
AUX_SOURCE_DIRECTORY (../src/model/manager SOURCES)

AUX_SOURCE_DIRECTORY (../src/geometry SOURCES)
AUX_SOURCE_DIRECTORY (../src/util SOURCES)

AUX_SOURCE_DIRECTORY (../src/controller SOURCES)

AUX_SOURCE_DIRECTORY (../src/tween SOURCES)
AUX_SOURCE_DIRECTORY (../src/tween/ease SOURCES)
AUX_SOURCE_DIRECTORY (../src/tween/accessor SOURCES)
AUX_SOURCE_DIRECTORY (../src/tween/parser SOURCES)

AUX_SOURCE_DIRECTORY (../src/sound SOURCES)
AUX_SOURCE_DIRECTORY (../src/sound/pcm SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (../src)

# Biblioteka z silnikiem bajka.
if (ANDROID)
    add_library (bajka STATIC ${SOURCES})   
else ()
    add_library (bajka SHARED ${SOURCES})
endif ()

if (NOT ANDROID)
    TARGET_LINK_LIBRARIES (bajka ${OPENGL_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${TILIAE_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${JANSSON_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${PNG_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${ZLIB_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${JPEG_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${FREETYPE_LIBRARIES})
endif ()

if (WITH_CHIPMUNK)
    TARGET_LINK_LIBRARIES (bajka chipmunk)
endif()
    
# Executable test.
IF (0)
    AUX_SOURCE_DIRECTORY (../test TEST_SOURCES)
    
    #if (true)
    add_executable (test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (test bajka)
    TARGET_LINK_LIBRARIES (test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (test boost_prg_exec_monitor)
ENDIF ()
    
INSTALL (
    TARGETS bajka
    DESTINATION lib 
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/pc/bajka.pc.in ${CMAKE_CURRENT_BINARY_DIR}/pc/bajka.pc @ONLY)
    