#include "esther/utility.h"

#include "esther/common.h"
#include "esther/std_string.h"

struct std_string *read_file(const char *fileName) {
    FILE *file = fopen(fileName, "rb");

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(size + 1);

    if (fread(data, size, 1, file)) {
    }

    fclose(file);

    data[size] = '\0';

    struct std_string *str = std_string_new_init_len(data, size);

    free(data);

    return str;
}
