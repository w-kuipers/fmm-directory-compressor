#ifndef MKDIR_WIN_H
#define MKDIR_WIN_H

#include <windows.h>
#include <iostream>

namespace os_sp {
    bool make_dir(std::string path);
} // namespace os

#endif