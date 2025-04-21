#ifndef URL_BLACKLIST_H
#define URL_BLACKLIST_H

#include <string>
#include <vector>
#include <memory>
#include "bloom_filter.h"

class BlacklistURL {
private:
    std::shared_ptr<BloomFilter> bloomfilter; // A Bloom filter used to check if a URL might be blacklisted
    std::vector<std::string> blacklisted; // A list of blacklisted URLs
    
public:
    // Constructor for BlackListURL.
    BlacklistURL(std::shared_ptr<BloomFilter> bloomfilter);
    
    // Add URL to blacklist
    void addURL(const std::string& url);
    
    // Check if URL is blacklisted
    bool isBlacklisted(const std::string& url) const;
    
    // Checking false positives(if url is actually in the blacklist)
    bool isFalsePositive(const std::string& url) const;
    
    // Get all blacklist url
    const std::vector<std::string>& getBlacklisted() const;
    
    // Set blacklisted URLs- used when loading from file
    void setBlacklisted(const std::vector<std::string>& urls);
    
    // Get the bloom filter
    std::shared_ptr<BloomFilter> getBloomFilter() const;
};

#endif 