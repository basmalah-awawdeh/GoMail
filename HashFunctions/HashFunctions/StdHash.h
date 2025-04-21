#ifndef STD_HASH_H
#define STD_HASH_H

#include "HashFunction.h"

// Standard hash implementation
class StdHash : public HashFunc {
    public:
        size_t hash(const std::string& url) const override;
    };
#endif // STD_HASH_H
