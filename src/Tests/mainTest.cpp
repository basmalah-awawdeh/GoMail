
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <functional>
#include <bitset>
#include"../src/BloomFilter/BloomFilter.h"
#include "../src/HashFunctions/HashFunction.h"
#include"../src/HashFunctions/DoubleHash.h"
#include "../src/UrlCheck/url_blacklist.h"
#include "../src/FileManager/BlacklistFileManager.h"
#include "../src/FileManager/BloomFilterFileManager.h"
#include "../src/UrlCheck/url_validation.h"
#include <filesystem>

// testing the StdHash class
TEST(HashFunctionTest, StdHashTest) {
    StdHash hash_func;
    std::string url = "www.example.com0";
    //just check that it return a non-zero valeu
    EXPECT_NE(hash_func.hash(url), 0);
    // checking that it returns the same hash for the same input
    EXPECT_EQ(hash_func.hash(url), hash_func.hash(url));
}
// testing the DoubleStdHash class
TEST(HashFunctionTest, DoubleHashTest) {
    DoubleStdHash hash_func;
    std::string url = "www.example.com0";
    // just check that it returns a non-zero valeu
    EXPECT_NE(hash_func.hash(url), 0);
    //checking that it returns the same hash for the same input
    EXPECT_EQ(hash_func.hash(url), hash_func.hash(url));
}

// test the HashFunctionFactory
TEST(HashFunctionFactoryTest, CreateHashFunctionTest) {
    auto hash1 = MakeHash::createHashFunction(1);
    auto hash2 = MakeHash::createHashFunction(2);
    EXPECT_NE(hash1, nullptr);
    EXPECT_NE(hash2, nullptr);
    // type check
    EXPECT_NE(dynamic_cast<StdHash*>(hash1.get()), nullptr);
    EXPECT_NE(dynamic_cast<DoubleStdHash*>(hash2.get()), nullptr);
}
//testing the Bloomfilter constructor
TEST(BloomFilterTest, ConstructorTest) {
    std::vector<std::shared_ptr<HashFunction>> hash_functions;
    hash_functions.push_back(std::make_shared<StdHash>());
    BloomFilter filter(8, hash_functions);
    EXPECT_EQ(filter.getSize(), 8);
    EXPECT_EQ(filter.getNumberOfHashes(), 1);
    //checking that all bits are false on the begining
    const auto& bit_array = filter.getArray();
    for (size_t i = 0; i < bit_array.size(); ++i) {
        EXPECT_FALSE(bit_array[i]);
    }
}
//testing adding an item to the Bloomfilter
TEST(BloomFilterTest, AddTest) {
    std::vector<std::shared_ptr<HashFunction>> hash_functions;
    hash_functions.push_back(std::make_shared<StdHash>());
    BloomFilter filter(8, hash_functions);
    filter.add("www.example.com0");
    //at least one bit should be set
    const auto& bit_array = filter.getArray();
    bool any_bit_set = false;
    for (size_t i = 0; i < bit_array.size(); ++i) {
        if (bit_array[i]) {
            any_bit_set = true;
            break;
        }
    }
    EXPECT_TRUE(any_bit_set);
}

