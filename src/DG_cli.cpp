#include "include/generate.h"

// Namespace
using namespace std;

int main() {

    string directory_name;
    string file = "../tests/test.json";

    cout << "Please specify a name for the root directory (default=templatename): ";
    cin >> directory_name;

    dg::from_file(directory_name, file);
        
    return 0;
}
