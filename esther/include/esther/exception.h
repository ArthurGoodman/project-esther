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

typedef enum ExceptionType {
    ExError,
    ExContinue,
    ExBreak,
    ExReturn
} ExceptionType;

typedef struct Exception {
    Object base;

    ExceptionType type;
    struct string msg;
    union {
        Object *pos;
        Object *value;
    };
} Exception;

#define as_Exception(obj) ((Exception *) (obj))

Object *Exception_new_error(Esther *es, struct string msg);
Object *Exception_new_continue(Esther *es);
Object *Exception_new_break(Esther *es, Object *value);
Object *Exception_new_return(Esther *es, Object *value);

void Exception_init_error(Esther *es, Object *self, struct string msg);
void Exception_init_continue(Esther *es, Object *self);
void Exception_init_break(Esther *es, Object *self, Object *value);
void Exception_init_return(Esther *es, Object *self, Object *value);

ExceptionType Exception_getType(Object *self);

struct string Exception_getMessage(Object *self);

Object *Exception_getPos(Object *self);
void Exception_setPos(Object *self, Object *pos);

Object *Exception_getValue(Object *self);
void Exception_setValue(Object *self, Object *value);

void Exception_throw_new(Esther *es, const char *fmt, ...);
void Exception_throw(Object *self);

void Exception_virtual_mapOnRefs(Mapper *self, MapFunction f);
void Exception_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
