# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET (CMAKE_VERBOSE_MAKEFILE 0) 

#ADD_DEFINITIONS (-O3)
ADD_DEFINITIONS (-g)
ADD_DEFINITIONS (-Winvalid-pch)
#ADD_DEFINITIONS (-H)
ADD_DEFINITIONS (-Wall)
ADD_DEFINITIONS (-DBAJKA_DEBUG)
#ADD_DEFINITIONS (-fsyntax-only)

SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
SET (CMAKE_VERBOSE_MAKEFILE 0)

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

# Sources
AUX_SOURCE_DIRECTORY (../view SOURCES)
AUX_SOURCE_DIRECTORY (../view/draw SOURCES)
AUX_SOURCE_DIRECTORY (../view/resource SOURCES)

AUX_SOURCE_DIRECTORY (../events SOURCES)
AUX_SOURCE_DIRECTORY (../events/filter SOURCES)
AUX_SOURCE_DIRECTORY (../events/sdl SOURCES)
AUX_SOURCE_DIRECTORY (../events/types SOURCES)

AUX_SOURCE_DIRECTORY (../model SOURCES)
AUX_SOURCE_DIRECTORY (../model/static SOURCES)
AUX_SOURCE_DIRECTORY (../model/physics SOURCES)

AUX_SOURCE_DIRECTORY (../geometry SOURCES)
AUX_SOURCE_DIRECTORY (../util SOURCES)

AUX_SOURCE_DIRECTORY (../dependencies/openGl SOURCES)
AUX_SOURCE_DIRECTORY (../dependencies/sdl SOURCES)

AUX_SOURCE_DIRECTORY (../controller SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (/usr/local/include/chipmunk)
INCLUDE_DIRECTORIES (../view)
INCLUDE_DIRECTORIES (../model)
INCLUDE_DIRECTORIES (../geometry)
#INCLUDE_DIRECTORIES (../fluids)
INCLUDE_DIRECTORIES (../util)
INCLUDE_DIRECTORIES (../events)
INCLUDE_DIRECTORIES (../controller)
INCLUDE_DIRECTORIES (../dependencies/sdl)
INCLUDE_DIRECTORIES (../dependencies/openGl)
INCLUDE_DIRECTORIES (../base)

# Biblioteka z silnikiem bajka.
add_library (bajka SHARED ${SOURCES})
TARGET_LINK_LIBRARIES (bajka ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES (bajka ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES (bajka ${SDLIMAGE_LIBRARY})
TARGET_LINK_LIBRARIES (bajka ${SDLTTF_LIBRARY})
TARGET_LINK_LIBRARIES (bajka ${JPEG_LIBRARIES})
TARGET_LINK_LIBRARIES (bajka ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (bajka chipmunk)

# Executable test.
IF (1)
    AUX_SOURCE_DIRECTORY (../test TEST_SOURCES)
    #AUX_SOURCE_DIRECTORY (../test/helpers TEST_SOURCES)
    
    #if (true)
    add_executable (test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (test bajka)
    TARGET_LINK_LIBRARIES (test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (test boost_prg_exec_monitor)
ENDIF ()

IF (1)
    # Executable demo.
    AUX_SOURCE_DIRECTORY (../demo DEMO_SOURCES)
    #LIST(APPEND DEMO_SOURCES ${SOURCES})
    
    add_executable (demo ${DEMO_SOURCES})
    TARGET_LINK_LIBRARIES (demo bajka)
ENDIF ()

IF (0)
    # Executable demo.
    AUX_SOURCE_DIRECTORY (../platformer/src PLATFORMER_SOURCES)
   
    add_executable (platformer ${PLATFORMER_SOURCES})
    TARGET_LINK_LIBRARIES (platformer bajka)  
    TARGET_LINK_LIBRARIES (platformer ${OPENGL_LIBRARIES})
    TARGET_LINK_LIBRARIES (platformer ${JPEG_LIBRARIES})
    TARGET_LINK_LIBRARIES (platformer ${SDL_LIBRARY})
    TARGET_LINK_LIBRARIES (platformer ${SDLIMAGE_LIBRARY})
    TARGET_LINK_LIBRARIES (platformer ${TILIAE_LIBRARIES})
ENDIF ()
