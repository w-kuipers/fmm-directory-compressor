cmake_minimum_required(VERSION 3.0.0)
project(FMM_dirstructure_generator VERSION 0.1.0)

include(CTest)
enable_testing()

## Windows compiling
if (WIN32)
    add_executable(FMMdirstructuregenerator src/DG_cli.cpp src/include/generate.cpp src/include/win32/make_dir.cpp)
endif (WIN32)

# find_package(jsoncpp CONFIG REQUIRED)
# target_link_libraries(main PRIVATE jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
