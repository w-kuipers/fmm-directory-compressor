/*

 *  FMM Directory Compressor - Compressing directory structures to a .FPS file.

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

#ifndef COMPRESS_H
#define COMPRESS_H

#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <zip.h>
#include <boost/filesystem.hpp>
#include "common.h"

#include <fcntl.h>

#ifdef _WIN32
#include <json/json.h>
#include <io.h>
#endif

#ifdef unix
#include <json/json.h>
#include <unistd.h>
#endif
namespace bfs = boost::filesystem;

class compress_directory {
    public:
        void compress(const std::string& input_dir, const std::string& output_filename);
        Json::Value gather_files(const std::string& input_dir, const std::string& output_dir);
    private:
        void walk_directory(const std::string& start_dir, const std::string& input_dir, zip_t *zipper);
        std::vector<std::string> generate_file_array(const std::string& input_dir);
};

class decompress_archive {
    public:
        std::string decompress(const char *file_string, const char *to_fetch);
        void decompress_bin(const char *file_string, const char *to_fetch, std::string location);
};  


#endif