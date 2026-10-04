#ifdef _WIN32

#include <iostream>
#include <windows.h>
#include <filesystem>

#include "Detect.h"

using namespace std;
using namespace filesystem;

// get the process
string Detect::getForegroundProcess(){
    // gets the active window
    HWND curWindow = GetForegroundWindow();

    if (curWindow == nullptr){
        return "";
    }

    // get the process ID
    DWORD processID;
    // this asks windows which process owns the curWindow
    GetWindowThreadProcessId(curWindow, &processID);

    // we have the id of the ID windows uses to identify the running process
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);
    // if windows prevents opening the process, stop
    if (process == nullptr){
        return "";
    }

    // find the process's executable
    // place to store the name
    char processName[MAX_PATH];
    DWORD size = MAX_PATH;

    // using the process handle, tell me the full path of the executable and put it into processName
    if (!QueryFullProcessImageNameA(process, 0, processName, &size)){
        CloseHandle(process);
        return "";
    }

    CloseHandle(process);
    return string(processName, size);
}

// use the process to get the name
string Detect::getProcessName(){
    string processPath = getForegroundProcess();
    if (processPath.empty()){
        cout << "OpenProcess failed: " << GetLastError() << endl;
        return "Replay";
    }

    path exePath(processPath);
    string exeName = exePath.stem().string();

    if (games.find(exeName) != games.end()){
        return games[exeName];
    }
    
    return exeName;
}

#endif