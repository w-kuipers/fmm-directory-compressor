#include "include/generate.cpp"

// Namespace
using namespace std;
using namespace dg;

int main() {

    string directory_name;

    cout << "Please specify a name for the root directory (default=templatename): ";
    cin >> directory_name;

    dg::structure_generate(directory_name);
        
    return 0;
}
