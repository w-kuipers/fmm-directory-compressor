#ifndef __PYMODULE
#define __PYMODULE

#include <pybind11/pybind11.h>
#include <string>
#include "generate.h"

namespace py = pybind11;
directory_generate dg;
generate_zip gz;

bool SKIPLONGPATHS;

#endif
