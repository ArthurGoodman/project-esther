#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"
#include "esther/std_string.h"

struct jump_buffer {
    jmp_buf buf;
    struct jump_buffer *next;
};

#define TRY                         \
    do {                            \
        struct jump_buffer __buf__; \
        push_jump_buffer(&__buf__); \
        if (!setjmp(__buf__.buf)) {

#define CATCH(exception) \
    pop_jump_buffer();   \
    }                    \
    else {               \
        Object *exception = get_last_exception();

#define ENDTRY \
    }          \
    }          \
    while (0)

#define THROW longjmp(pop_jump_buffer()->buf, 1)

void push_jump_buffer(struct jump_buffer *buf);
struct jump_buffer *pop_jump_buffer();

Object *get_last_exception();

typedef struct Exception {
    Object base;

    struct string msg;
    Object *pos;
} Exception;

#define as_Exception(obj) ((Exception *) (obj))

Object *Exception_new(Esther *es, struct string msg);

void Exception_init(Esther *es, Object *self, struct string msg);

struct string Exception_getMessage(Object *self);

Object *Exception_getPos(Object *self);
void Exception_setPos(Object *self, Object *pos);

void Exception_throw_new(Esther *es, const char *fmt, ...);
void Exception_throw(Object *self);

void Exception_virtual_mapOnReferences(Mapper *self, MapFunction f);
void Exception_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
