#pragma once

#include <filesystem>

using namespace std;
using namespace filesystem;

class Config{
    private:
        path obsFolder;
        path destinationFolder;

    public:
        Config();
        
        void setObsFolder(path obsFolder);
        void setDestinationFolder(path destinationFolder);
        void load();
        void save();
        void setFolders();

        path getObsFolder() const;
        path getDestinationFolder() const;
};