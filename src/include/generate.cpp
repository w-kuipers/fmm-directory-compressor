#include "generate.h"

using namespace std;

#ifdef _WIN32
#include "win32/make_dir.h"
string sub_directory = "../../tests/";
#endif

#ifdef __PYMODULE
sub_directory = "../tests/";
#endif

#ifdef unix
#include "linux/make_dir.h"
string sub_directory = "../tests/";
#endif



void direcory_generate::generate(string root_directory_name, json json_data) {

    string root_path = sub_directory + root_directory_name;

    // Create root directory
    if (!os_sp::make_dir(root_path)) {
        return; // Break function if root fails to generate
    };

    // Loop through subdirectories
    for (size_t d = 0; d < json_data["structure"].size(); d++) {

        direcory_generate::check_subs(json_data["structure"][d]["sub"]);

        // Get directory name
        string directory_name = json_data["structure"][d]["title"];

        // Format path
        string full_path = root_path + "/" + directory_name;

        // Create directory
        if (!os_sp::make_dir(full_path)) {
            cerr << "Error: " << strerror(errno) << endl;
            return;
        };
    };
};

void direcory_generate::from_file(string root_directory_name, string file_string) {

    // Read file
    ifstream file(file_string);

    // Parse JSON from file
    json json_data;
    file >> json_data;

    // Call function to generate 
    direcory_generate::generate(root_directory_name, json_data);
};



void direcory_generate::check_subs(json level) {

    for (size_t s = 0; s < level.size(); s++) {
        cout << level[s]["title"] << endl;
    };

    
};