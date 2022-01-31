#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "json.hpp"
using namespace nlohmann;

namespace dg {
    void generate(std::string directory_name, json json_data);
    void from_file(std::string root_directory_name, std::string file);
    void check_subs(json level);
} // namespace dg

#endif
