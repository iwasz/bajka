# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)
project (browser)

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
 
SET (CMAKE_VERBOSE_MAKEFILE 0)

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
    add_executable (${PROJECT_NAME} ${SOURCES})
else ()
    add_library (${PROJECT_NAME} SHARED ${SOURCES})
endif ()

set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")

if (NOT ANDROID)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} boost_program_options)
endif ()

TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${TILIAE_LIBRARIES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${BAJKA_LIBRARIES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${SHELL_LIBRARIES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} chipmunk)

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
    
    pkg_check_modules (ZLIB REQUIRED "zlib")
    INCLUDE_DIRECTORIES (${ZLIB_INCLUDE_DIRS})
    link_directories(${ZLIB_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${ZLIB_LIBRARIES})
    
    # Android-specific Log Support
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} log)
    
    # The EGL graphics library
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} EGL)
    
    # The Android native application APIs
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} android)
    
    # The OpenGL ES 1.x Library
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} GLESv2)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} stdc++)
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