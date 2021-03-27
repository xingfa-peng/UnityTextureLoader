# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add.library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.



macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
			
			string(REGEX REPLACE ${sgbd_cur_dir}/.∗.∗ \\1 sgbd_fpath ${sgbd_file})
			string(REGEX REPLACE ".∗.∗/.*" \\1 sgbd_group_name ${sgbd_fpath})
			string(REPLACE "${sgbd_cur_dir}/" "" sgbd_group_name ${sgbd_group_name})
			get_filename_component(  FULL_NAME "${sgbd_group_name}" PATH)
			
			if(FULL_NAME)
				string(REPLACE "/" "\\" FULL_NAME ${FULL_NAME})
				source_group(${FULL_NAME} FILES ${sgbd_file})
			endif(FULL_NAME)
			
			#message(STATUS "group = [${FULL_NAME}] file = [${sgbd_file}]")
			
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

project(Inking)

add_subdirectory(TextureLoader)