#include "StdHash.h"

size_t StdHash::hash(const std::string& url) const{
    return std::hash<std::string>{}(url);
}
