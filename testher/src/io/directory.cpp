#include "directory.h"

#include <windows.h>

#include "file.h"

Directory::Directory() {
}

Directory::Directory(const std::string &path) {
    setPath(path);
}

bool Directory::exists() const {
    DWORD fileAttributes = GetFileAttributesA(path.c_str());
    return fileAttributes != INVALID_FILE_ATTRIBUTES && (fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

std::string Directory::getPath() const {
    return path;
}

void Directory::setPath(const std::string &path) {
    char buffer[MAX_PATH];
    GetFullPathNameA(path.c_str(), MAX_PATH, buffer, 0);
    this->path = buffer;
}

std::string Directory::getName() const {
    std::size_t i = path.find_last_of("/\\");
    return path.substr(i + 1, path.size());
}

std::list<File> Directory::getFiles() const {
    HANDLE handle = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAA findData;
    std::list<File> files;

    handle = FindFirstFileA((path + "\\*").c_str(), &findData);

    if (handle == INVALID_HANDLE_VALUE)
        return std::list<File>();

    do
        if (strcmp(findData.cFileName, ".") && strcmp(findData.cFileName, "..") && !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            files.push_back(path + "\\" + findData.cFileName);
    while (FindNextFileA(handle, &findData));

    FindClose(handle);

    return GetLastError() != ERROR_NO_MORE_FILES ? std::list<File>() : files;
}
