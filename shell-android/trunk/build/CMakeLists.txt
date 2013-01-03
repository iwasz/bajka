# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

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

if (ANDROID)
    ADD_DEFINITIONS (-DANDROID)
else()
    ADD_DEFINITIONS (-DLINUX)
endif()
    
SET (CMAKE_C_FLAGS "-g -fPIC -Wall -O0 -Winvalid-pch -ffunction-sections -fdata-sections")
SET (CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
SET (CMAKE_C_FLAGS_RELEASE "-g0 -fPIC -Wall -O3 -Winvalid-pch -ffunction-sections -fdata-sections -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

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
    