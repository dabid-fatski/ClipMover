#include <iostream>
#include <filesystem>
#include "ClipMove.h"

using namespace std;
using namespace filesystem;

ClipMove::ClipMove(path clip, path destination){
    destinationFolder = destination;
    clipPath = clip;
}

void ClipMove::moveClip(){
    try {
        rename(clipPath, destinationFolder / clipPath.filename());
        cout << "Move succeeded" << endl;
    } catch (const filesystem_error& e) {
        cout << "Move failed" << endl;
    }
    
}