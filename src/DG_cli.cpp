#include "include/generate.h"

// Namespace
using namespace std;
directory_generate dg;

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
    

    cout << "Please specify a name for the root directory (default=templatename): ";
    cin >> directory_name;

    dg.from_file(directory_name, file, location);
        
    return 0;
};
