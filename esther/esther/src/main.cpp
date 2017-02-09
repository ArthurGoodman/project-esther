#include <esther.h>

#include <common/config.h>
#include <memory/conservativememorymanager.h>

int main(int argc, char **argv) {
#ifdef CONSERVATIVE_GC
    register uint32_t *ebp asm("ebp");
    es::ConservativeMemoryManager::initStack(ebp);
#endif

    // if (argc < 2)
    //     return 0;

    es::Esther esther;
    esther.runFile(argc < 2 ? "scripts/script.es" : argv[1]);

    return 0;
}
