#ifndef MKDIR_UNIX_H
#define MKDIR_UNIX_H

#include <iostream>
#include <sys/stat.h>

namespace os_sp {
    bool make_dir(std::string path);
} // namespace os

#endif