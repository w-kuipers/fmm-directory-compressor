#include <pybind11/pybind11.h>
#include <string>
#include "../src/include/generate.h"

namespace py = pybind11;

void py_generate(std::string directory_name) {
    dg::generate(directory_name);
}

PYBIND11_MODULE(generate_directory, m) {
    m.doc() = "Python wrapper for the FMM directory structure generator";
    m.def("generate", &py_generate);
}