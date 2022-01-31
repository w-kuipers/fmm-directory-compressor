#include "make_dir.h"

bool os_sp::make_dir(std::string path) {

    if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        return true;
    }
    else {
        return false;
    }
}