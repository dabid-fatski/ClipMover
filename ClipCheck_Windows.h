#ifdef _WIN32
#pragma once

#include <iostream>
#include <filesystem>
#include <windows.h>

using namespace std;
using namespace filesystem;

class ClipCheck{
    private:
        path folderPath;
        path destinationFolder;
        HANDLE folder;

        
    public:
        ClipCheck(path folderPath, path destination);
        ~ClipCheck();

        void watch();
        bool ifReady(const path& filePath);
};
#endif