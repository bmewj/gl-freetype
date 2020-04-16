cmake_minimum_required(VERSION 3.14)
project(FreeType2)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FREETYPE REQUIRED IMPORTED_TARGET freetype2)

add_library(FreeType2 INTERFACE IMPORTED GLOBAL)
target_include_directories(FreeType2 INTERFACE
    ${FREETYPE_INCLUDE_DIRS}
)
target_link_options(FreeType2 INTERFACE
    ${FREETYPE_LDFLAGS}
)
