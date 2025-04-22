#include "BloomFilterFileManager.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>

// Constructor that initalize the file manager for the bloom filter
BloomFilterFileManager::BloomFilterFileManager(const std::string& filename)
    : bit_array_filename(filename) {}


// Save the bloomFilter data to a file   
bool BloomFilterFileManager::save(const BlacklistURL& blacklist) {

    // Open the file in write mode
    std::ofstream bit_file(bit_array_filename, std::ios::binary);
    if (!bit_file) {
        return false;
    }

    // Get the bit array from the bloom filter
    const auto& bit_array = blacklist.getBloomFilter()->getArray();

    // Get the size of the bit array
    size_t size = bit_array.size();

    // Write the bit size of the bit array to the file
    bit_file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    // Convert the vector<bool> to bytes for better storage
    std::vector<unsigned char> bytes((size + 7) / 8);
    for (size_t i = 0; i < size; ++i) {
        if (bit_array[i]) {
            bytes[i / 8] |= (1 << (i % 8));
        }
    }
    
    // Write the bytes to the file
    bit_file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    return true;
}

// Load a bloom filter data from a file
bool BloomFilterFileManager::load(BlacklistURL& blacklist) {

    // open the file for reading mode
    std::ifstream bit_file(bit_array_filename, std::ios::binary);
    if (!bit_file) {
        return false;
    }

    size_t size; 
   
    //read the size of the bit array
    bit_file.read(reinterpret_cast<char*>(&size), sizeof(size));
    if (size != blacklist.getBloomFilter()->getSize()) {
        return false; // Size mismatch
    }

    // Read the bytes from the file
    std::vector<unsigned char> bytes((size + 7) / 8);
    bit_file.read(reinterpret_cast<char*>(bytes.data()), bytes.size());

    // Convert the bytes back to a vector<bool> to reconstruct the bit array
    std::vector<bool> bit_array(size, false);
    for (size_t i = 0; i < size; ++i) {
        if (bytes[i / 8] & (1 << (i % 8))) {
            bit_array[i] = true;
        }
    }

    // Set the bit array in the Bloom filter
    blacklist.getBloomFilter()->setarray(bit_array);
    return true;
}

// Check if the bloom filter file is exist
bool BloomFilterFileManager::filesExist() const {
    // To check if the file exists at the given path
    return std::filesystem::exists(bit_array_filename);
}
