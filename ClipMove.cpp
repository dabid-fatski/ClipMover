#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "ClipMove.h"

using namespace std;
using namespace filesystem;

ClipMove::ClipMove(path clip, path destination, string name){
    destinationFolder = destination;
    clipPath = clip;
    clipName = name;
}

ClipMove::~ClipMove() = default;

void ClipMove::moveClip(){
    // rename the file to include the game name
    // get rid of the Replay and replace it with the name
    string newName = clipName + " " + clipPath.stem().string().substr(6) + clipPath.extension().string();

    int attempts = 0;
    // 3 attempts to move the clip
    // chances are it should never need to get to 3?
    while (attempts < 5){
        try {
            rename(clipPath, destinationFolder / newName);
            cout << "Move succeeded" << endl;
            return;
        } catch (const filesystem_error& e) {
            attempts++;
            cout << "Move failed. Attempt: " << attempts << "/5" << endl;
            if (attempts < 5){
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }
}
