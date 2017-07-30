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

static Object *IO_new(Esther *es, FILE *file) {
    Object *self = gc_alloc(sizeof(struct IO));
    Object_init(es, self, TObject, ioClass);
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

static Object *IO_read(Esther *es, Object *self, Object *arg) {
    size_t size = Variant_toInt(ValueObject_getValue(arg));
    struct string str = string_new_prealloc(size);
    size_t len = fread(str.data, 1, size, as_IO(self)->file);
    str.size = len;
    return String_new_move(es, str);
}

void IO_initialize(Esther *es, Context *context) {
    ioClass = Class_new(es, string_const("IO"), es->objectClass);
    *(void **) ioClass = &vtable_for_IOClass;

    Object_setAttribute(ioClass, string_const("stdout"), IO_new(es, stdout));
    Object_setAttribute(ioClass, string_const("stdin"), IO_new(es, stdin));
    Object_setAttribute(ioClass, string_const("stderr"), IO_new(es, stderr));

    Class_setMethod_func(ioClass, Function_new(es, string_const("write"), (Object * (*) ()) IO_write, 1));
    Class_setMethod_func(ioClass, Function_new(es, string_const("writeLine"), (Object * (*) ()) IO_writeLine, 1));
    Class_setMethod_func(ioClass, Function_new(es, string_const("read"), (Object * (*) ()) IO_read, 1));

    Context_setLocal(context, Class_getName(ioClass), ioClass);
}

void IO_finalize(Esther *UNUSED(es)) {
}
