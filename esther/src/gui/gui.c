#if defined(__WIN64)
#define __x86_64
#endif

#include <esther.h>

#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#define EXPORT
#define IMPORT
#endif

void EXPORT GUI_initialize(Esther *es, Context *context) {
    printf("GUI_init\n");
}

void EXPORT GUI_finalize(Esther *es) {
}
