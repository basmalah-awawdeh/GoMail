#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <memory>
#include <string>
#include <functional>

// Abstract base class for hash functions
class HashFunc {
    public:
        virtual size_t hash(const std::string& url) const = 0;
        virtual ~HashFunc() = default;
    };

#endif // HASH_FUNCTION_H
