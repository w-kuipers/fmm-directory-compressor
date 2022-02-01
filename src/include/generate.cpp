#include "generate.h"

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

void generate_file::create(const bfs::path &dir_path) {
    
    // Setup JSON
    json structure;
    structure["template_name"] = "TEST";

    int count = 0;
    bfs::directory_iterator end_itr;
    for ( bfs::directory_iterator itr( dir_path );itr != end_itr; ++itr ) {
        cout << itr->path() << endl;
        cout << itr->path().filename() << endl;

        structure["structure"][count] = itr->path().filename().string();;

        cout << count << endl;

        count++;
    }

    ofstream cur_file("../tests/generated_test.json");
    cur_file << structure;
    cur_file.close();

    
    // directory_iterator it{p};
    // while (it != directory_iterator{}) {
    //     cout << *it++ << '\n';
    // }
        
};