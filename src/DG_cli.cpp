#include "include/generate.h"

// Namespace
using namespace std;
dg dir_gen;

int main() {

    string directory_name;

    // Some debugging stuff
    #ifdef _WIN32
    string file = "../../tests/test.json";
    #endif

    #ifdef unix
    string file = "../tests/test.json";
    #endif
    

    cout << "Please specify a name for the root directory (default=templatename): ";
    cin >> directory_name;

    dir_gen.from_file(directory_name, file);
        
    return 0;
};
