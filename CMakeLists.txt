# **** BEGIN GPL LICENSE BLOCK ****

#   FMM Directory Compressor

#   Copyright (C) 2022  Wibo Kuipers
 
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with this program.  
#   If not, see https://github.com/w-kuipers/fmm-directory-compressor/blob/master/LICENSE.
 
# **** END GPL LICENSE BLOCK ****

cmake_minimum_required(VERSION 3.5.1)

set(version_number "0.1.0")

project(FMM_Directory_Compressor VERSION ${version_number})

include(CTest)
enable_testing()

## Windows compiling
# if (WIN32)

include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(jsoncpp COMPONENTS REQUIRED)
find_package(libzip CONFIG REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# if (CLI OR ALL)
add_executable(fmm-directory-compressor src/DC_cli.cpp src/include/generate.cpp src/include/win32/make_dir.cpp src/include/compress.cpp src/include/common.cpp)
target_link_libraries(fmm-directory-compressor ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp libzip::zip)
# endif (CLI OR ALL)

# if (PY OR ALL)
pybind11_add_module(fmmpy_directory_compressor src/DC_py.cpp src/include/generate.cpp src/include/win32/make_dir.cpp src/include/compress.cpp src/include/common.cpp)
target_link_libraries(fmmpy_directory_compressor PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp libzip::zip)
# endif (PY OR ALL)

# if (JS OR ALL)
include(C:/dev/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
# target_include_directories(AILEMProcessor PUBLIC "C:/Users/vjohnson/Documents/AILBrowserDev/emscripten_project/emsdk/fastcomp/emscripten/system/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/js")

add_executable(fmmjs-directory-compressor src/DC_js.cpp src/include/generate.cpp src/include/win32/make_dir.cpp src/include/compress.cpp src/include/common.cpp)

message(STATUS "Setting compilation target to WASM")
set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
set_target_properties(fmmjs-directory-compressor PROPERTIES LINK_FLAGS "-s WASM=1 -s EXPORTED_FUNCTIONS='[_main]'")

target_link_libraries(fmmjs-directory-compressor PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp libzip::zip)
# endif (JS OR ALL)
    

# endif (WIN32)

## Linux and Unix compiling
# if (UNIX)

#     include(lib/vcpkg/scripts/buildsystems/vcpkg.cmake)
    
#     find_package(Boost COMPONENTS system filesystem REQUIRED)
#     find_package(jsoncpp CONFIG REQUIRED)
#     find_package(libzip REQUIRED)
#     find_package(pybind11 CONFIG REQUIRED)

#     if (cli OR all)
#         add_executable(main/fmm-directory-compressor src/DC_cli.cpp src/include/generate.cpp src/include/linux/make_dir.cpp src/include/compress.cpp src/include/common.cpp)
#         target_link_libraries(fmm-directory-compressor ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_object jsoncpp_static JsonCpp::JsonCpp libzip::zip)
#     endif (main OR all)

#     if (py OR all)
#         pybind11_add_module(python/fmmpy_directory_compressor src/DC_py.cpp src/include/generate.cpp src/include/linux/make_dir.cpp src/include/compress.cpp src/include/common.cpp)
#         target_link_libraries(fmmpy_directory_compressor PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_object jsoncpp_static JsonCpp::JsonCpp libzip::zip)
#     endif (py OR all)  
    
# endif (UNIX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
