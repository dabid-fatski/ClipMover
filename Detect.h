#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class Detect{
    private:
        // have this map exe names to the game name
        // idk what to do about possible duplicates
        unordered_map<string, string> games = {};

    public:
        string getForegroundProcess();
        string getProcessName();
        bool isGame();
};