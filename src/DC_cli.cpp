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

#include "include/DC_cli.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        cerr << "\nError: No arguments where given\n";
        return 1;
    }

    // Handle args
    for (int a = 2; a < argc; a++) {

        // Deal with long paths (windows..)
        if (string(argv[a]) == "--skip-long-paths") {
            SKIPLONGPATHS = true;
            cout << "Skipping any path that is larger than 260 characters\n";
        }
    }

    // Run the right program
    if (string(argv[1]) == "compress-directory") {
        if (argc < 4) {
            cerr << "\nError: compress-directory takes 2 arguments (src, dst)\n";
            return 1;
        }

        std::string structure_name;

        while (structure_name.empty()) {
            cout << "Please specify a name for the this structure template: ";
            cin >> structure_name;
        }

        gz.from_path(argv[2], structure_name, argv[3]);
    }
    else if (string(argv[1]) == "decompress-directory") {
        if (argc < 4) {
            cerr << "\nError: compress-directory takes 2 arguments (.FPS file, dst)\n";
            return 1;
        }

        std::string directory_name;

        cout << "Please specify a name for the root directory (default=templatename): ";
        cin >> directory_name;

        dg.from_file(directory_name, argv[2], argv[3]);
    }
    else {
        cerr << "\nError: program " + string(argv[1]) + " does not exist\n";
        return 1;
    }
        
    return 0;
};
