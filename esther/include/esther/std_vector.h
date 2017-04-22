#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct std_vector;

struct std_vector *std_vector_new();
struct std_vector *std_vector_new_init(void **data, size_t size);

void std_vector_delete(struct std_vector *self);

struct std_vector *std_vector_append(struct std_vector *self, void *value);
struct std_vector *std_vector_append_vector(struct std_vector *self, struct std_vector *vector);

size_t std_vector_size(struct std_vector *self);

bool std_vector_isEmpty(struct std_vector *self);

void *std_vector_at(struct std_vector *self, size_t i);

#ifdef __cplusplus
}
#endif
