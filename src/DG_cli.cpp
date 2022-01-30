#include "include/generate.h"

// Namespace
using namespace std;

int main() {

    string directory_name;

    cout << "Please specify a name for the root directory (default=templatename): ";
    cin >> directory_name;

    dg::generate(directory_name);
        
    return 0;
}
