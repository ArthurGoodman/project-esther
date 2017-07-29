#include <esther.h>

void IO_initialize(Esther *UNUSED(es), Context *UNUSED(context)) {
    printf("IO_initialize\n");
}

void IO_finalize(Esther *UNUSED(es)) {
    printf("IO_finalize\n");
}
