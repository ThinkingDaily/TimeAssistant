#ifndef __FILE_UTILITY_H
#define __FILE_UTILITY_H

#include <stdbool.h>
#include <string>

class CFileUtility {
public:
    static bool SplitFileName(const std::string& filename, std::string& path, 
        std::string& basename, std::string& ext);

};


#endif
