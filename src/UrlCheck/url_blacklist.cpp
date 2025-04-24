#include "url_blacklist.h"
#include <algorithm>

BlacklistURL::BlacklistURL(std::shared_ptr<BloomFilter> bloomfilter)
    : bloomfilter(bloomfilter) {
}

// adding  Url to blacklist
void BlacklistURL::addURL(const std::string& url) {
    bloomfilter->add(url);
    blacklisted.push_back(url);
}

//if Url is blacklist ==>true,o.w false 
bool BlacklistURL::isBlacklisted(const std::string& url) const {
    bool found = bloomfilter->isFound(url);
    return found;
}

// if Url is actually in blacklist and not falsePositive ==> true, o.w false 
bool BlacklistURL::isFalsePositive(const std::string& url) const {
    bool falsePositive =std::find(blacklisted.begin(), blacklisted.end(), url) != blacklisted.end();
    return falsePositive;
}

// getting blacklist Urls
const std::vector<std::string>& BlacklistURL::getBlacklisted() const {
    return blacklisted;
}

// setting blacklist URLs
void BlacklistURL::setBlacklisted(const std::vector<std::string>& urls) {
    blacklisted = urls;
}

//getting bloomfilter
std::shared_ptr<BloomFilter> BlacklistURL::getBloomFilter() const {
    return bloomfilter;
}