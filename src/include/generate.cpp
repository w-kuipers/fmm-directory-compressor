#include "generate.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <fstream>

std::string sub_directory = "../tests/";

void dg::generate(std::string directory_name) {

    std::ifstream file("../tests/test.json");

    Json::Value raw_json;
    Json::Reader json_reader;

    json_reader.parse(file, raw_json);

    std::cout << raw_json["template_name"] << endl;


    // std::string full_path = sub_directory + directory_name;

    // // Generate directory
    // if (mkdir(full_path.c_str(), 0777) == -1) {
    //     std::cerr << "Error: " << strerror(errno) << std::endl;
    // }
        
    // else {
    //     std::cout << "Sucessfully generated directory structure" << std::endl;
    // }
}