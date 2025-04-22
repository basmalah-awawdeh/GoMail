#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <memory>
#include "../BloomFilter/BloomFilter.h"
#include "../HashFunctions/HashFunction.h"
#include "../UrlCheck/url_blacklist.h"
#include "../FileManager/BlacklistFileManager.h"
#include "../FileManager/BloomFilterFileManager.h"

// Creates hash functions based on the types provided
std::vector<std::shared_ptr<HashFunction>> createHashFunctionsFromTypes(const std::vector<int>& hash_types);

// Extracts the size of the Bloom filter and the types of hash functions from the configuration string
bool extractSizeAndHashTypes(const std::string& line, int& size, std::vector<int>& hash_types);

// Create a new Bloom filter with specifed size and the list of hash.
std::shared_ptr<BloomFilter> createBloomFilterWithHashes(int size, const std::vector<int>& hash_types);

// Handle user commands (add/ check URL)
void handleUserCommands(BlacklistFileManager& blacklistFileManager, BloomFilterFileManager& bloomFileManager, BlacklistURL& blacklist);

#endif 
