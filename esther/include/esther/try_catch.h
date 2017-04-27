#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <setjmp.h>

struct jump_buffer {
    jmp_buf buf;
    struct jump_buffer *next;
};

#define TRY(type, exception)        \
    do {                            \
        struct jump_buffer __buf__; \
        type exception;             \
        push_jump_buffer(&__buf__); \
        if (!(exception = setjmp(__buf__.buf))) {

#define CATCH \
    }         \
    else {

#define ENDTRY \
    }          \
    }          \
    while (0)

#define THROW(exception) longjmp(pop_jump_buffer()->buf, (exception))

void push_jump_buffer(struct jump_buffer *buf);
struct jump_buffer *pop_jump_buffer();

#ifdef __cplusplus
}
#endif
