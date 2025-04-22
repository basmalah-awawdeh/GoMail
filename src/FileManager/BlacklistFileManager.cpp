#include "BlacklistFileManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>


// Constructor that initalize the file manager
BlacklistFileManager::BlacklistFileManager(const std::string& filename)
    : blacklist_filename(filename) {}


// Save the blacklist data to a file
bool BlacklistFileManager::save(const BlacklistURL& blacklist) {
    // Open the file in write mode
    std::ofstream blacklist_file(blacklist_filename);
    if (!blacklist_file) {
        return false;
    }

    // Loop through each blacklisted URL and write it to the file
    for (const auto& url : blacklist.getBlacklisted()) {
        blacklist_file << url << std::endl;
    }

    return true;
}

// Load the blacklist data from a file
bool BlacklistFileManager::load(BlacklistURL& blacklist) {
    
    // Open the file in read mode
    std::ifstream blacklist_file(blacklist_filename);
    if (!blacklist_file) {
        return false;
    }


    std::vector<std::string> urls;// Vector to store the URLs that we read from file
    std::string url;

    // Read each line in the file and insert into the vector
    while (std::getline(blacklist_file, url)) {
        urls.push_back(url);
    }

    // Set the loaded URLs to the blacklist
    blacklist.setBlacklisted(urls);

    return true;
}

// Check if the blacklist file exist
bool BlacklistFileManager::filesExist() const {
    // To check if the file exists at the given path
    return std::filesystem::exists(blacklist_filename);
}
