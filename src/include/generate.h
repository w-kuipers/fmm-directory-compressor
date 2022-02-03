#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <boost/filesystem.hpp>

#ifdef _WIN32
#include "win32/make_dir.h"
#include <json/json.h>
#endif

#ifdef unix
#include "linux/make_dir.h"
#include <jsoncpp/json/json.h>
#endif

using namespace std;
namespace bfs = boost::filesystem;

class directory_generate {
    public:
        void from_file(std::string root_directory_name, std::string file, std::string location);
        void create_generation_tree(std::string directory_name, Json::Value json_data, std::string location);
    private:
        Json::Value generation_tree;
        Json::Value file_generation_tree;
        void traverse(Json::Value json_data, std::string path);
};

class generate_file {
    public:
        void create(const bfs::path &dir_path);
    private:
        Json::Value traverse(const bfs::path &dir_path);
};

class generate_zip {
    public:
        void from_path(std::string path);
};

#endif