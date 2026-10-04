#include <iostream>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <string>

#include "ClipCheck_Windows.h"
#include "ClipCheck_Linux.h"
#include "Detect.h"
#include "config.h"

using namespace std;
using namespace filesystem;

int main(){

    // i want to make it so it sorts it but idk if its worth the time to figure that out
    Config config;

    ClipCheck program(config.getObsFolder(), config.getDestinationFolder());
    program.watch();
}