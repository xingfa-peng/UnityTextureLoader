cmake_minimum_required (VERSION 3.2.3)
# Set project name
project (STB_image)

FILE (GLOB ALL_FILES "source/*.c" "source/*.h" "source/*.cpp")

add_library("stb_image" ${ALL_FILES})