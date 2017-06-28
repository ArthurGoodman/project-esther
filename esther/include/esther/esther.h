#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Esther {
} Esther;

void Esther_init(Esther *es);
void Esther_finalize(Esther *es);

void Esther_runFile(Esther *es, const char *fileName);

#ifdef __cplusplus
}
#endif
