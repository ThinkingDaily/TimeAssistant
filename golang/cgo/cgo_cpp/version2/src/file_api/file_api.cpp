#include "file_api.h"

#include <stdio.h>
#include <string>
#include "file_utility.h"

bool split(const char* filename)
{
    if (NULL == filename) {
        printf("Nul filename.\n");
        return false;
    }

    std::string file_name(filename);
    std::string path;
    std::string basename;
    std::string ext;
    CFileUtility::SplitFileName(file_name, path, basename, ext);
    printf("file name: %s, path: %s, base name: %s, ext: %s\n",
        file_name.c_str(), path.c_str(), basename.c_str(), ext.c_str());
    return true;
}
