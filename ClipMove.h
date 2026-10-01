#pragma once

#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

class ClipMove{
    private:
        path destinationFolder;
        path clipPath;

    public:
        ClipMove(path clip, path destination);
        
        void moveClip();
};