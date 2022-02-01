#include "include/generate.h"

// Namespace
using namespace std;
directory_generate dg;
generate_file gf;

int main() {

    string directory_name;

    // Some debugging stuff
    #ifdef _WIN32
    string file = "../../tests/test.json";
    string location = "../../tests/";
    #endif

    #ifdef unix
    string file = "../tests/test.json";
    string location = "../tests/";
    #endif
    

    // cout << "Please specify a name for the root directory (default=templatename): ";
    // cin >> directory_name;

    // dg.from_file(directory_name, file, location);

    string directory = "../tests/to_use";

    gf.create(directory);
        
    return 0;
};
