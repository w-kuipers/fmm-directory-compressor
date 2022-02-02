cmake_minimum_required(VERSION 3.0.0)
project(FMM_dirstructure_generator VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(lib/pybind11)

## Windows compiling
if (WIN32)

    include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)

    
    add_executable(FMMdirstructuregenerator src/DG_cli.cpp src/include/generate.cpp src/include/win32/make_dir.cpp)
    pybind11_add_module(generate_directory src/DG_py.cpp src/include/generate.cpp src/include/win32/make_dir.cpp)

endif (WIN32)

## Linux and Unix compiling
if (UNIX)
    
    find_package(Boost COMPONENTS system filesystem REQUIRED)
    find_package(jsoncpp COMPONENTS system filesystem REQUIRED)

    add_executable(FMMdirstructuregenerator src/DG_cli.cpp src/include/generate.cpp src/include/linux/make_dir.cpp)
    pybind11_add_module(generate_directory src/DG_py.cpp src/include/generate.cpp src/include/linux/make_dir.cpp)

    target_link_libraries(FMMdirstructuregenerator ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_lib)
    
endif (UNIX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
