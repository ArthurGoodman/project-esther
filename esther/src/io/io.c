#include <esther.h>

struct IO {
    Object base;
    FILE *file;
};

#define as_IO(obj) ((struct IO *) (obj))

#define IOClass_virtual_newInstance Class_virtual_unimplemented_newInstance

#define IO_virtual_mapOnRefs Object_virtual_mapOnRefs

static void IO_virtual_finalize(ManagedObject *self) {
    fclose(as_IO(self)->file);
}

CLASS_VTABLE(IO)
OBJECT_VTABLE(IO)

static Object *ioClass;
static Object *fileClass;

static Object *IO_new(Esther *es, FILE *file, Object *objectClass) {
    Object *self = gc_alloc(sizeof(struct IO));
    Object_init(es, self, TObject, objectClass);
    as_IO(self)->file = file;
    *(void **) self = &vtable_for_IO;
    return self;
}

static Object *IO_write(Esther *es, Object *self, Object *arg) {
    Object *str = Object_toString(es, arg);
    size_t len = fwrite(String_c_str(str), 1, String_size(str), as_IO(self)->file);
    return ValueObject_new_int(es, len);
}

static Object *IO_writeLine(Esther *es, Object *self, Object *arg) {
    Object *str = Object_toString(es, arg);
    String_append_char(str, '\n');
    return IO_write(es, self, str);
}

static Object *IO_read(Esther *es, Object *self, Object *args) {
    struct string str;

    size_t argc = Tuple_size(args);

    if (argc == 0) {
        str = string_new_empty();
        char buffer[1024];
        while (true) {
            size_t n = fread(buffer, 1, sizeof(buffer), as_IO(self)->file);
            string_append_buffer(&str, buffer, n);
            if (n < sizeof(buffer))
                break;
        }
    } else if (argc == 1) {
        size_t size = Variant_toInt(ValueObject_getValue(Tuple_get(args, 0)));
        str = string_new_prealloc(size);
        size_t len = fread(str.data, 1, size, as_IO(self)->file);
        str.size = len;
    } else
        Exception_throw_new(es, "invalid number of arguments");

    return String_new_move(es, str);
}

static Object *IO_readLine(Esther *es, Object *self) {
    struct string str = string_new_prealloc(128);
    char *buffer = str.data;
    size_t size = str.capacity;

    memset(buffer, '\n', size);

    while (true) {
        fgets(buffer, size, as_IO(self)->file);

        char *c = memchr(buffer, '\n', size);

        if (c == NULL) {
            size_t oldSize = str.capacity - 1;

            string_resize(&str, str.capacity * 2);
            buffer = str.data + oldSize;
            size = str.data + str.capacity - buffer;

            memset(buffer, '\n', size);
        } else {
            if (c == buffer + size || *(c + 1) == '\n') {
                str.size = c - str.data;

                if (str.size > 0)
                    str.size--;
                else {
                    str.data[0] = '\0';
                }
            } else
                str.size = c - str.data + 1;

            return String_new_move(es, str);
        }
    }
}

static Object *IO_readLines(Esther *es, Object *self) {
    Object *lines = Array_new(es, 0);

    while (true) {
        Object *line = IO_readLine(es, self);

        if (String_size(line) == 0)
            break;

        Array_push(lines, line);
    }

    return lines;
}

static Object *IO_readChar(Esther *es, Object *self) {
    char value;
    fscanf(as_IO(self)->file, "%c", &value);
    return ValueObject_new_char(es, value);
}

static Object *IO_readInt(Esther *es, Object *self) {
    int value;
    fscanf(as_IO(self)->file, "%i", &value);
    return ValueObject_new_int(es, value);
}

static Object *IO_readFloat(Esther *es, Object *self) {
    double value;
    fscanf(as_IO(self)->file, "%lf", &value);
    return ValueObject_new_real(es, value);
}

static Object *IO_flush(Esther *es, Object *self) {
    fflush(as_IO(self)->file);
    return es->nullObject;
}

static Object *IO_close(Esther *es, Object *self) {
    fclose(as_IO(self)->file);
    return es->nullObject;
}

static Object *FileClass_open(Esther *es, Object *UNUSED(self), Object *fileName, Object *mode) {
    return IO_new(es, fopen(String_c_str(fileName), String_c_str(mode)), fileClass);
}

void IO_initialize(Esther *es, Context *context) {
    ioClass = Class_new(es, string_const("IO"), NULL);
    *(void **) ioClass = &vtable_for_IOClass;

    Object_setAttribute(ioClass, string_const("stdout"), IO_new(es, stdout, ioClass));
    Object_setAttribute(ioClass, string_const("stdin"), IO_new(es, stdin, ioClass));
    Object_setAttribute(ioClass, string_const("stderr"), IO_new(es, stderr, ioClass));

    Class_setMethod_func(ioClass, Function_new(es, string_const("write"), (Object * (*) ()) IO_write, 1));
    Class_setMethod_func(ioClass, Function_new(es, string_const("writeLine"), (Object * (*) ()) IO_writeLine, 1));
    Class_setMethod_func(ioClass, Function_new(es, string_const("read"), (Object * (*) ()) IO_read, -1));
    Class_setMethod_func(ioClass, Function_new(es, string_const("readLine"), (Object * (*) ()) IO_readLine, 0));
    Class_setMethod_func(ioClass, Function_new(es, string_const("readLines"), (Object * (*) ()) IO_readLines, 0));
    Class_setMethod_func(ioClass, Function_new(es, string_const("readChar"), (Object * (*) ()) IO_readChar, 0));
    Class_setMethod_func(ioClass, Function_new(es, string_const("readInt"), (Object * (*) ()) IO_readInt, 0));
    Class_setMethod_func(ioClass, Function_new(es, string_const("readFloat"), (Object * (*) ()) IO_readFloat, 0));
    Class_setMethod_func(ioClass, Function_new(es, string_const("flush"), (Object * (*) ()) IO_flush, 0));
    Class_setMethod_func(ioClass, Function_new(es, string_const("close"), (Object * (*) ()) IO_close, 0));

    Context_setLocal(context, Class_getName(ioClass), ioClass);

    fileClass = Class_new(es, string_const("File"), ioClass);
    *(void **) fileClass = &vtable_for_IOClass;

    Object_setAttribute(fileClass, string_const("open"), Function_new(es, string_const("open"), (Object * (*) ()) FileClass_open, 2));

    Context_setLocal(context, Class_getName(fileClass), fileClass);
}

void IO_finalize(Esther *UNUSED(es)) {
}
