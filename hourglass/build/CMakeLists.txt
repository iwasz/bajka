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
    ADD_DEFINITIONS (-DUSE_CHIPMUNK)
    SET (ANDROID True)
elseif (TARGET_PLATFORM STREQUAL "iPhone")
    ADD_DEFINITIONS (-DIPHONE)
    ADD_DEFINITIONS (-DUSE_TOUCH_SCREEN)
    SET (IPHONE True)
endif ()

message(STATUS "Target platform='${TARGET_PLATFORM}'")

ADD_DEFINITIONS (-O0)
ADD_DEFINITIONS (-g)
ADD_DEFINITIONS (-Winvalid-pch)
ADD_DEFINITIONS (-Wall)
ADD_DEFINITIONS (-DBAJKA_DEBUG)

#SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
SET (CMAKE_VERBOSE_MAKEFILE 0)

if (LINUX)
    SET (CMAKE_PREFIX_PATH "/home/iwasz/local")
    INCLUDE_DIRECTORIES ("/home/iwasz/local/include")
    link_directories("/home/iwasz/local/lib")
    
    # Boost, można zakomentowa, you can skip this
    SET(Boost_ADDITIONAL_VERSIONS "1.46" "1.46.0")
    find_package (Boost 1.46.0)
    include_directories(${Boost_INCLUDE_DIRS})
    
    include (FindPkgConfig)
    pkg_check_modules (TILIAE "tiliae")
    INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
    link_directories(${TILIAE_LIBRARY_DIRS})

    pkg_check_modules (BAJKA "bajka")
    INCLUDE_DIRECTORIES (${BAJKA_INCLUDE_DIRS})
    link_directories(${BAJKA_LIBRARY_DIRS})
    
    # Find GL
    include (FindOpenGL)
    INCLUDE_DIRECTORIES (${OPENGL_INCLUDE_DIR})
    
    # sdl
    include (FindSDL)
    INCLUDE_DIRECTORIES (${SDL_INCLUDE_DIR})
    
    # sdl_image
    include (FindSDL_image)
    INCLUDE_DIRECTORIES (${SDL_SDLIMAGE_INCLUDE_DIR})
    
    pkg_check_modules (SDLTTF "tiliae")   
    INCLUDE_DIRECTORIES (${SDLTTF_INCLUDE_DIR})
    link_directories(${SDLTTF_LIBRARY_DIRS})

    INCLUDE_DIRECTORIES ("/usr/local/include/chipmunk")
    INCLUDE_DIRECTORIES ("/home/iwasz/local/include/chipmunk")
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

    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/controller")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/events")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/geometry")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/model")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/platform")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/tween")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/util")
    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/bajka/view")

    INCLUDE_DIRECTORIES ("/home/iwasz/local/share/android-toolchain/user/include/chipmunk")
    
    link_directories($ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/lib)    
endif ()

# Sources
AUX_SOURCE_DIRECTORY (../src SOURCES)

INCLUDE_DIRECTORIES (../src)

if (LINUX)       
    add_executable (hourglass ${SOURCES})
    TARGET_LINK_LIBRARIES (hourglass ${BAJKA_LIBRARIES})    
    TARGET_LINK_LIBRARIES (hourglass chipmunk)    
elseif (ANDROID)
    add_library (hourglass SHARED ${SOURCES})
    
    # Android-specific Log Support
    TARGET_LINK_LIBRARIES (hourglass log)
    
    # The EGL graphics library
    TARGET_LINK_LIBRARIES (hourglass EGL)
    
    # The Android native application APIs
    TARGET_LINK_LIBRARIES (hourglass android)
    
    # The OpenGL ES 1.x Library
    TARGET_LINK_LIBRARIES (hourglass GLESv1_CM)
    TARGET_LINK_LIBRARIES (hourglass stdc++)
    TARGET_LINK_LIBRARIES (hourglass bajka)    
    TARGET_LINK_LIBRARIES (hourglass tiliae)
    TARGET_LINK_LIBRARIES (hourglass mxml)
    TARGET_LINK_LIBRARIES (hourglass chipmunk)    
    
endif ()

