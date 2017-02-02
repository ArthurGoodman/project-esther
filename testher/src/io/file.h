#pragma once

#include <string>

class File {
    std::string path;

public:
    File();
    File(const std::string &path);

    bool exists() const;

    std::string getPath() const;
    void setPath(const std::string &path);

    std::string getDirectoryPath() const;
    std::string getName() const;

    std::string read() const;
};
