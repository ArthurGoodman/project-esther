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

Object *Exception_new(Esther *es, const char *msg) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init(es, self, msg);
    return self;
}

void Exception_init(Esther *es, Object *self, const char *msg) {
    Object_init(es, self, TException, es->exceptionClass);

    as_Exception(self)->msg = strdup(msg);
    as_Exception(self)->pos = NULL;

    self->base.base.mapOnReferences = Exception_virtual_mapOnReferences;
    self->base.finalize = Exception_virtual_finalize;
}

const char *Exception_getMessage(Object *self) {
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
    struct std_string *msg = std_string_format_va(fmt, ap);
    va_end(ap);

    last_exception = Exception_new(es, std_string_c_str(msg));

    std_string_delete(msg);

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

    free((void *) as_Exception(self)->msg);
}
