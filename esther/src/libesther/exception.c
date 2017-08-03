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

Object *Exception_new_error(Esther *es, struct string msg) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init_error(es, self, msg);
    return self;
}

Object *Exception_new_continue(Esther *es) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init_continue(es, self);
    return self;
}

Object *Exception_new_break(Esther *es, Object *value) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init_break(es, self, value);
    return self;
}

Object *Exception_new_return(Esther *es, Object *value) {
    Object *self = gc_alloc(sizeof(Exception));
    Exception_init_return(es, self, value);
    return self;
}

static ObjectVTable vtable_for_Exception = {
    .base = {
        .base = {
            .mapOnRefs = Exception_virtual_mapOnRefs },
        .finalize = Exception_virtual_finalize },
    .toString = Object_virtual_toString,
    .inspect = Object_virtual_toString,
    .equals = Object_virtual_equals,
    .less = Object_virtual_less,
    .isTrue = Object_virtual_isTrue,
    .clone = Object_virtual_clone_unimplemented
};

static void Exception_init(Esther *es, Object *self, ExceptionType type, struct string msg, Object *obj) {
    Object_init(es, self, TException, Esther_getRootObject(es, c_str_to_id("Exception")));

    as_Exception(self)->type = type;
    as_Exception(self)->msg = string_copy(msg);
    as_Exception(self)->pos = obj;

    *(void **) self = &vtable_for_Exception;
}

void Exception_init_error(Esther *es, Object *self, struct string msg) {
    Exception_init(es, self, ExError, msg, NULL);
}

void Exception_init_continue(Esther *es, Object *self) {
    Exception_init(es, self, ExContinue, string_new_empty(), NULL);
}

void Exception_init_break(Esther *es, Object *self, Object *value) {
    Exception_init(es, self, ExBreak, string_new_empty(), value);
}

void Exception_init_return(Esther *es, Object *self, Object *value) {
    Exception_init(es, self, ExReturn, string_new_empty(), value);
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
