#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H

#include "HashFunction.h"

class StdDoubleHash : public HashFunc {
    public: 
    size_t hash(const std::string& url) const override;
};

#endif // DOUBLE_HASH_H
