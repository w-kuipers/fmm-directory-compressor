cmake_minimum_required(VERSION 3.0.0)
project(FMM_dirstructure_generator VERSION 0.1.0)

include(CTest)
enable_testing()

# add_subdirectory(lib/jsoncpp)
add_subdirectory(lib/pybind11)

## Windows compiling
if (WIN32)
    add_executable(FMMdirstructuregenerator src/DG_cli.cpp src/include/generate.cpp src/include/win32/make_dir.cpp)
    pybind11_add_module(generate_directory src/DG_py.cpp src/include/generate.cpp src/include/win32/make_dir.cpp)
endif (WIN32)

## Linux and Unix compiling
if (UNIX)
    
    add_executable(FMMdirstructuregenerator src/DG_cli.cpp src/include/generate.cpp src/include/linux/make_dir.cpp)
    
    pybind11_add_module(generate_directory src/DG_py.cpp src/include/generate.cpp src/include/linux/make_dir.cpp)
endif (UNIX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
