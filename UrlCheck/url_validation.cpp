#include "url_validation.h"

// Basic URL validation using regular expressions
bool isValidURL(const std::string& url) {
    std::regex url_regex(R"(^(?:(?:file:///(?:[A-Za-z]:)?(?:/[^\s])?)|(?:(?:[A-Za-z][A-Za-z0-9+.\-])://)?(?:localhost|(?:[A-Za-z0-9\-]+\.)+[A-Za-z0-9\-]+|(?:\d{1,3}\.){3}\d{1,3})(?::\d+)?(?:/[^\s]*)?)$)");

    return std::regex_match(url, url_regex);
}
