#include "DoubleHash.h"
#include <functional>

size_t StdDoubleHash::hash(const std::string& element) const{
    std::string first = std::to_string(std::hash<std::string>{}(element));
    size_t second = std::hash<std::string>{}(first);
    return second;
}

