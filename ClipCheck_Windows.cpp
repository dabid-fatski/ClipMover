#ifdef _WIN32

#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <windows.h>

#include "ClipCheck_Windows.h"
#include "ClipMove.h"
#include "Detect.h"

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
    Detect detect;
    char buffer[1024];
    // windows unsigned 32 bit int
    DWORD bytesReturned;

    while (true){
        // waits until it sees a new file
        bool check = ReadDirectoryChangesW(
            folder,
            buffer,
            sizeof(buffer),
            FALSE,
            FILE_NOTIFY_CHANGE_FILE_NAME,
            &bytesReturned,
            nullptr,
            nullptr
        );

        if (!check){
            cout << "ReadDirectoryChanges failed: " << GetLastError() << endl;
            break;
        }

        // converts the address that's pointing to the bytes in buffer to the FILE_NOTIFY_INFO structure
        FILE_NOTIFY_INFORMATION* info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);
        while (true){
            // its a pointer because we are pointing to raw memory (buffer)
            if (info->Action == FILE_ACTION_ADDED){
                // get the path to the file
                wstring fileName(info->FileName, info->FileNameLength / sizeof(WCHAR));
                path filePath = folderPath / fileName;

                if (filePath.extension() == L".mp4" || filePath.extension() == L".mov"){
                    // waits until it's done writing then moves
                    
                    if (ifReady(filePath)){
                        ClipMove mover(filePath, destinationFolder, detect.getProcessName());
                        mover.moveClip();
                        // couts the path
                        cout << detect.getForegroundProcess() << endl;
                    }
                }
            }
            // if there are no more clips to move, go back to waiting
            if (info->NextEntryOffset == 0){
                break;
            }

            /*
            if there are still things to move, point to the next noti
            reinterpret_cast<char*>(info) treats it as a pointer to individual bytes
            so take current address and move it forward NextEntryOffset bytes
            NextEntryOffset is how many bytes to move forward to get to the next noti
            */
            info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<char*>(info) + info->NextEntryOffset);
        }
        
    }
}

bool ClipCheck::ifReady(const path& filePath){
    uintmax_t prevSize = 0;
    int count = 0;

    while (true) {
        // make sure the file exists
        if (!exists(filePath)){
            count = 0;
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }

        uintmax_t curSize;

        // make sure the file is ready to be moved
        try {
            curSize = file_size(filePath);
        } catch (const filesystem_error&){
            count = 0;
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }

        if (curSize == prevSize && curSize) {
            count++;
        } else {
            count = 0;
        }

        if (count >= 3){
            return true;
        }

        prevSize = curSize;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
#endif