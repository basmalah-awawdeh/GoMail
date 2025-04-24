#include "CLI.h"
#include "../HashFunctions/HashFunctionFactory.h"
#include "../HashFunctions/StdHash.h"
#include "../HashFunctions/DoubleHash.h"
#include "../HashFunctions/HashFunction.h"
#include "../UrlCheck/url_validation.h"
#include <sstream>
#include <iostream>

// Function to create hash functions based on the provided types
std::vector<std::shared_ptr<HashFunction>> createHashFunctionsFromTypes(const std::vector<int>& hash_types) {
    std::vector<std::shared_ptr<HashFunction>> hash_functions;
    for (int type : hash_types) {
        hash_functions.push_back(MakeHash::createHashFunction(type)); // Factory for creating hash functions
    }
    return hash_functions;
}

// Helper function to find the first digit in a string
size_t getFirstDigitPosition(const std::string& str) {
    return str.find_first_of("0123456789");
}

// Parse configuration for size and hash function types
bool extractSizeAndHashTypes(const std::string& line, int& size, std::vector<int>& hash_types) {
    size_t pos = getFirstDigitPosition(line);
    if (pos == std::string::npos) {
        return false; // No digits found
    }

    std::istringstream iss(line.substr(pos));

    // Read the size
    if (!(iss >> size)) {
        return false; // Invalid size
    }

    // Read hash types
    int type;
    while (iss >> type) {
        // Add each hash type to the hash_types vector.
        hash_types.push_back(type); 
    }

    return !hash_types.empty(); // Ensure that hash types are provided
}

// Create and initialize the Bloom filter with the given size and hash functions
std::shared_ptr<BloomFilter> createBloomFilterWithHashes(int size, const std::vector<int>& hash_types) {
    auto hash_functions = createHashFunctionsFromTypes(hash_types);
    return std::make_shared<BloomFilter>(size, hash_functions);
}

// Handle user commands (adding/checking URLs) in a loop
void handleUserCommands(BlacklistFileManager& blacklistFileManager, BloomFilterFileManager& bloomFileManager, BlacklistURL& blacklist) {
    std::string line;
    while (std::getline(std::cin, line)) {
        size_t pos = getFirstDigitPosition(line);
        if (pos == std::string::npos) {
            continue; // No digits in line, skip
        }

        // Extract command from the string
        std::istringstream cmdStream(line.substr(pos));
        int cmd;
        
        if (!(cmdStream >> cmd)) {
            continue;  // Invalid format, ignore
        }

        std::string url;
        std::getline(cmdStream >> std::ws, url);

        // Switched based on command type(1- add, 2- checkURL)
        switch (cmd) {
            case 1:  // Add URL to blacklist

                // Validate the URL before adding
                if (!url.empty() && isValidURL(url)) {
                    blacklist.addURL(url);
                    blacklistFileManager.save(blacklist);
                    bloomFileManager.save(blacklist);
                }
                break;
                
            case 2:  // Check if URL is blacklisted
                if (blacklist.isBlacklisted(url)) {
                    
                    // Confirm if actually is black list
                    bool actuallyBlacklisted = blacklist.isFalsePositive(url);
                    std::cout << "true " << (actuallyBlacklisted ? "true" : "false") << std::endl;
                } else {
                    std::cout << "false" << std::endl; 
                }
                break;
                
            default:
                continue;  // Ignore invalid commands
        }
    }
}
