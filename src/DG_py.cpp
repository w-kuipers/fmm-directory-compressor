#include "include/DG_py.h"

namespace py = pybind11;
directory_generate dg;
generate_zip gz;

// Generate FPS file from directory path
void generate_file_from_path(string path, string name, string location) {
    gz.from_path(path, name, location);
}

// Generate the directory structure from FPS file
void generate_structure_from_file(std::string directory_name, std::string file_string, std::string location) {
    dg.from_file(directory_name, file_string, location);
}

// Python module
PYBIND11_MODULE(generate_directory, m) {
    m.doc() = "Python wrapper for the FMM project structure generator";
    m.def("generate_structure_from_file", &generate_structure_from_file);
    m.def("generate_file_from_path", &generate_file_from_path);
}