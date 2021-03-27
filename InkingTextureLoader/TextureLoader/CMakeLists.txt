# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add.library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

include_directories("${PROJECT_SOURCE_DIR}/ThirdParty/stb_image/source")
include_directories("${PROJECT_SOURCE_DIR}/ThirdParty/UnityPluginAPI")

if(MSVC)
include_directories("$ENV{DXSDK_DIR}Include")
link_directories("$ENV{DXSDK_DIR}Lib/x64")
else()

endif()

if(MSVC)
    add_definitions(-D _D3D11_)
else()
    add_definitions(-D _OPENGLES_)
endif()

file(GLOB_RECURSE source_files "Source/*.h" "Source/*.cpp")
source_group_by_dir(source_files)

add_library(TextureLoader SHARED ${source_files} )
# add_library(TextureLoader ${source_files} )

set_target_properties(TextureLoader PROPERTIES 
OUTPUT_NAME "InkingTextureLoader"
)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

if(MSVC)
target_link_libraries(TextureLoader
d3d11.lib
d3dcompiler.lib
d3dx11d.lib
d3dx9d.lib
dxerr.lib
dxguid.lib
winmm.lib
)
else()
target_link_libraries(TextureLoader
-lEGL
-lGLESv2
)
endif()
