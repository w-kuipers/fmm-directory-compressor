#include "generate.h"
#include "win32/make_dir.h"

using namespace std;

#ifdef _WIN32
string sub_directory = "../../tests/";
#endif

#ifdef __PYMODULE
sub_directory = "../tests/";
#endif

#ifdef unix
string sub_directory = "../tests/";
#endif

void dg::generate(string root_directory_name, Json::Value json_data) {

    string root_path = sub_directory + root_directory_name;

    // Create root directory
    if (!os_sp::make_dir(root_path)) {
        return; // Break function if root fails to generate
    }

    // Loop through subdirectories
    // for (size_t d = 0; d < json_data["structure"].size(); d++) {

    //     // Get directory name
    //     string directory_name = json_data["structure"][d]["title"].asString();

    //     // Format path
    //     string full_path = root_path + "/" + directory_name;

    //     // Create directory
    //     if (!os_sp::make_dir(full_path)) {
    //         cerr << "Error: " << strerror(errno) << endl;
    //         return;
    //     }
    // }
}

void dg::from_file(string root_directory_name, string file_string) {

    // Read file
    ifstream file(file_string);

    // Parse JSON from file
    Json::Value json_data;
    Json::Reader json_reader;
    json_reader.parse(file, json_data);

    // Call function to generate 
    dg::generate(root_directory_name, json_data);
}
