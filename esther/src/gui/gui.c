#define __x86_64

#include <esther.h>

void __declspec(dllexport) GUI_initialize(Esther *es, Context *context) {
    printf("GUI_init\n");
}

void __declspec(dllexport) GUI_finalize(Esther *es) {
}
