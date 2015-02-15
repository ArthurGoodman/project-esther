#include "common.h"
#include "io.h"
#include "esther.h"
#include "debug.h"

int main(int argc, char **argv) {
    //if(argc < 2) return 0;

    string fileName = argc < 2 ? "scripts/test.es" : argv[1];
    Esther::runFile(fileName);

    return 0;
}
