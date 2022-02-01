#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "json.hpp"


#ifdef _WIN32
#include "win32/make_dir.h"
#endif

#ifdef unix
#include "linux/make_dir.h"
#endif

using namespace nlohmann;

class directory_generate {
    public:
        void from_file(std::string root_directory_name, std::string file, std::string location);
        void create_generation_tree(std::string directory_name, json json_data, std::string location);
    private:
        json generation_tree;
        bool check_subs(json level);
        void directory_generate::traverse(json json_data, std::string path);
};

#endif