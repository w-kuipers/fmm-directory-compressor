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

#include "make_dir.h"

bool os_sp::make_dir(std::string path) {

    if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        return true;
    }
    else {
        return false;
    }
}