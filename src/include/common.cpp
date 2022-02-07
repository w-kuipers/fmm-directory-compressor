#include "common.h"

std::string random_generation::str() {
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    std::string::size_type length = 8;

    s.reserve(length);

    while(length--)
        s += chrs[pick(rg)];

    return s;
}