#include <esther.h>

#include <cstdio>

#include <string>

void dump_string(string str) {
    printf("data = \"%s\"; size = %zi; capacity = %zi\n", str.data, string_size(&str), string_capacity(&str));
}

int main(int argc, const char **argv) {
    // if (argc < 2)
    //     return 0;

    string str0 = string_format("%s, %s!", "Hello", "World");
    string str1 = string_new(str0.data, 5);
    string str2 = string_new_c_str(str0.data);
    string str3 = string_copy(str2);
    string str4 = string_substr(&str3, 5, -1);
    string str5 = string_new_empty();

    dump_string(str1);
    dump_string(str2);
    dump_string(str3);
    dump_string(str4);
    dump_string(str5);

    string_append(&str1, str4);
    string_append(&str5, str1);

    dump_string(str1);
    dump_string(str5);

    string_erase(&str5, 5, 7);
    dump_string(str5);

    string_insert(&str5, 5, str4);
    dump_string(str5);

    string_replace_c_str(&str5, 7, 5, "Arthur");
    dump_string(str5);

    printf("%zi\n", string_find(&str1, str4));

    string_free(&str0);
    string_free(&str1);
    string_free(&str2);
    string_free(&str3);
    string_free(&str4);
    string_free(&str5);

    Esther es;
    Esther_init(&es);

    Esther_runFile(&es, argc < 2 ? "../scripts/script.es" : argv[1]);

    Esther_finalize(&es);

    return 0;
}
