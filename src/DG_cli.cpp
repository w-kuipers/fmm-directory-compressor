#include "include/generate.h"

// Namespace
using namespace std;
directory_generate dg;
generate_file gf;
generate_zip gz;

int main() {

    string directory_name;
    string structure_name;

    // Some debugging stuff
    #ifdef _WIN32
    string file = "../../tests/generated_test.json";
    string location = "../../tests/";
    string directory = "Z:/01_PROJECTS/192755_Toneelgroep-Oostpool/2112130_Toneelgroep-Oostpool_Edward-II-Interviews";
    #endif

    #ifdef unix
    string file = "../tests/generated_test.json";
    string location = "../tests/";
    string directory = "../tests/to_use";
    #endif
    

    // cout << "Please specify a name for the root directory (default=templatename): ";
    // cin >> directory_name;

    // dg.from_file(directory_name, file, location);

    // gf.create(directory);

    while (structure_name.empty()) {
        cout << "Please specify a name for the this structure template: ";
        cin >> structure_name;
    }

    gz.from_path(directory, structure_name, "../../tests/fpstest/");
        
    return 0;
};
