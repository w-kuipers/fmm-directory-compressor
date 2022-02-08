#include "generate.h"

void directory_generate::from_file(string root_directory_name, string file_string, string location) {

    // check if source file and dst directory exist
    if (!bfs::exists(file_string)) {
        std::cout << "Error: Source file does not exist!\n";
        return;
    }
    if (!bfs::exists(location)) {
        std::cout << "Error: Desination directory does not exist!\n";
        return;
    }
    if (bfs::exists(location + "/" + root_directory_name)) {
        std::cout << "Error: A directory with this name already exists!\n";
        return;
    }

    decompress_archive da;

    // Decompress JSON structure file
    string fetched_structure_raw = da.decompress(file_string.c_str(), "structure.json");

    // Convert data to JSON
    Json::Value fetched_structure;   
    Json::Reader reader;

    // Parse process
    bool parse_success = reader.parse(fetched_structure_raw, fetched_structure);
    if (!parse_success) {
        cout << "Failed to parse"
               << reader.getFormattedErrorMessages();
        exit(0);
    }

    // Call function to generate 
    directory_generate::create_generation_tree(root_directory_name, fetched_structure, location);

    // Generate directory tree
    for (Json::Value::ArrayIndex p = 0; p < directory_generate::generation_tree.size(); p++) {
        if (!os_sp::make_dir(directory_generate::generation_tree[p].asString())) {
            return; // Break function if root fails to generate
        }
    }

    // Create directory in user temp location
    random_generation random; 
    string s = random.str(); // Create random ID
    string temp_directory_name = "FMM_decompress_" + s;
    const string temp_directory_path = bfs::temp_directory_path().string() + "/" + temp_directory_name;
    bfs::create_directory(temp_directory_path); // Create the directory

    // Generate files
    for (Json::Value::ArrayIndex fp = 0; fp < directory_generate::file_generation_tree.size(); fp++) {

        // Get file path and id
        string cur_path = directory_generate::file_generation_tree[fp]["path"].asString();
        string cur_id = directory_generate::file_generation_tree[fp]["id"].asString();

        // Fetch file from zip archive
        da.decompress_bin(file_string.c_str(), cur_id.c_str(), temp_directory_path);

        ifstream src(temp_directory_path + "/" + cur_id, ios::binary);
        ofstream dst(cur_path, ios::binary);

        dst << src.rdbuf();
    }

    // Remove temp directory
    bfs::remove_all(temp_directory_path);
    
}

void directory_generate::create_generation_tree(string root_directory_name, Json::Value json_data, string location) {

    // Append root directory to generation tree
    string root_path = location + "/" + root_directory_name + "/";
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
            Json::Value cur_file_tree;
            cur_file_tree["path"] = new_path;
            cur_file_tree["id"] = json_data[d]["id"];
            directory_generate::file_generation_tree.append(cur_file_tree);
        }
    }
    
    return;
}

Json::Value generate_file::create(const bfs::path &dir_path, const string dst_path) {

    // Generate JSON structure by recursively going through the directory
    Json::Value generated_structure = generate_file::traverse(dir_path); // File array is defined in global class scope

    // Create JSON root with metadata and the structure appended
    Json::Value structure_root;
    structure_root["template_name"] = "test";
    structure_root["structure"] = generated_structure;

    // Write the JSON tree to a file
    ofstream cur_file(dst_path + "/structure.json");
    cur_file << structure_root;
    cur_file.close();

    // Return the file array
    return generate_file::file_array;
};


Json::Value generate_file::traverse(const bfs::path &dir_path) {

    // Init JSON
    Json::Value generated_structure(Json::arrayValue);

    // Iterate through directory dir_path
    bfs::directory_iterator end_itr;
    for (bfs::directory_iterator itr( dir_path );itr != end_itr; ++itr) {

        if (SKIPLONGPATHS == true) {
            if (itr->path().string().size() > 260) {
                continue;
            }
        }
        else {
            if (itr->path().string().size() > 260) {
                cerr << "Encountered a path that is larger than 260 characters." << endl;
                exit(0);
            }
        }
    

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

            // Random ID
            random_generation random;
            string file_id = random.str();

            // Init JSON
            Json::Value file_val;
            Json::Value id_val;

            // Set JSON data 
            file_val["type"] = "file";
            file_val["title"] = cur_name;
            file_val["id"] = file_id;

            id_val["path"] = itr->path().string();
            id_val["id"] = file_id;

            // Append
            generated_structure.append(file_val);
            generate_file::file_array.append(id_val);
        }
    }

    return generated_structure;
}

void generate_zip::from_path(string path, string name, string location) {

    // Check if source directory exists
    if (!bfs::exists(path)) {
        cout << "Error: Source directory not found!\n";
        return;
    }

    // Check if filename is available
    if (bfs::exists(location + "/" + name + ".fps")) {
        cout << "Error: File already exists!\n";
        return;
    }

    // Check if location is available
    if (!bfs::exists(location)) {
        cout << "Error: Destination directory not found!\n";
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

    // Generate JSON structure file
    generate_file gf;
    Json::Value file_array = gf.create(path, temp_directory_path); // Also returns file_array

    // Copy files to TEMP directory
    for (Json::Value::ArrayIndex f = 0; f < file_array.size(); f++) {

        ifstream src(file_array[f]["path"].asString(), ios::binary);
        ofstream dst(temp_directory_path + "/" + file_array[f]["id"].asString(), ios::binary);

        dst << src.rdbuf();
    }

    // Compress the directory into a .FPS file
    compress_directory cp;
    cp.compress(temp_directory_path, location + "/" + name + ".fps");

    // Remove temp directory
    bfs::remove_all(temp_directory_path);

    return;
}