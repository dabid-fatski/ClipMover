#pragma once

#include <iostream>
#include <filesystem>
#include <windows.h>

using namespace std;
using namespace filesystem;

class ClipCheck{
    private:
        HANDLE folder;
        path folderPath;
        path destinationFolder;

    public:
        ClipCheck(path folderPath, path destination);
        ~ClipCheck();

        void watch();
};