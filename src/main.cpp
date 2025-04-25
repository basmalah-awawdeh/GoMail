#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "BloomFilter/BloomFilter.h"
#include "HashFunctions/HashFunction.h"
#include "UrlCheck/url_blacklist.h"
#include "FileManager/BlacklistFileManager.h"
#include "FileManager/BloomFilterFileManager.h"
#include "CLI/CLI.h"  

int main() {
    std::string line;
    int size = 0;
    std::vector<int> hash_types;
    // reading input lines and ignoring invalid until we get a valid configuration for size and hash functions
    while (size==0 && std::getline(std::cin, line)) {
        if (inputExtracting(line, size, hash_types)) {
            break;
        }
    }
    // no valid configuration is found
    if (size==0 || hash_types.empty()) {
        return 1;
    }
    // initializing Bloom filter with size and hash functions from input
    auto bloom_filter = blommFilterhashesCreating(size, hash_types);
    // creating a blacklistURL that will use the bloom filter for Url checking
    BlacklistURL blacklist(bloom_filter);
    // creating a file manager object
    BloomFilterFileManager bloomFileManager("/usr/src/myapp/data/bloom_filter.txt");
    BlacklistFileManager blacklistFileManager("/usr/src/myapp/data/blacklist.txt");
    // loading existing data
    bloomFileManager.load(blacklist);
    blacklistFileManager.load(blacklist);
    //handling user commands
    commandsHandling(blacklistFileManager, bloomFileManager, blacklist);
    return 0;
}

//g++ -I./src/BloomFilter -I./src/HashFunction -I./src/UrlCheck -I./src/Tests -I./src/FileManager src/main.cpp     src/BloomFilter/BloomFilter.cpp src/HashFunctions/DoubleHash.cpp     src/HashFunctions/HashFunctionFactory.cpp src/HashFunctions/StdHash.cpp     src/UrlCheck/url_blacklist.cpp src/UrlCheck/url_validation.cpp     src/FileManager/BlacklistFileManager.cpp src/FileManager/BloomFilterFileManager.cpp src/CLI/CLI.cpp -o main
/*
cd /mnt/c/Users/בסמלה/Desktop/barIlan/programming/GoMail/GoMail/GoMail
 rm -rf build
 mkdir build
 cd build
  cmake ..
  make -j$(nproc)
   ctest --output-on-failure
*/
// docker build -t gomail .    
//docker run -v ${PWD}/data:/usr/src/myapp/data -it gomail
//enter input
//stop your docker and turn it on again -- from the app -> actions
//docker exec -it 3c485e11b29f823c4bdf1036d05247f10c13a0615ed5b45c87e61cee5e90ab6c /bin/bash -- change it as your container's id
//cd ..
//cd data
//ls
//cat blacklist.txt