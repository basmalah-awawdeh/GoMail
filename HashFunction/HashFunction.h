#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <memory>
#include <string>
#include <functional>

class HashFunc {
    public:
    //default destructor
    virtual ~HashFunc() {}
    virtual size_t hash(const std::string& url) const=0;
};
#endif // HASH_FUNCTION_H
