#include "StdHash.h"

size_t StdHash::hash(const std::string& element) const{
    return std::hash<std::string>{}(element);
}

