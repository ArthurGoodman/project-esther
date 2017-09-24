#include <esther.h>

int main(int argc, const char **argv) {
    // if (argc < 2)
    //     return 0;

    uint8_t local;
    gc_initialize((ptr_ptr_t) &local);

    Esther es;
    Esther_init(&es);

    Esther_runScript(&es, argc < 2 ? "esther/scripts/script.es" : argv[1]);

    Esther_finalize(&es);

    return 0;
}
