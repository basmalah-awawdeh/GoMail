#ifndef I_FILE_MANAGER_H
#define I_FILE_MANAGER_H

#include <string>
#include "../UrlCheck/url_blacklist.h"  

class IFileManager {
public:
    virtual ~IFileManager() = default;  

    // Save data to file
    virtual bool save(const BlacklistURL& blacklist) = 0;  
    
    // Load data from file
    virtual bool load(BlacklistURL& blacklist) = 0; 
    
    // Check if files exist
    virtual bool filesExist() const = 0; 
};

#endif
