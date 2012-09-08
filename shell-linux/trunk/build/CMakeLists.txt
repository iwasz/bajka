# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

ADD_DEFINITIONS (-DLINUX)
ADD_DEFINITIONS (-DUSE_SDL)
ADD_DEFINITIONS (-DUSE_OPENGL)
ADD_DEFINITIONS (-DUSE_CHIPMUNK)
SET (LINUX True)

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
    DESTINATION "include/shell-linux" 
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

# Find GL
include (FindOpenGL)
INCLUDE_DIRECTORIES (${OPENGL_INCLUDE_DIR})

# sdl
include (FindSDL)
INCLUDE_DIRECTORIES (${SDL_INCLUDE_DIR})

# sdl_image
include (FindSDL_image)
INCLUDE_DIRECTORIES (${SDL_SDLIMAGE_INCLUDE_DIR})

# SDL TTF
pkg_check_modules (SDLTTF REQUIRED "SDL_ttf")    
INCLUDE_DIRECTORIES (${SDLTTF_INCLUDE_DIR})
link_directories(${SDLTTF_LIBRARY_DIRS})

# Sources
AUX_SOURCE_DIRECTORY (../src SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (../src)

# Biblioteka z silnikiem bajka.
add_library (shell-linux SHARED ${SOURCES})
TARGET_LINK_LIBRARIES (shell-linux ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES (shell-linux ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES (shell-linux ${SDLIMAGE_LIBRARY})
TARGET_LINK_LIBRARIES (shell-linux ${SDLTTF_LIBRARIES})
TARGET_LINK_LIBRARIES (shell-linux ${JPEG_LIBRARIES})
TARGET_LINK_LIBRARIES (shell-linux ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (shell-linux ${BAJKA_LIBRARIES}) 
    
# Executable test.
IF (0)
    AUX_SOURCE_DIRECTORY (../test TEST_SOURCES)
    #AUX_SOURCE_DIRECTORY (../test/helpers TEST_SOURCES)
    
    #if (true)
    add_executable (test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (test shell-linux)
    TARGET_LINK_LIBRARIES (test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (test boost_prg_exec_monitor)
ENDIF ()

INSTALL (
    TARGETS shell-linux
    DESTINATION lib 
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)
    