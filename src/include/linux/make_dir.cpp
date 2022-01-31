#include "make_dir.h"

bool os_sp::make_dir(std::string path) {

    if (mkdir(path.c_str(), 0777) != -1) {
        return true;
    }
    else {
        return false;
    }
}