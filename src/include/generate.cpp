#include "generate.h"

using namespace std;

void directory_generate::from_file(string root_directory_name, string file_string, string location) {

    // Read file
    ifstream file(file_string);

    // Parse JSON from file
    json json_data;
    file >> json_data;

    // Call function to generate 
    directory_generate::create_generation_tree(root_directory_name, json_data, location);

    // Generate directory tree
    for (size_t p = 0; p < directory_generate::generation_tree.size(); p++) {
        if (!os_sp::make_dir(directory_generate::generation_tree[p])) {
            return; // Break function if root fails to generate
        };
    }
    
}

void directory_generate::create_generation_tree(string root_directory_name, json json_data, string location) {

    // Append root directory to generation tree
    string root_path = location + root_directory_name;
    directory_generate::generation_tree[0] = root_path;

    // Call recursive function to walk through JSON tree
    directory_generate::traverse(json_data["structure"], root_path);

    return;
}

void directory_generate::traverse(json json_data, string path) {

    // Loop through sublevel
    for (size_t d = 0; d < json_data.size(); d++) {

        // Append current path to generation tree
        string cur_title = json_data[d]["title"];
        string new_path = path + "/" + cur_title;
        directory_generate::generation_tree[directory_generate::generation_tree.size()] = new_path;

        // Check if current level has sublevels, if so call the function again
        if (directory_generate::check_subs(json_data[d]["sub"])) {
            directory_generate::traverse(json_data[d]["sub"], new_path);
        }
    }

    return;
}

bool directory_generate::check_subs(json sub) {

    // Subs exist if sub is not null
    if (sub != nullptr) {
        return true;
    }
    return false;
}