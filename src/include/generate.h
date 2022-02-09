/*

 *  FMM Directory Compressor

 *  Copyright (C) 2022  Wibo Kuipers
 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  
 *  If not, see https://github.com/w-kuipers/fmm-directory-compressor/blob/master/LICENSE.
 
 */

#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <boost/filesystem.hpp>
#include "compress.h"
#include "common.h"

#ifdef _WIN32
#include "win32/make_dir.h"
#include <json/json.h>
#endif

#ifdef unix
#include "linux/make_dir.h"
#include <json/json.h>
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
        Json::Value create(const bfs::path &dir_path, const string dst_path);
    private:
        Json::Value file_array;
        Json::Value traverse(const bfs::path &dir_path);
};

class generate_zip {
    public:
        void from_path(std::string path, std::string name, std::string location);
};

#endif