#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct std_vector;

struct std_vector *std_vector_new();
struct std_vector *std_vector_new_init(void *const *data, size_t size);

void std_vector_delete(struct std_vector *self);

struct std_vector *std_vector_append(struct std_vector *self, struct std_vector *vector);

void std_vector_push(struct std_vector *self, void *value);
void *std_vector_pop(struct std_vector *self);

size_t std_vector_size(struct std_vector *self);

bool std_vector_isEmpty(struct std_vector *self);

void *std_vector_at(struct std_vector *self, size_t index);

void std_vector_set(struct std_vector *self, size_t index, void *value);

#ifdef __cplusplus
}
#endif
