#include "io.h"

#include <stdlib.h>

map<string, unique_ptr<fstream>> IO::files;

// Read the file into a string.
string IO::readFile(string fileName) {
    ifstream file(fileName.data());

    if (!file) {
        cout << "error opening file '" << fileName << "'\n";
        return "";
    }

    ostringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}

// Write data into a file.
void IO::writeFile(string fileName, string data) {
    ofstream file(fileName.data());

    if (!file)
        cout << "error opening file '" << fileName << "'\n";

    ostringstream buffer(data);
    file << buffer.str();

    file.close();
}

void IO::createDirectory(string name) {
    system(string("if not exist logs md " + name).data());
}

void IO::openFile(string fileName) {
    files[fileName] = unique_ptr<fstream>(new fstream(fileName.data(), ios::out | ios::trunc));
}

bool IO::isOpen(string fileName) {
    return files.find(fileName) != files.end();
}

void IO::writeToFile(string fileName, string data) {
    ostringstream buffer(data);
    *files[fileName] << buffer.str();
    files[fileName]->flush();
}

void IO::closeFile(string fileName) {
    files[fileName]->close();
    files.erase(fileName);
}

void IO::closeAllFiles() {
    foreach (i, files)
        i->second->close();

    files.clear();
}

void IO::print(string data) {
    cout << data;
}

void IO::printLine(string data) {
    cout << data << endl;
}

string IO::scan() {
    string str;
    cin >> str;
    return str;
}

string IO::scanLine() {
    string str;
    getline(cin, str);
    return str;
}

string IO::fullPath(string partialPath) {
    char path[_MAX_PATH];
    if (_fullpath(path, partialPath.data(), _MAX_PATH))
        return path;

    return "";
}
