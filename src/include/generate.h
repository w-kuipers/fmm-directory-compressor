#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include <json/json.h>
#include <json/value.h>

namespace dg {
    void generate(std::string directory_name, Json::Value json_data);
    void from_file(std::string root_directory_name, std::string file);
} // namespace dg

#endif
