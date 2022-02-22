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

#include "include/DC_js.h"

// Generate FSA file from directory path
void compress_directory(std::string path, std::string name, std::string location, bool _SKIPLONGPATHS = false) { // TODO when skiplongpaths is not passed in python the functions failes

    if (_SKIPLONGPATHS) {
        SKIPLONGPATHS = true;
    }

    gz.from_path(path, name, location);

    return;
}

// Generate the directory structure from FSA file
void decompress_directory(std::string directory_name, std::string file_string, std::string location) {
    dg.from_file(directory_name, file_string, location);

    return;
}

// JavaScript module
EMSCRIPTEN_BINDINGS(fmmjs_directory_compressor) {
    function("compress_directory", &compress_directory);
    function("decompress_directory", &decompress_directory);
}