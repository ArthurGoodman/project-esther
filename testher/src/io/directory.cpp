#include "directory.h"

#ifdef __WIN32
#include <windows.h>
#endif

#include "file.h"

Directory::Directory() {
}

Directory::Directory(const std::string &path) {
    setPath(path);
}

bool Directory::exists() const {
#ifdef __WIN32
    DWORD fileAttributes = GetFileAttributesA(path.c_str());
    return fileAttributes != INVALID_FILE_ATTRIBUTES && (fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
#endif
    return false;
}

std::string Directory::getPath() const {
    return path;
}

void Directory::setPath(const std::string &path) {
#ifdef __WIN32
    char buffer[MAX_PATH];
    GetFullPathNameA(path.c_str(), MAX_PATH, buffer, 0);
    this->path = buffer;
#endif
}

std::string Directory::getName() const {
    std::size_t i = path.find_last_of("/\\");
    return path.substr(i + 1, path.size());
}

std::list<File> Directory::getFiles() const {
#ifdef __WIN32
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
#endif
    return {};
}
