#include "generate.h"

using namespace dg;

void dg::structure_generate(std::string directory_name) {

    std::string full_path = sub_directory + directory_name;

    // Generate directory
    if (mkdir(full_path.c_str(), 0777) == -1) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
    }
        
    else {
        std::cout << "Sucessfully generated directory structure" << std::endl;
    }
}