# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)
project (browser)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#ADD_DEFINITIONS (-DUSE_SDL)

ADD_DEFINITIONS (-DREFLECTION_ENABLED)
add_definitions (-Wl,-z,defs)

SET (CMAKE_C_FLAGS "-g -fPIC -Wall -O0 -Winvalid-pch -ffunction-sections -fdata-sections")
SET (CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
SET (CMAKE_C_FLAGS_RELEASE "-g0 -fPIC -Wall -O3 -Winvalid-pch -ffunction-sections -fdata-sections -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
 
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

if (ANDROID)
    ADD_DEFINITIONS (-static)
    SET (EXECUTABLE_OUTPUT_PATH "./")
    SET (LIBRARY_OUTPUT_PATH "./android/libs/armeabi-v7a")
endif ()
     
# Boost, można zakomentowa, you can skip this
# Zakomentoeałę, bo na laptopie zaczęło się wywalac.
#find_package (Boost REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})

include (FindPkgConfig)
pkg_check_modules (TILIAE REQUIRED "tiliae")
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

pkg_check_modules (BAJKA REQUIRED "bajka")
INCLUDE_DIRECTORIES (${BAJKA_INCLUDE_DIRS})
link_directories(${BAJKA_LIBRARY_DIRS})

pkg_check_modules (SPARSE_HASH REQUIRED "libsparsehash")
INCLUDE_DIRECTORIES (${SPARSE_HASH_INCLUDE_DIRS})

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
if (ANDROID)
    AUX_SOURCE_DIRECTORY ("$ENV{NDK}/sources/android/native_app_glue" SOURCES)
    INCLUDE_DIRECTORIES ("$ENV{NDK}/sources/android/native_app_glue")
endif()

AUX_SOURCE_DIRECTORY (../src SOURCES)

# Local includes (inside project).
INCLUDE_DIRECTORIES (../src)

if (NOT ANDROID)
    add_executable (${PROJECT_NAME} ${SOURCES})
else ()
    add_library (${PROJECT_NAME} SHARED ${SOURCES})
endif ()

set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")

if (NOT ANDROID)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} boost_program_options)
endif ()

TARGET_LINK_LIBRARIES (${PROJECT_NAME} stdc++)
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${BAJKA_LIBRARIES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${SHELL_LIBRARIES})

if (USE_CHIPMUNK)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} chipmunk)
endif ()

if (ANDROID)
    pkg_check_modules (MXML REQUIRED "mxml")
    link_directories(${MXML_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${MXML_LIBRARIES})

    pkg_check_modules (JANSSON REQUIRED "jansson")
    INCLUDE_DIRECTORIES (${JANSSON_INCLUDE_DIRS})
    link_directories(${JANSSON_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${JANSSON_LIBRARIES})
    
    pkg_check_modules (PNG REQUIRED "libpng")
    INCLUDE_DIRECTORIES (${PNG_INCLUDE_DIRS})
    link_directories(${PNG_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${PNG_LIBRARIES})
        
#    FIND_PACKAGE (JPEG)
#    INCLUDE_DIRECTORIES (${JPEG_INCLUDE_DIR})
#    TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${JPEG_LIBRARIES})
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} jpeg)
    
    pkg_check_modules (FREETYPE REQUIRED "freetype2")
    INCLUDE_DIRECTORIES (${FREETYPE_INCLUDE_DIRS})
    link_directories(${FREETYPE_LIBRARY_DIRS})    
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${FREETYPE_LIBRARIES})

#    set (CMAKE_SHARED_LINKER_FLAGS "-static -Wl,--no-undefined")
        
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} z)
    
    # Android-specific Log Support
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} log)
    
    # The EGL graphics library
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} EGL)
    
    # The Android native application APIs
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} android)
    
    # The OpenGL ES 1.x Library
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} GLESv2)

    # The OpenGL SL
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} OpenSLES)
endif ()


if (NOT ANDROID)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} boost_filesystem)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} boost_system)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${GLEW_LIBRARIES})
endif ()

# http://www.rojtberg.net/465/debugging-native-code-with-ndk-gdb-using-standalone-cmake-toolchain/
# TODO sprawdz, czy debug build
if (ANDROID)
    message ("1. generate Android.mk")
    file (WRITE ./android/jni/Android.mk "APP_ABI := ${ANDROID_NDK_ABI_NAME}\n")
    
    message ("2. generate gdb.setup")
    get_directory_property (INCLUDE_DIRECTORIES DIRECTORY . INCLUDE_DIRECTORIES)
    string (REGEX REPLACE ";" " " INCLUDE_DIRECTORIES "${INCLUDE_DIRECTORIES}")
    file (WRITE ./android/libs/${ANDROID_NDK_ABI_NAME}/gdb.setup "set solib-search-path ./obj/local/${ANDROID_NDK_ABI_NAME}\n")
    file (APPEND ./android/libs/${ANDROID_NDK_ABI_NAME}/gdb.setup "directory ${INCLUDE_DIRECTORIES}\n")
    
    message ("3. copy gdbserver executable")
#    file (COPY "$ENV{NDK}/toolchains/arm-linux-androideabi-4.4.3/prebuilt/gdbserver" DESTINATION "./android/libs/${ANDROID_NDK_ABI_NAME}/")
    file (COPY "$ENV{NDK}/prebuilt/android-arm/gdbserver/gdbserver" DESTINATION "./android/libs/${ANDROID_NDK_ABI_NAME}/")
    
    message ("4. copy lib to obj")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND mkdir -p ./android/obj/local/${ANDROID_NDK_ABI_NAME}/)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND cp ./android/libs/${ANDROID_NDK_ABI_NAME}/lib${PROJECT_NAME}.so ./android/obj/local/${ANDROID_NDK_ABI_NAME}/)
endif ()