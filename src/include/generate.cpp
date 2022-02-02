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
    directory_generate::traverse(json_data["structure"]["sub"], root_path); // Handles directories
    directory_generate::handle_files(json_data["structure"]["content"], root_path); // Handles files

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

        // Check if current level has files
        if (directory_generate::check_subs(json_data[d]["content"])) {
            directory_generate::handle_files(json_data[d]["content"], new_path);
        }

    }

    return;
}

void directory_generate::handle_files(json json_data, string path) {

    cout << json_data << endl;
    cout << path << endl;

    // Loop through sublevel
    for (size_t d = 0; d < json_data.size(); d++) {

        // Append current path to file generation tree
        string cur_title = json_data[d]["title"];
        string new_path = path + "/" + cur_title;

        directory_generate::file_generation_tree[directory_generate::file_generation_tree.size()] = new_path;
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

void generate_file::create(string dir_path) {
    
    

    Json::Value generated_structure = generate_file::traverse(dir_path);

    
    ofstream cur_file("../tests/generated_test.json");
    cur_file << generated_structure;
    cur_file.close();
        
};


// TODO convert filesystem stuff to boost
Json::Value generate_file::traverse(const string &dir_path) {

    DIR* dirp;
    struct dirent *p;
    dirp = opendir(dir_path.c_str());

    Json::Value generated_structure(Json::arrayValue);

    // If directory exists loop through it
    if (dirp) {
        while ((p = readdir(dirp)) != nullptr){
            if (strcmp( p->d_name, ".") == 0 || strcmp( p->d_name, "..") == 0) {
                continue;
            }

            // If current iteration is directory
            if (p->d_type == DT_DIR) {

                // Init JSON
                Json::Value dir_val;

                // Set JSON data
                dir_val["type"] = "directory";
                dir_val["name"] = p->d_name;
                dir_val["content"] = generate_file::traverse(dir_path + string("/") + string(p->d_name)); // Recursively call function again with current directory

                // Append
                generated_structure.append(dir_val);

            // If current iteration is file
            } else if (p->d_type == DT_REG) {

                // Init JSON
                Json::Value file_val;

                // Set JSON data 
                file_val["type"] = "file";
                file_val["name"] = p->d_name;

                // Append
                generated_structure.append(file_val);
            }
        }

    }
    return generated_structure;
}