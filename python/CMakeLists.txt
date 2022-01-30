cmake_minimum_required(VERSION "3.16.3")

project("FMM_DG_py")

add_subdirectory(pybind11)
pybind11_add_module(generate_directory DG_py.cpp)


