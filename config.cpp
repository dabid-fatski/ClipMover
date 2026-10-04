#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "config.h"

using namespace std;
using namespace filesystem;

Config::Config(){
    load();
}

void Config::load(){
    ifstream file("config.txt");

    // if the file doesnt exist
    if (!file.is_open()){
        cout << "Please set the OBS Folder and Destination Folder" << endl;
        setFolders();
        return;
    }

    string obsPath;
    string destinationPath;

    getline(file, obsPath);
    getline(file, destinationPath);

    if (obsPath.empty() || destinationPath.empty()){
        cout << "Config incomplete" << endl;
        setFolders();
        return;
    }

    if (!obsPath.empty()){
        obsFolder = obsPath;
    }

    if (!destinationPath.empty()){
        destinationFolder = destinationPath;
    }
}

void Config::save(){
    ofstream file("config.txt");

    if (!file.is_open()){
        return;
    }

    file << obsFolder.string() << endl;
    file << destinationFolder.string() << endl;
}

void Config::setFolders(){
    string obsPath;
    string destinationPath;

    cout << "Config file not found, please configurate." << endl;
    cout << "Enter OBS folder path: ";
    cin >> obsPath;

    cout << "Enter Destination folder path: ";
    cin >> destinationPath;

    obsFolder = obsPath;
    destinationFolder = destinationPath;

    save();
    cout << "Config saved" << endl;
}

void Config::setObsFolder(path obsFolder){
    this->obsFolder = obsFolder;
}

void Config::setDestinationFolder(path destinationFolder){
    this->destinationFolder = destinationFolder;
}

path Config::getObsFolder() const{
    return obsFolder;
}

path Config::getDestinationFolder() const{
    return destinationFolder;
}