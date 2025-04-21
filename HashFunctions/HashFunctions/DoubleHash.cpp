#include "DoubleHash.h"
#include <functional>

size_t DoubleStdHash::hash(const std::string& url) const{
    std::string first = std::to_string(std::hash<std::string>{}(url));
    size_t second = std::hash<std::string>{}(first);
    return second;
}

