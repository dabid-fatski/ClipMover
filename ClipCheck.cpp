#include <iostream>
#include <filesystem>
#include <windows.h>
#include <thread>
#include <chrono>

#include "ClipCheck.h"
#include "ClipMove.h"

using namespace std;
using namespace filesystem;

ClipCheck::ClipCheck(path folderPath, path destination){
    this->folderPath = folderPath;
    destinationFolder = destination;

    folder = CreateFileW(
        folderPath.c_str(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        nullptr
    );
}

ClipCheck::~ClipCheck(){
    CloseHandle(folder);
}

void ClipCheck::watch(){
    char buffer[1024];
    DWORD bytesReturned;

    // waits until it sees a new file
    ReadDirectoryChangesW(
        folder,
        buffer,
        sizeof(buffer),
        FALSE,
        FILE_NOTIFY_CHANGE_FILE_NAME,
        &bytesReturned,
        nullptr,
        nullptr
    );

    // waits until something gets added
    FILE_NOTIFY_INFORMATION* info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);
    // its a pointer because we are pointing to raw memory (buffer)
    if (info->Action == FILE_ACTION_ADDED){
        // get the path to the file
        wstring fileName(info->FileName, info->FileNameLength / sizeof(WCHAR));
        path filePath = folderPath / fileName;

        // waits 3 seconds after it gets a noti
        this_thread::sleep_for(chrono::seconds(3));

        // moves it
        ClipMove mover(filePath, destinationFolder);
        mover.moveClip();
    }
}