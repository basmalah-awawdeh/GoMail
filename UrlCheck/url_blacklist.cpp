#include "url_blacklist.h"
#include <algorithm>

BlacklistURL::BlacklistURL(std::shared_ptr<BloomFilter> bloomfilter)
    : bloomfilter(bloomfilter) {
}

// Adding a URL to blacklist.
void BlacklistURL::addURL(const std::string& url) {
    bloomfilter->add(url);
    blacklisted.push_back(url);
}

// Return true if a URL is blacklist, false if not
bool BlacklistURL::isBlacklisted(const std::string& url) const {
    return bloomfilter->mightContain(url);
}

// Return true if a URL is actually is blacklist, false if not
bool BlacklistURL::isFalsePositive(const std::string& url) const {
    return std::find(blacklisted.begin(), blacklisted.end(), url) != blacklisted.end();
}

// Get blacklist URLs
const std::vector<std::string>& BlacklistURL::getBlacklisted() const {
    return blacklisted;
}

// Set blacklist URLs
void BlacklistURL::setBlacklisted(const std::vector<std::string>& urls) {
    blacklisted = urls;
}

// Get the bloomfilter
std::shared_ptr<BloomFilter> BlacklistURL::getBloomFilter() const {
    return bloomfilter;
}