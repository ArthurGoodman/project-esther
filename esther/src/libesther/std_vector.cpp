#include "esther/std_vector.h"

#include <vector>

namespace {
typedef std::vector<void *> cpp_vector;

inline std_vector *to_c(cpp_vector *ptr) {
    return reinterpret_cast<std_vector *>(ptr);
}

inline cpp_vector *to_cpp(std_vector *ptr) {
    return reinterpret_cast<cpp_vector *>(ptr);
}
}

std_vector *std_vector_new() {
    return to_c(new cpp_vector);
}

std_vector *std_vector_new_init(void *const *data, size_t size) {
    return to_c(new cpp_vector(data, data + size));
}

void std_vector_delete(std_vector *self) {
    delete to_cpp(self);
}

void std_vector_resize(std_vector *self, size_t size) {
    to_cpp(self)->resize(size);
}

std_vector *std_vector_append(std_vector *self, std_vector *vector) {
    to_cpp(self)->insert(to_cpp(self)->end(), to_cpp(vector)->begin(), to_cpp(vector)->end());
    return self;
}

void std_vector_push(std_vector *self, void *value) {
    to_cpp(self)->push_back(value);
}

void *std_vector_pop(std_vector *self) {
    void *value = to_cpp(self)->back();
    to_cpp(self)->pop_back();
    return value;
}

size_t std_vector_size(std_vector *self) {
    return to_cpp(self)->size();
}

bool std_vector_isEmpty(std_vector *self) {
    return to_cpp(self)->empty();
}

void *std_vector_at(std_vector *self, size_t index) {
    return to_cpp(self)->at(index);
}

void std_vector_set(std_vector *self, size_t index, void *value) {
    (*to_cpp(self))[index] = value;
}
