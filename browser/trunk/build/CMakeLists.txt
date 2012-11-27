# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

ADD_DEFINITIONS (-DUSE_SDL)
ADD_DEFINITIONS (-DUSE_OPENGL)
ADD_DEFINITIONS (-DUSE_CHIPMUNK)

ADD_DEFINITIONS (-O0)
#ADD_DEFINITIONS (-g -fvisibility=hidden)
ADD_DEFINITIONS (-g)
ADD_DEFINITIONS (-Winvalid-pch)
#ADD_DEFINITIONS (-H)
ADD_DEFINITIONS (-Wall)
ADD_DEFINITIONS (-DBAJKA_DEBUG)
ADD_DEFINITIONS (-DREFLECTION_ENABLED)
#ADD_DEFINITIONS (-fsyntax-only)

if (ANDROID)
    ADD_DEFINITIONS (-static)
    SET (EXECUTABLE_OUTPUT_PATH "./")
    SET (LIBRARY_OUTPUT_PATH "./android/libs/armeabi-v7a")
endif ()
     
# Boost, można zakomentowa, you can skip this
find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include (FindPkgConfig)
pkg_check_modules (TILIAE REQUIRED "tiliae")
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

pkg_check_modules (BAJKA REQUIRED "bajka")
INCLUDE_DIRECTORIES (${BAJKA_INCLUDE_DIRS})
link_directories(${BAJKA_LIBRARY_DIRS})

if (NOT ANDROID)
    pkg_check_modules (SHELL REQUIRED "shell-linux")
else ()
    pkg_check_modules (SHELL REQUIRED "shell-android")
endif ()

INCLUDE_DIRECTORIES (${SHELL_INCLUDE_DIRS})
link_directories(${SHELL_LIBRARY_DIRS})

if (NOT ANDROID)
    pkg_check_modules (GLEW REQUIRED "glew")
    INCLUDE_DIRECTORIES (${GLEW_INCLUDE_DIRS})
    link_directories(${GLEW_LIBRARY_DIRS})
endif ()

# Sources
AUX_SOURCE_DIRECTORY ("$ENV{NDK}/sources/android/native_app_glue" SOURCES)
INCLUDE_DIRECTORIES ("$ENV{NDK}/sources/android/native_app_glue")
AUX_SOURCE_DIRECTORY (../src SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (../src)

if (NOT ANDROID)
    add_executable (browser ${SOURCES})
else ()
    add_library (browser SHARED ${SOURCES})
endif ()

if (NOT ANDROID)
    TARGET_LINK_LIBRARIES (browser boost_program_options)
endif ()

TARGET_LINK_LIBRARIES (browser ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (browser ${BAJKA_LIBRARIES})
TARGET_LINK_LIBRARIES (browser ${SHELL_LIBRARIES})
TARGET_LINK_LIBRARIES (browser chipmunk)

if (ANDROID)
    pkg_check_modules (MXML REQUIRED "mxml")
    link_directories(${MXML_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (browser ${MXML_LIBRARIES})

    pkg_check_modules (JANSSON REQUIRED "jansson")
    INCLUDE_DIRECTORIES (${JANSSON_INCLUDE_DIRS})
    link_directories(${JANSSON_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (browser ${JANSSON_LIBRARIES})
    
    pkg_check_modules (PNG REQUIRED "libpng")
    INCLUDE_DIRECTORIES (${PNG_INCLUDE_DIRS})
    link_directories(${PNG_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (browser ${PNG_LIBRARIES})
    
    pkg_check_modules (ZLIB REQUIRED "zlib")
    INCLUDE_DIRECTORIES (${ZLIB_INCLUDE_DIRS})
    link_directories(${ZLIB_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (browser ${ZLIB_LIBRARIES})
    
    FIND_PACKAGE (JPEG)
    INCLUDE_DIRECTORIES (${JPEG_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES (browser ${JPEG_LIBRARIES})
    
    pkg_check_modules (FREETYPE REQUIRED "freetype2")
    INCLUDE_DIRECTORIES (${FREETYPE_INCLUDE_DIRS})
    link_directories(${FREETYPE_LIBRARY_DIRS})    
    TARGET_LINK_LIBRARIES (browser ${FREETYPE_LIBRARIES})
    
    # Android-specific Log Support
    TARGET_LINK_LIBRARIES (browser log)
    
    # The EGL graphics library
    TARGET_LINK_LIBRARIES (browser EGL)
    
    # The Android native application APIs
    TARGET_LINK_LIBRARIES (browser android)
    
    # The OpenGL ES 1.x Library
    TARGET_LINK_LIBRARIES (browser GLESv2)
    TARGET_LINK_LIBRARIES (browser stdc++)
endif ()


if (NOT ANDROID)
    TARGET_LINK_LIBRARIES (browser boost_filesystem)
    TARGET_LINK_LIBRARIES (browser boost_system)
    TARGET_LINK_LIBRARIES (browser ${GLEW_LIBRARIES})
endif ()
