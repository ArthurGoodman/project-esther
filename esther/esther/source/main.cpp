#include "estherstaticinterface.h"

int main(int argc, char **argv) {
    // if (argc < 2) return 0;

    std::string fileName = argc < 2 ? "scripts/script.es" : argv[1];
    EstherStaticInterface::runFile(fileName);

    return 0;
}
