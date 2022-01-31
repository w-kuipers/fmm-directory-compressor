cmake_minimum_required(VERSION 3.0.0)

project("FMM_DG_py")

include(CTest)
enable_testing()

add_subdirectory(pybind11)
add_subdirectory(lib/jsoncpp)

pybind11_add_module(generate_directory DG_py.cpp ../src/include/generate.cpp ../src/include/WIN32/make_dir.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


