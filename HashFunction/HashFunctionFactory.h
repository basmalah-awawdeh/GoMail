#ifndef HASH_FUNCTION_FACTORY_H
#define HASH_FUNCTION_FACTORY_H

#include "HashFunction.h"
#include <memory>

class MakeHash {
    public:
    static std::shared_ptr<HashFunc> CreateHashFunc(int type);

};

#endif // HASH_FUNCTION_FACTORY_H
