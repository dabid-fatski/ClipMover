#pragma once

#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

class ClipMove{
    private:
        path destinationFolder;
        path clipPath;
        string clipName;

    public:
        ClipMove(path clip, path destination, string name);
        ~ClipMove();

        void moveClip();
};