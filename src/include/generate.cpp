#include "generate.h"


// TODO use jsoncpp instead of json.hpp
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
        }
    }

    // Generate files
    for (size_t fp = 0; fp < directory_generate::file_generation_tree.size(); fp++) {
        string cur_filename = directory_generate::file_generation_tree[fp];
        ofstream cur_file(cur_filename);
        cur_file << "temp data"; // TODO get real data
        cur_file.close();
    }
    
}

void directory_generate::create_generation_tree(string root_directory_name, json json_data, string location) {

    // Append root directory to generation tree
    string root_path = location + root_directory_name;
    directory_generate::generation_tree[0] = root_path;

    // Call recursive functions to walk through JSON tree
    directory_generate::traverse(json_data["structure"], root_path);

    return;
}

void directory_generate::traverse(json json_data, string path) {

    // Loop through sublevel
    for (size_t d = 0; d < json_data.size(); d++) {

        // Create new path
        string cur_title = json_data[d]["title"];
        string new_path = path + "/" + cur_title;

        // Check if current iteration type is file
        if (json_data[d]["type"] == "directory") {

            // Add directory path to generation tree
            directory_generate::generation_tree[directory_generate::generation_tree.size()] = new_path;

            // Check if current level has sublevels, if so call the function again
            if (directory_generate::check_subs(json_data[d]["content"])) {
                directory_generate::traverse(json_data[d]["content"], new_path);
            }
        }

        // Check if current iteration type is file
        if (json_data[d]["type"] == "file") {

            // Add file path to file generation tree
            directory_generate::file_generation_tree[directory_generate::file_generation_tree.size()] = new_path;
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

void generate_file::create(const bfs::path &dir_path) {
    
    

    Json::Value generated_structure = generate_file::traverse(dir_path);

    Json::Value structure_root;
    structure_root["template_name"] = "test";
    structure_root["structure"] = generated_structure;

    ofstream cur_file("../../tests/generated_test.json");
    cur_file << structure_root;
    cur_file.close();
        
};


Json::Value generate_file::traverse(const bfs::path &dir_path) {

    // Init JSON
    Json::Value generated_structure(Json::arrayValue);

    // Iterate through directory dir_path
    bfs::directory_iterator end_itr;
    for (bfs::directory_iterator itr( dir_path );itr != end_itr; ++itr) {

        // Name of current iteration
        string cur_name = itr->path().filename().string();

        // If current iteration is directory
        if (!bfs::is_regular_file(itr->path())) {

             // Init JSON
            Json::Value dir_val;

            // Set JSON data
            dir_val["type"] = "directory";
            dir_val["title"] = cur_name;
            dir_val["content"] = generate_file::traverse(dir_path.string() + string("/") + cur_name); // Recursively call function again with current directory

            // Append
            generated_structure.append(dir_val);
        }

        // If current iteration is file
        if (bfs::is_regular_file(itr->path())) {

             // Init JSON
            Json::Value file_val;

            // Set JSON data 
            file_val["type"] = "file";
            file_val["title"] = cur_name;

            // Append
            generated_structure.append(file_val);
        }
    }

    return generated_structure;
}