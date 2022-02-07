#include "generate.h"

void directory_generate::from_file(string root_directory_name, string file_string, string location) {

    // Read file
    ifstream file(file_string);

    // Parse JSON from file
    Json::Value json_data;
    file >> json_data;

    // Call function to generate 
    directory_generate::create_generation_tree(root_directory_name, json_data, location);

    // Generate directory tree
    for (Json::Value::ArrayIndex p = 0; p < directory_generate::generation_tree.size(); p++) {
        if (!os_sp::make_dir(directory_generate::generation_tree[p].asString())) {
            return; // Break function if root fails to generate
        }
    }

    // Generate files
    for (Json::Value::ArrayIndex fp = 0; fp < directory_generate::file_generation_tree.size(); fp++) {
        string cur_filename = directory_generate::file_generation_tree[fp].asString();
        ofstream cur_file(cur_filename);
        cur_file << "temp data"; // TODO get real data
        cur_file.close();
    }
    
}

void directory_generate::create_generation_tree(string root_directory_name, Json::Value json_data, string location) {

    // Append root directory to generation tree
    string root_path = location + root_directory_name;
    directory_generate::generation_tree[0] = root_path;

    // Call recursive functions to walk through JSON tree
    directory_generate::traverse(json_data["structure"], root_path);

    return;
}

void directory_generate::traverse(Json::Value json_data, string path) {

    // Loop through sublevel
    for (Json::Value::ArrayIndex d = 0; d < json_data.size(); d++) {

        // Create new path
        string cur_title = json_data[d]["title"].asString();
        string new_path = path + "/" + cur_title;

        // Check if current iteration type is file
        if (json_data[d]["type"] == "directory") {

            // Add directory path to generation tree
            directory_generate::generation_tree[directory_generate::generation_tree.size()] = new_path;

            // Check if current level has sublevels, if so call the function again
            directory_generate::traverse(json_data[d]["content"], new_path);

        }

        // Check if current iteration type is file
        if (json_data[d]["type"] == "file") {

            // Add file path to file generation tree
            directory_generate::file_generation_tree[directory_generate::file_generation_tree.size()] = new_path;
        } 
    }
    return;
}

void generate_file::create(const bfs::path &dir_path, const string dst_path) {

    // Generate JSON structure by recursively going through the directory    
    Json::Value generated_structure = generate_file::traverse(dir_path);

    // Create JSON root with metadata and the structure appended
    Json::Value structure_root;
    structure_root["template_name"] = "test";
    structure_root["structure"] = generated_structure;

    // Write the JSON tree to a file
    ofstream cur_file(dst_path + "/structure.json");
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

void generate_zip::from_path(string path, string name, string location) {

    // Check if filename is available
    if (bfs::exists(location + name + ".fps")) {
        cout << "File already exists!" << endl;
        return;
    }

    // Check if location is available
    if (!bfs::exists(location)) {
        cout << "Destination directory not found!" << endl;
        return;
    }

    // Create random ID
    random_generation random;
    string s = random.str();

    // Create temp directory name and path
    string temp_directory_name = "FMM_genzipstruct_" + s;
    const string temp_directory_path = bfs::temp_directory_path().string() + "/" + temp_directory_name;

    // Create the directory
    bfs::create_directory(temp_directory_path);

    // Copy files to temp directory
    compress_directory cp;
    cp.gather_files(path, temp_directory_path);

    // Generate JSON structure file
    generate_file gf;
    gf.create(path, temp_directory_path);

    // Compress the directory into a .FPS file
    cp.compress(temp_directory_path, location + name + ".fps");

    // Remove temp directory
    bfs::remove_all(temp_directory_path);

    return;
}