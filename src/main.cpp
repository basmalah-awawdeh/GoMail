#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../BloomFilter/BloomFilter.h"
#include "../HashFunctions/HashFunction.h"
#include "../UrlCheck/url_blacklist.h"
#include "../FileManager/BlacklistFileManager.h"
#include "../FileManager/BloomFilterFileManager.h"
#include "../CLI/CLI.h"  


int main() {
    std::string line;
    int size = 0;
    std::vector<int> hash_types;

    // Read input lines until we get a valid configuration for size and hash functions
    while (size == 0 && std::getline(std::cin, line)) {
        if (extractSizeAndHashTypes(line, size, hash_types)) {
            break; // Successfully parsed the configuration, exit the loop
        }
    }

    // If no valid configuration is found
    if (size == 0 || hash_types.empty()) {
        std::cerr << "Invalid size or no hash functions specified" << std::endl;
        return 1;
    }

    // Initialize the Bloom filter with the provided size and hash functions
    auto bloom_filter = createBloomFilterWithHashes(size, hash_types);

    // Create a blacklistURL that will use the bloom filter for URL checking
    BlacklistURL blacklist(bloom_filter);

    // Create a file manager object
    BloomFilterFileManager bloomFileManager("data/bloom_filter.dat");
    BlacklistFileManager blacklistFileManager("data/blacklist.dat");


    // Try to load existing data
    bloomFileManager.load(blacklist);
    blacklistFileManager.load(blacklist);
    // Handle user commands (add or checkURL)
    handleUserCommands(blacklistFileManager, bloomFileManager, blacklist);

    return 0;
}

//g++ -I./src/BloomFilter -I./src/HashFunction -I./src/UrlCheck -I./src/Tests -I./src/FileManager src/main.cpp     src/BloomFilter/BloomFilter.cpp src/HashFunctions/DoubleHash.cpp     src/HashFunctions/HashFunctionFactory.cpp src/HashFunctions/StdHash.cpp     src/UrlCheck/url_blacklist.cpp src/UrlCheck/url_validation.cpp     src/FileManager/BlacklistFileManager.cpp src/FileManager/BloomFilterFileManager.cpp src/CLI/CLI.cpp -o main