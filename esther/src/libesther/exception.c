#include "esther/exception.h"

#include "esther/esther.h"
#include "esther/std_string.h"

static struct jump_buffer *buffer = NULL;

void push_jump_buffer(struct jump_buffer *buf) {
    buf->next = buffer;
    buffer = buf;
}

struct jump_buffer *pop_jump_buffer() {
    struct jump_buffer *top = buffer;
    buffer = buffer->next;
    return top;
}

static Object *last_exception = NULL;

Object *get_last_exception() {
    return last_exception;
}

Object *Exception_new(Esther *es, struct string msg) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init(es, self, msg);
    return self;
}

static VTableForObject Exception_vtable = {
    .base = {
        .base = {
            .mapOnReferences = Exception_virtual_mapOnReferences },
        .finalize = Exception_virtual_finalize },
    .toString = Object_virtual_toString,
    .inspect = Object_virtual_toString,
    .equals = Object_virtual_equals,
    .isTrue = Object_virtual_isTrue
};

void Exception_init(Esther *es, Object *self, struct string msg) {
    Object_init(es, self, TException, es->exceptionClass);

    as_Exception(self)->msg = string_copy(msg);
    as_Exception(self)->pos = NULL;

    *(void **) self = &Exception_vtable;
}

struct string Exception_getMessage(Object *self) {
    return as_Exception(self)->msg;
}

Object *Exception_getPos(Object *self) {
    return as_Exception(self)->pos;
}

void Exception_setPos(Object *self, Object *pos) {
    as_Exception(self)->pos = pos;
}

void Exception_throw_new(Esther *es, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    struct string msg = string_vformat(fmt, ap);
    va_end(ap);

    last_exception = Exception_new(es, msg);

    string_free(msg);

    THROW;
}

void Exception_throw(Object *self) {
    last_exception = self;

    THROW;
}

void Exception_virtual_mapOnReferences(Mapper *self, MapFunction f) {
    Object_virtual_mapOnReferences(self, f);

    f(as_Exception(self)->pos);
}

void Exception_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    string_free(as_Exception(self)->msg);
}
