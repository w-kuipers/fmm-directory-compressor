#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "json.hpp"
using namespace nlohmann;

class directory_generate {
    public:
        void from_file(std::string root_directory_name, std::string file);
        void create_generation_tree(std::string directory_name, json json_data);
    private:
        json generation_tree;
        bool check_subs(json level);
        void directory_generate::traverse(json json_data, std::string path);
};

#endif