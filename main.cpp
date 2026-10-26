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

    Config config;

    ClipCheck program(config.getObsFolder(), config.getDestinationFolder());
    program.watch();
}