//testing checking if an item might be in the Bloomfilter
TEST(BloomFilterTest, MightContainTest) {
    std::vector<std::shared_ptr<HashFunction>> hash_functions;
    hash_functions.push_back(std::make_shared<StdHash>());
    BloomFilter filter(8, hash_functions);
    filter.add("www.example.com0");
    //check if might contains URLs
    EXPECT_TRUE(filter.isFound("www.example.com0"));
    EXPECT_FALSE(filter.isFound("www.example.com"));
    EXPECT_TRUE(filter.isFound("www.example.com11"));
}
//testing the URLBlakclist
TEST(URLBlacklistTest, BasicFunctionalityTest) {
    std::vector<std::shared_ptr<HashFunction>> hash_functions;
    hash_functions.push_back(std::make_shared<StdHash>());
    auto bloom_filter = std::make_shared<BloomFilter>(8, hash_functions);
    BlacklistURL blacklist(bloom_filter);
    //at first there no URLs are blacklisted
    EXPECT_FALSE(blacklist.isBlacklisted("www.example.com0"));
    EXPECT_FALSE(blacklist.isFalsePositive("www.example.com0"));
    //add URL to the blacklist
    blacklist.addURL("www.example.com0");
    //now the URL should be blacklisted
    EXPECT_TRUE(blacklist.isBlacklisted("www.example.com0"));
    EXPECT_TRUE(blacklist.isFalsePositive("www.example.com0"));
    // checking for another URL that are in blacklist but is not falsePositive
    EXPECT_TRUE(blacklist.isBlacklisted("www.example.com11"));
    EXPECT_FALSE(blacklist.isFalsePositive("www.example.com11"));
    // checking for another URL that are not in blacklist and also is not falsePositive
    EXPECT_FALSE(blacklist.isBlacklisted("www.example.com"));
    EXPECT_FALSE(blacklist.isFalsePositive("www.example.com"));
}
//testig checking validURLs
TEST(URLValidationTest, ValidURLs){
    //valid URLs
    EXPECT_TRUE(isValidURL("http://www.example.com"));
    EXPECT_TRUE(isValidURL("https://www.example.com"));
    EXPECT_TRUE(isValidURL("www.example.com"));
    EXPECT_TRUE(isValidURL("http://example.com"));
    EXPECT_TRUE(isValidURL("https://example.com"));
    // not valid URLs
    EXPECT_FALSE(isValidURL("www."));
    EXPECT_FALSE(isValidURL(" "));
    EXPECT_FALSE(isValidURL("https://"));
    EXPECT_FALSE(isValidURL("example."));
}

//testing saving and loading the URL blacklist
TEST(FileManagerTest, SaveLoadTest) {
    //creating a directory for testing
    std::filesystem::create_directories("data");
    std::vector<std::shared_ptr<HashFunction>> hash_functions;
    hash_functions.push_back(std::make_shared<StdHash>());
    auto bloom_filter = std::make_shared<BloomFilter>(8, hash_functions);
    BlacklistURL blacklist(bloom_filter);
    //adding a URL to the blacklist
    blacklist.addURL("www.example.com0");
    //saving the blacklist
    BlacklistFileManager blackFile("data/blacklist.dat");
    BloomFilterFileManager bloomFile("data/bloom_filter.dat");
    // checking if the fiels saved
    EXPECT_TRUE(blackFile.save(blacklist));
    EXPECT_TRUE(bloomFile.save(blacklist));
    // creating new blacklist
    auto new_bloom_filter = std::make_shared<BloomFilter>(8, hash_functions);
    BlacklistURL new_blacklist(new_bloom_filter);
    //loading the saved blacklist
    EXPECT_TRUE(blackFile.load(new_blacklist));
    EXPECT_TRUE(bloomFile.load(new_blacklist));
    // checking that the loaded blacklist has the correct URL
    EXPECT_TRUE(new_blacklist.isBlacklisted("www.example.com0"));
    EXPECT_TRUE(new_blacklist.isFalsePositive("www.example.com0"));
    //cleaning up
    std::filesystem::remove_all("data");
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//g++ -std=c++17 -isystem /path/to/gtest/include -L /path/to/gtest/lib src/mainTest.cpp src/FileManager/BlacklistFileManager.cpp src/FileManager/BloomFilterFileManager.cpp src/HashFunctions/HashFunctionFactory.cpp src/HashFunctions/StdHash.cpp src/HashFunctions/DoubleHash.cpp src/UrlCheck/url_validation.cpp src/UrlCheck/url_blacklist.cpp src/BloomFilter/BloomFilter.cpp -lgtest -lgtest_main -pthread -o bloom_filter_test

/*
cd /mnt/c/Users/בסמלה/Desktop/barIlan/programming/GoMail/GoMail
rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)
ctest --output-on-failure
*/
