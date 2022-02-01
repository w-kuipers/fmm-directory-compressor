#include "include/DG_py.h"

namespace py = pybind11;
dg dir_gen;

void py_generate(std::string directory_name, std::string file_string) {
    dir_gen.from_file(directory_name, file_string);
};

PYBIND11_MODULE(generate_directory, m) {
    m.doc() = "Python wrapper for the FMM directory structure generator";
    m.def("generate", &py_generate);
};