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
ADD_DEFINITIONS (-DREFLECTION_ENABLED)
#ADD_DEFINITIONS (-fsyntax-only)
     
SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local") 
SET (CMAKE_PREFIX_PATH "/home/iwasz/local")
INCLUDE_DIRECTORIES ("/home/iwasz/local/include")
link_directories("/home/iwasz/local/lib")

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

pkg_check_modules (SHELL REQUIRED "shell-linux")
INCLUDE_DIRECTORIES (${SHELL_INCLUDE_DIRS})
link_directories(${SHELL_LIBRARY_DIRS})

# Testowo
#pkg_check_modules (GLES2 REQUIRED "glesv2")
#INCLUDE_DIRECTORIES (${GLES2_INCLUDE_DIRS})
#link_directories(${GLES2_LIBRARY_DIRS})

# Sources
AUX_SOURCE_DIRECTORY (../src SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (../src)

add_executable (browser ${SOURCES})
TARGET_LINK_LIBRARIES (browser boost_program_options)
TARGET_LINK_LIBRARIES (browser ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (browser ${BAJKA_LIBRARIES})
TARGET_LINK_LIBRARIES (browser ${SHELL_LIBRARIES})
TARGET_LINK_LIBRARIES (browser chipmunk)
TARGET_LINK_LIBRARIES (browser boost_filesystem)
TARGET_LINK_LIBRARIES (browser boost_system)
TARGET_LINK_LIBRARIES (browser ${GLES2_LIBRARIES})

