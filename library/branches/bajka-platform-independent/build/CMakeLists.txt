# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET (CMAKE_VERBOSE_MAKEFILE 0) 
ADD_DEFINITIONS (-DLINUX)
ADD_DEFINITIONS (-DUSE_OPENGL)
ADD_DEFINITIONS (-DUSE_CHIPMUNK)
ADD_DEFINITIONS (-O0)
#ADD_DEFINITIONS (-g -fvisibility=hidden)
ADD_DEFINITIONS (-g -fPIC)
ADD_DEFINITIONS (-Winvalid-pch)
#ADD_DEFINITIONS (-H)
ADD_DEFINITIONS (-Wall)
ADD_DEFINITIONS (-DBAJKA_DEBUG)
#ADD_DEFINITIONS (-fsyntax-only)

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
     
SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local") 
SET (CMAKE_PREFIX_PATH "/home/iwasz/local")
INCLUDE_DIRECTORIES ("/home/iwasz/local/include")
link_directories("/home/iwasz/local/lib")

#Boost
find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Tiliae
include (FindPkgConfig)
pkg_check_modules (TILIAE REQUIRED "tiliae")
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

# Find GL
include (FindOpenGL)
INCLUDE_DIRECTORIES (${OPENGL_INCLUDE_DIR})

# Chipmunk
INCLUDE_DIRECTORIES ("/usr/local/include/chipmunk")
INCLUDE_DIRECTORIES ("/home/iwasz/local/include/chipmunk")
    
#    AUX_SOURCE_DIRECTORY ("$ENV{NDK}/sources/android/native_app_glue" SOURCES)
#    INCLUDE_DIRECTORIES ("$ENV{NDK}/sources/android/native_app_glue")
    
    #find_library (TILIAE_LIBRARIES "mxml")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/core")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/beanWrapper")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/common")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/container")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/factory")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/editor")
#    INCLUDE_DIRECTORIES ("$ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/include/tiliae/reflection")
#    
#    INCLUDE_DIRECTORIES ("/home/iwasz/local/share/android-toolchain/user/include/chipmunk")
#    
#    link_directories($ENV{ANDROID_STANDALONE_TOOLCHAIN}/user/lib)    

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
AUX_SOURCE_DIRECTORY (../src/model/layout SOURCES)
AUX_SOURCE_DIRECTORY (../src/model/manager SOURCES)

AUX_SOURCE_DIRECTORY (../src/geometry SOURCES)
AUX_SOURCE_DIRECTORY (../src/util SOURCES)

AUX_SOURCE_DIRECTORY (../src/controller SOURCES)

AUX_SOURCE_DIRECTORY (../src/tween SOURCES)
AUX_SOURCE_DIRECTORY (../src/tween/ease SOURCES)
AUX_SOURCE_DIRECTORY (../src/tween/accessor SOURCES)

AUX_SOURCE_DIRECTORY (../src/openGl SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (../src)
#INCLUDE_DIRECTORIES (../src/view)
#INCLUDE_DIRECTORIES (../src/model)
#INCLUDE_DIRECTORIES (../src/geometry)
#INCLUDE_DIRECTORIES (../src/util)
#INCLUDE_DIRECTORIES (../src/events)
#INCLUDE_DIRECTORIES (../src/controller)
#INCLUDE_DIRECTORIES (../src/openGl)
#INCLUDE_DIRECTORIES (../src/tween)

# Biblioteka z silnikiem bajka.
add_library (bajka SHARED ${SOURCES})
TARGET_LINK_LIBRARIES (bajka ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES (bajka ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (bajka chipmunk)
    
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
    
INSTALL (
    TARGETS bajka
    DESTINATION lib 
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)
