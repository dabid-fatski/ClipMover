#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "ClipMove.h"

using namespace std;
using namespace filesystem;

ClipMove::ClipMove(path clip, path destination){
    destinationFolder = destination;
    clipPath = clip;
}

ClipMove::~ClipMove() = default;

void ClipMove::moveClip(){
    int attempts = 0;

    // 3 attempts to move the clip
    // chances are it should never need to get to 3?
    while (attempts < 3){
        try {
            rename(clipPath, destinationFolder / clipPath.filename());
            cout << "Move succeeded" << endl;
            return;
        } catch (const filesystem_error& e) {
            attempts++;
            cout << "Move failed. Attempt: " << attempts << "/3" << endl;
            if (attempts < 3){
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
    }
}