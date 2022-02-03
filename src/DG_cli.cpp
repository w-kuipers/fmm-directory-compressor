#include "include/generate.h"

// Namespace
using namespace std;
directory_generate dg;
generate_file gf;

int main() {

    string directory_name;

    // Some debugging stuff
    #ifdef _WIN32
    string file = "../../tests/generated_test.json";
    string location = "../../tests/";
    string directory = "../../tests/to_use";
    #endif

    #ifdef unix
    string file = "../tests/generated_test.json";
    string location = "../tests/";
    string directory = "../tests/to_use";
    #endif
    

    cout << "Please specify a name for the root directory (default=templatename): ";
    cin >> directory_name;

    dg.from_file(directory_name, file, location);

    // gf.create(directory);
        
    return 0;
};
