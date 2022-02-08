cmake_minimum_required(VERSION 3.0.0)

set(version_number "0.1.0")

project(FMM_Directory_Compressor VERSION ${version_number})

include(CTest)
enable_testing()

## Windows compiling
if (WIN32)

    include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)

    find_package(Boost COMPONENTS system filesystem REQUIRED)
    find_package(jsoncpp COMPONENTS REQUIRED)
    find_package(libzip CONFIG REQUIRED)
    find_package(pybind11 CONFIG REQUIRED)

    add_executable(fmm_directory_compressor_${version_number} src/DC_cli.cpp src/include/generate.cpp src/include/win32/make_dir.cpp src/include/compress.cpp src/include/common.cpp)
    pybind11_add_module(fmmpy_directory_compressor_${version_number} src/DC_py.cpp src/include/generate.cpp src/include/win32/make_dir.cpp src/include/compress.cpp src/include/common.cpp)

    target_link_libraries(fmmpy_directory_compressor_${version_number} PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp libzip::zip)
    target_link_libraries(fmm_directory_compressor_${version_number} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp libzip::zip)

endif (WIN32)

## Linux and Unix compiling
if (UNIX)

    include(lib/vcpkg/scripts/buildsystems/vcpkg.cmake)
    
    find_package(Boost COMPONENTS system filesystem REQUIRED)
    find_package(jsoncpp CONFIG REQUIRED)
    find_package(libzip REQUIRED)
    find_package(pybind11 CONFIG REQUIRED)

    add_executable(fmm_directory_compressor_${version_number} src/DC_cli.cpp src/include/generate.cpp src/include/linux/make_dir.cpp src/include/compress.cpp src/include/common.cpp)
    pybind11_add_module(fmmpy_directory_compressor_${version_number} src/DC_py.cpp src/include/generate.cpp src/include/linux/make_dir.cpp src/include/compress.cpp src/include/common.cpp)

    target_link_libraries(fmmpy_directory_compressor_${version_number} PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_object jsoncpp_static JsonCpp::JsonCpp libzip::zip)
    target_link_libraries(fmm_directory_compressor_${version_number} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} jsoncpp_object jsoncpp_static JsonCpp::JsonCpp libzip::zip)
    
endif (UNIX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
