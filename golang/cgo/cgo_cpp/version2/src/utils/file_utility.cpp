#include "file_utility.h"

#include <stdio.h>

/*
abc.txt => Path: , basename: abc, ext: txt
./abc.zip => Path: ./, basename: abc, ext: zip
ab/abc.Zip => Path: ab/, basename: abc, ext: Zip
a/b/c/file.zip => Path: a/b/c/, basename: file, ext: zip
a/b/abcd => Path: a/b/, basename: abcd, ext: 
*/
bool CFileUtility::SplitFileName(const std::string& filename, 
    std::string& path, std::string& basename, std::string& ext)
{
    //std::cout<<"filename:"<<filename<<std::endl;
    std::size_t pos = filename.rfind('/');
    if (std::string::npos == pos) {
        path = "";
        basename = filename;
    } else {
        pos++;
        path = filename.substr(0, pos);
        basename = filename.substr(pos);
    }

    //std::cout<<"pos:"<<pos<<", basename:"<<basename<<std::endl;

    pos = basename.find('.');
    if (std::string::npos == pos) {
        ext = "";
    } else {
        ext = basename.substr(pos + 1);
        basename = basename.substr(0, pos);
    }

    //std::cout<<"pos:"<<pos<<", basename:"<<basename<<", ext: "<<ext<<std::endl;

    return true;
}