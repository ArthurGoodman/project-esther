#include "esther/exception.h"

#include "esther/esther.h"

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

#define Exception_virtual_clone Object_virtual_clone_unimplemented

OBJECT_VTABLE(Exception)

static void Exception_init(Esther *es, Object *self, ExceptionType type, struct string msg, Object *obj) {
    Object_init(es, self, TException, Esther_getRootObject(es, cstr_to_id("Exception")));

    as_Exception(self)->type = type;
    as_Exception(self)->msg = string_copy(msg);
    as_Exception(self)->pos = obj;

    *(void **) self = &vtable_for_Exception;
}

Object *Exception_new_error(Esther *es, struct string msg) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init(es, self, ExError, msg, NULL);
    return self;
}

Object *Exception_new_continue(Esther *es) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init(es, self, ExContinue, string_const(""), NULL);
    return self;
}

Object *Exception_new_break(Esther *es, Object *value) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init(es, self, ExBreak, string_const(""), value);
    return self;
}

Object *Exception_new_return(Esther *es, Object *value) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init(es, self, ExReturn, string_const(""), value);
    return self;
}

Object *Exception_new_stopIteration(Esther *es) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init(es, self, ExStopIteration, string_const(""), NULL);
    return self;
}

ExceptionType Exception_getType(Object *self) {
    return as_Exception(self)->type;
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

Object *Exception_getValue(Object *self) {
    return as_Exception(self)->value;
}

void Exception_setValue(Object *self, Object *value) {
    as_Exception(self)->value = value;
}

void Exception_throw_new(Esther *es, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    struct string msg = string_vformat(fmt, ap);
    va_end(ap);

    last_exception = Exception_new_error(es, msg);

    string_free(msg);

    THROW;
}

void Exception_throw(Object *self) {
    last_exception = self;

    THROW;
}

void Exception_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    f(as_Exception(self)->value);
}

void Exception_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    string_free(as_Exception(self)->msg);
}
