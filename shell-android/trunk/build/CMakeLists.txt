# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

ADD_DEFINITIONS (-DUSE_OPENGL)
ADD_DEFINITIONS (-DUSE_CHIPMUNK)
ADD_DEFINITIONS (-DANDROID)
ADD_DEFINITIONS (-DUSE_OPENGLES)    
ADD_DEFINITIONS (-DUSE_TOUCH_SCREEN)
    
ADD_DEFINITIONS (-O0)
#ADD_DEFINITIONS (-g -fvisibility=hidden)
ADD_DEFINITIONS (-g)
ADD_DEFINITIONS (-Winvalid-pch)
#ADD_DEFINITIONS (-H)
ADD_DEFINITIONS (-Wall)
ADD_DEFINITIONS (-DBAJKA_DEBUG)
#ADD_DEFINITIONS (-fsyntax-only)

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/../src/"
    DESTINATION "include/shell-android" 
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*.svn*" EXCLUDE
    PATTERN "*test*" EXCLUDE)

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/pc/"
    DESTINATION "lib/pkgconfig"
    FILES_MATCHING PATTERN "*.pc"
    PATTERN "*.svn*" EXCLUDE)
     
# Boost, można zakomentowa, you can skip this
find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include (FindPkgConfig)
pkg_check_modules (TILIAE REQUIRED "tiliae")
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

pkg_check_modules (BAJKA REQUIRED "bajka")
INCLUDE_DIRECTORIES (${BAJKA_INCLUDE_DIRS})
link_directories(${BAJKA_LIBRARY_DIRS})

# Sources
AUX_SOURCE_DIRECTORY (../src SOURCES)
AUX_SOURCE_DIRECTORY (../src/sound SOURCES)
#AUX_SOURCE_DIRECTORY ("$ENV{NDK}/sources/android/native_app_glue" SOURCES)
INCLUDE_DIRECTORIES ("$ENV{NDK}/sources/android/native_app_glue")

# Local includes (inside project).
INCLUDE_DIRECTORIES (../src)

# Biblioteka z silnikiem bajka.
add_library (shell-android STATIC ${SOURCES})
       
INSTALL (
    TARGETS shell-android
    DESTINATION lib 
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/pc/shell-android.pc.in ${CMAKE_CURRENT_BINARY_DIR}/pc/shell-android.pc @ONLY)
    