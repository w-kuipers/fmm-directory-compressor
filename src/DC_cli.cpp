#include "include/DC_cli.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        cerr << "\nError: No arguments where given\n";
        return 1;
    }

    // Handle args
    for (int a = 2; a < argc; a++) {

        cout << argv[a] << endl;

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

    // dg.from_file(directory_name, argv[2], argv[2]);
   

    // gf.create(directory);

    // while (structure_name.empty()) {
    //     cout << "Please specify a name for the this structure template: ";
    //     cin >> structure_name;
    // }

    // gz.from_path(directory, structure_name, "../tests/fpstest/");
        
    return 0;
};
