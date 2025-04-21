#include "BloomFilter.h"


BloomFilter::BloomFilter(size_t size, const std::vector<std::shared_ptr<HashFunc>>& hashes) 
 : bits(size, false), hashes(hashes), size(size) {
}
bool BloomFilter::isFound(const std::string& element) const{
    size_t s=0, val=0;
    while(s<hashes.size()){
        val = hashes[s]->hash(element) % s;
        if (bits[val]==false) return false;
        ++s;
    }
    return true;
}

void BloomFilter::add(const std::string& element){
    size_t s=0, val=0;
    while(s<hashes.size()){
        val = hashes[s]->hash(element) % s;
        bits[val]=true;
        ++s;
    }
}

size_t BloomFilter::getSize() const{
    return size;
}

size_t BloomFilter::getNumberOfHashes() const{
    return hashes.size();
}

const std::vector<bool>& BloomFilter::getArray() const{
    return bits;
}

void BloomFilter::setarray(const std::vector<bool>& newArray){
    if(newArray.size()==size)
    bits=newArray;
}