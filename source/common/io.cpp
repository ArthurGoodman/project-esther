#include "io.h"

// Read the file into a string.
string IO::readFile(string fileName) {
    ifstream f(fileName.data());

    if (!f) {
        cout << "error opening file '" << fileName << "'\n";
        return "";
    }

    ostringstream buffer;
    buffer << f.rdbuf();

    f.close();

    return buffer.str();
}

// Write data into a file.
void IO::writeFile(string fileName, string data) {
    ofstream f(fileName.data());

    if (!f)
        cout << "error opening file '" << fileName << "'\n";

    ostringstream buffer(data);
    f << buffer.str();

    f.close();
}

void IO::print(string data) {
    cout << data;
}

void IO::printLine(string data) {
    cout << data << endl;
}
