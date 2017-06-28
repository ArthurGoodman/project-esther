#include <esther.h>

int main(int argc, const char **argv) {
    // if (argc < 2)
    //     return 0;

    Esther es;
    Esther_init(&es);

    Esther_runFile(&es, argc < 2 ? "../scripts/script.es" : argv[1]);

    Esther_finalize(&es);

    return 0;
}
