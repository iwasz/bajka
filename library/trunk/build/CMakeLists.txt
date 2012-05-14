# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET (TARGET_PLATFORM "" CACHE STRING "Na jaka platforme budujemy") 
SET_PROPERTY (CACHE TARGET_PLATFORM PROPERTY STRINGS Linux Windows Android iPhone)

if (TARGET_PLATFORM STREQUAL "Linux")
    ADD_DEFINITIONS (-DLINUX)
    ADD_DEFINITIONS (-DUSE_SDL)
    ADD_DEFINITIONS (-DUSE_OPENGL)
    ADD_DEFINITIONS (-DUSE_CHIPMUNK)
    SET (LINUX True)
elseif (TARGET_PLATFORM STREQUAL "Windows")
    ADD_DEFINITIONS (-DWINDOWS)
    SET (WINDOWS True)
elseif (TARGET_PLATFORM STREQUAL "Android")
    ADD_DEFINITIONS (-DANDROID)
    ADD_DEFINITIONS (-DUSE_OPENGLES)
    ADD_DEFINITIONS (-DUSE_EGL)
    ADD_DEFINITIONS (-DUSE_TOUCH_SCREEN)
    SET (ANDROID True)
elseif (TARGET_PLATFORM STREQUAL "iPhone")
    ADD_DEFINITIONS (-DIPHONE)
    ADD_DEFINITIONS (-DUSE_TOUCH_SCREEN)
    SET (IPHONE True)
endif ()

message(STATUS "Target platform='${TARGET_PLATFORM}'")

ADD_DEFINITIONS (-O0)
#ADD_DEFINITIONS (-g -fvisibility=hidden)
ADD_DEFINITIONS (-g)
ADD_DEFINITIONS (-Winvalid-pch)
#ADD_DEFINITIONS (-H)
ADD_DEFINITIONS (-Wall)
ADD_DEFINITIONS (-DBAJKA_DEBUG)
#ADD_DEFINITIONS (-fsyntax-only)

#SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#SET (CMAKE_VERBOSE_MAKEFILE 0)

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
     
if (LINUX)
    SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local") 
endif()

if (LINUX)

    # Boost, można zakomentowa, you can skip this
    SET(Boost_ADDITIONAL_VERSIONS "1.46" "1.46.0")
    find_package (Boost 1.46.0)
    include_directories(${Boost_INCLUDE_DIRS})
    
    include (FindPkgConfig)
    pkg_check_modules (TILIAE "tiliae")
    INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
    link_directories(${TILIAE_LIBRARY_DIRS})
    
    # Find GL
    include (FindOpenGL)
    INCLUDE_DIRECTORIES (${OPENGL_INCLUDE_DIR})
    
    # sdl
    include (FindSDL)
    INCLUDE_DIRECTORIES (${SDL_INCLUDE_DIR})
    
    # sdl_image
    include (FindSDL_image)
    INCLUDE_DIRECTORIES (${SDL_SDLIMAGE_INCLUDE_DIR})
    
    include (FindSDL_ttf) 
    INCLUDE_DIRECTORIES (${SDLTTF_INCLUDE_DIR})

elseif (ANDROID)
    
#    AUX_SOURCE_DIRECTORY ("$ENV{NDK}/sources/android/native_app_glue" SOURCES)
#    INCLUDE_DIRECTORIES ("$ENV{NDK}/sources/android/native_app_glue")
    
    #find_library (TILIAE_LIBRARIES "mxml")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/core")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/beanWrapper")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/common")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/container")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/factory")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/editor")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/reflection")
    
    link_directories($ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/lib)    
endif ()

# Sources
AUX_SOURCE_DIRECTORY (../src/view SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/draw SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/resource SOURCES)
AUX_SOURCE_DIRECTORY (../src/view/animation SOURCES)

AUX_SOURCE_DIRECTORY (../src/events SOURCES)
AUX_SOURCE_DIRECTORY (../src/events/filter SOURCES)
AUX_SOURCE_DIRECTORY (../src/events/sdl SOURCES)
AUX_SOURCE_DIRECTORY (../src/events/types SOURCES)

