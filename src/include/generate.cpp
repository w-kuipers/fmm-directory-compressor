#include "generate.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

std::string sub_directory = "../tests/";

void dg::generate(std::string root_directory_name, Json::Value data) {

    std::string root_path = sub_directory + root_directory_name;

    // Create root directory with read/write/execute permissions
    if (mkdir(root_path.c_str(), 0777) == -1) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
    }
        
    else {
        std::cout << "Sucessfully generated directory structure" << std::endl;
    }

    // Loop through subdirectories
    for (int d = 0; d < data["structure"].size(); d++) {

        // Get directory name
        std::string directory_name = data["structure"][d]["title"].asString();

        // Format path
        std::string full_path = root_path + "/" + directory_name;

        // Create directory
        if (mkdir(full_path.c_str(), 0777) == -1) {
            std::cerr << "Error: " << strerror(errno) << std::endl;
        }
            
        else {
            std::cout << "Sucessfully generated directory structure" << std::endl;
        }
    }
}

void dg::from_file(std:: string root_directory_name, std::string file_string) {

    // Read file
    std::ifstream file(file_string);

    // Parse JSON from file
    Json::Value data;
    Json::Reader json_reader;
    json_reader.parse(file, data);

    // Call function to generate 
    dg::generate(root_directory_name, data);
}
