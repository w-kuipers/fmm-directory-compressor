#include "include/DC_cli.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        cerr << "No arguments where given";
        return 1;
    }

    // Handle args
    for (int a = 1; a < argc; a++) {

        // Deal with long paths (windows..)
        if (string(argv[a]) == "--skip-long-paths") {
            SKIPLONGPATHS = true;
            cout << "Skipping any path that is larger than 260 characters" << endl;
        }
    }

    string directory_name;
    string structure_name;

    // Some debugging stuff
    #ifdef _WIN32
    string file = "../../tests/pythonTests/Pythontest.fps";
    string location = "../../tests/generated_tests/";
    string directory = "Z:/01_PROJECTS/192755_Toneelgroep-Oostpool/2112130_Toneelgroep-Oostpool_Edward-II-Interviews";
    #endif

    #ifdef unix
    string file = "../tests/fpstest/test.fps";
    string location = "../tests/generated_tests";
    string directory = "/home/wibo/Documents/PROTO";
    #endif
    

    cout << "Please specify a name for the root directory (default=templatename): ";
    cin >> directory_name;

    dg.from_file(directory_name, file, location);

    // gf.create(directory);

    // while (structure_name.empty()) {
    //     cout << "Please specify a name for the this structure template: ";
    //     cin >> structure_name;
    // }

    // gz.from_path(directory, structure_name, "../tests/fpstest/");
        
    return 0;
};