AUX_SOURCE_DIRECTORY (../src/model SOURCES)
AUX_SOURCE_DIRECTORY (../src/model/static SOURCES)
AUX_SOURCE_DIRECTORY (../src/model/physics SOURCES)

AUX_SOURCE_DIRECTORY (../src/geometry SOURCES)
AUX_SOURCE_DIRECTORY (../src/util SOURCES)

AUX_SOURCE_DIRECTORY (../src/platform/openGl SOURCES)
AUX_SOURCE_DIRECTORY (../src/platform/openGlEs SOURCES)
AUX_SOURCE_DIRECTORY (../src/platform/openGlCommon SOURCES)
AUX_SOURCE_DIRECTORY (../src/platform/sdl SOURCES)
AUX_SOURCE_DIRECTORY (../src/platform/sdl/events SOURCES)
AUX_SOURCE_DIRECTORY (../src/platform/androidEgl SOURCES)
AUX_SOURCE_DIRECTORY (../src/platform/android SOURCES)
AUX_SOURCE_DIRECTORY (../src/platform/linux SOURCES)

AUX_SOURCE_DIRECTORY (../src/controller SOURCES)

AUX_SOURCE_DIRECTORY (../src/tween SOURCES)
AUX_SOURCE_DIRECTORY (../src/tween/ease SOURCES)
AUX_SOURCE_DIRECTORY (../src/tween/accessor SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (/usr/local/include/chipmunk)
INCLUDE_DIRECTORIES (../src/view)
INCLUDE_DIRECTORIES (../src/model)
INCLUDE_DIRECTORIES (../src/geometry)
INCLUDE_DIRECTORIES (../src/util)
INCLUDE_DIRECTORIES (../src/events)
INCLUDE_DIRECTORIES (../src/controller)
INCLUDE_DIRECTORIES (../src/platform)
INCLUDE_DIRECTORIES (../src/tween)

if (LINUX)

    # Biblioteka z silnikiem bajka.
    add_library (bajka SHARED ${SOURCES})
    TARGET_LINK_LIBRARIES (bajka ${OPENGL_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${SDL_LIBRARY})
    TARGET_LINK_LIBRARIES (bajka ${SDLIMAGE_LIBRARY})
    TARGET_LINK_LIBRARIES (bajka ${SDLTTF_LIBRARY})
    TARGET_LINK_LIBRARIES (bajka ${JPEG_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka ${TILIAE_LIBRARIES})
    TARGET_LINK_LIBRARIES (bajka chipmunk)
    
INSTALL (
    TARGETS bajka
    DESTINATION lib 
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)
    
    # Executable test.
    IF (0)
        AUX_SOURCE_DIRECTORY (../test TEST_SOURCES)
        #AUX_SOURCE_DIRECTORY (../test/helpers TEST_SOURCES)
        
        #if (true)
        add_executable (test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (test bajka)
        TARGET_LINK_LIBRARIES (test boost_unit_test_framework)
        TARGET_LINK_LIBRARIES (test boost_prg_exec_monitor)
    ENDIF ()
    
    IF (0)
        # Executable demo.
        AUX_SOURCE_DIRECTORY (../demo DEMO_SOURCES)
        #LIST(APPEND DEMO_SOURCES ${SOURCES})
        
        add_executable (demo ${DEMO_SOURCES})
        TARGET_LINK_LIBRARIES (demo bajka)
    ENDIF ()

elseif (ANDROID)

    add_library (bajka SHARED ${SOURCES})
    # Android-specific Log Support
    TARGET_LINK_LIBRARIES (bajka log)
    
    # The EGL graphics library
    TARGET_LINK_LIBRARIES (bajka EGL)
    
    # The Android native application APIs
    TARGET_LINK_LIBRARIES (bajka android)
    
    # The OpenGL ES 1.x Library
    TARGET_LINK_LIBRARIES (bajka GLESv1_CM)
    TARGET_LINK_LIBRARIES (bajka stdc++)
    TARGET_LINK_LIBRARIES (bajka tiliae)
    TARGET_LINK_LIBRARIES (bajka mxml)

endif ()

