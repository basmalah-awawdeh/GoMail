#ifndef BLOOM_FILTER_FILE_MANAGER_H
#define BLOOM_FILTER_FILE_MANAGER_H

#include "IFileManager.h"
#include "../UrlCheck/url_blacklist.h"
#include <string>

class BloomFilterFileManager : public IFileManager {
private:
    std::string bit_array_filename;  // Filename for Bloom filter data
public:
    BloomFilterFileManager(const std::string& filename = "data/bloom_filter.dat");

    bool save(const BlacklistURL& blacklist) override;
    bool load(BlacklistURL& blacklist) override;
    bool filesExist() const override;
};

#endif 
