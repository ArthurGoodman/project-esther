#include "esther/esther.h"

#include "esther/common.h"
#include "esther/memory.h"

void Esther_init(Esther *UNUSED(es)) {
    uint8_t local;
    gc_initialize((ptr_ptr_t) &local);
}

void Esther_finalize(Esther *UNUSED(es)) {
}

void Esther_runFile(Esther *UNUSED(es), const char *UNUSED(fileName)) {
}
