#include "esther/std_vector.h"

#include <vector>

namespace {
inline struct std_vector *to_c(std::vector<void *> *ptr) {
    return reinterpret_cast<struct std_vector *>(ptr);
}

inline std::vector<void *> *to_cpp(struct std_vector *ptr) {
    return reinterpret_cast<std::vector<void *> *>(ptr);
}
}

struct std_vector *std_vector_new() {
    return to_c(new std::vector<void *>);
}

struct std_vector *std_vector_new_init(void **data, size_t size) {
    return to_c(new std::vector<void *>(data, data + size));
}

void std_vector_delete(struct std_vector *self) {
    delete to_cpp(self);
}

struct std_vector *std_vector_append(struct std_vector *self, void *value) {
    to_cpp(self)->push_back(value);
    return self;
}

struct std_vector *std_vector_append_vector(struct std_vector *self, struct std_vector *vector) {
    to_cpp(self)->insert(to_cpp(self)->end(), to_cpp(vector)->begin(), to_cpp(vector)->end());
    return self;
}

size_t std_vector_size(struct std_vector *self) {
    return to_cpp(self)->size();
}

bool std_vector_isEmpty(struct std_vector *self) {
    return to_cpp(self)->empty();
}

void *std_vector_at(struct std_vector *self, size_t i) {
    return to_cpp(self)->at(i);
}
