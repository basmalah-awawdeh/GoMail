#ifndef HASH_FUNCTION_FACTORY_H
#define HASH_FUNCTION_FACTORY_H

#include "HashFunction.h"
#include <memory>

// Factory to create hash functions
class MakeHash {
    public:
        static std::shared_ptr<HashFunc> CreateHashFunc(int input);
    };

#endif // HASH_FUNCTION_FACTORY_H
