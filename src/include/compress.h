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
#include <jsoncpp/json/json.h>
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