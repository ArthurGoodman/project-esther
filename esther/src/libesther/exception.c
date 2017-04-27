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
    Object *self = malloc(sizeof(Exception));
    Exception_init(es, self, msg);
    return self;
}

void Exception_init(Esther *es, Object *self, const char *msg) {
    Object_init(es, self, es->exceptionClass);

    as_Exception(self)->msg = strdup(msg);
}

const char *Exception_getMessage(Object *self) {
    return as_Exception(self)->msg;
}

void Exception_throw(Esther *es, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    struct std_string *msg = std_string_format_va(fmt, ap);
    va_end(ap);

    last_exception = Exception_new(es, std_string_c_str(msg));

    std_string_delete(msg);

    THROW;
}
