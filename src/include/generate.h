#ifndef GENERATE_H
#define GENERATE_H

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

namespace dg {
    void generate(std::string directory_name, Json::Value data);
    void from_file(std::string root_directory_name, std::string file);
} // namespace dg

#endif
