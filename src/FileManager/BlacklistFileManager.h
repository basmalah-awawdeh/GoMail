#ifndef BLACKLIST_FILE_MANAGER_H
#define BLACKLIST_FILE_MANAGER_H

#include "IFileManager.h"
#include "../UrlCheck/url_blacklist.h"
#include <string>

class BlacklistFileManager : public IFileManager {
private:
    std::string blacklist_filename;  // Filename for blacklist data
public:
    BlacklistFileManager(const std::string& filename = "data/blacklist.dat");
    bool save(const BlacklistURL& blacklist) override;
    bool load(BlacklistURL& blacklist) override;
    bool filesExist() const override;
};

#endif 
