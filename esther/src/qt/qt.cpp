#if defined(_MSC_VER)
#define __x86_64
#endif

#include <esther.h>

#if defined(_MSC_VER)
#define EXPORT extern "C" __declspec(dllexport)
#elif defined(__GNUC__)
#define EXPORT extern "C" __attribute__((visibility("default")))
#else
#define EXPORT extern "C"
#endif

#include <QApplication>
#include <QMessageBox>

static Mapper *globalMapper;

static Object *applicationClass;
static Object *messageBoxClass;

struct Application {
    Object base;
    int argc;
    QApplication *ptr;
};

#define as_Application(obj) ((Application *) (obj))

#define Application_virtual_mapOnRefs Object_virtual_mapOnRefs
#define Application_virtual_clone Object_virtual_clone_unimplemented

static void Application_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);
    delete as_Application(self)->ptr;
}

OBJECT_VTABLE(Application)

static Object *ApplicationClass_virtual_newInstance(Esther *es, Object *, Object *) {
    Application *instance = reinterpret_cast<Application *>(gc_alloc(sizeof(Application)));
    Object_init(es, &instance->base, TObject, applicationClass);
    instance->ptr = new QApplication(instance->argc, 0);
    *reinterpret_cast<void **>(instance) = &vtable_for_Application;
    return reinterpret_cast<Object *>(instance);
}

CLASS_VTABLE(Application)

struct MessageBox {
    Object base;
    QMessageBox *ptr;
};

#define as_MessageBox(obj) ((MessageBox *) (obj))

#define MessageBox_virtual_mapOnRefs Object_virtual_mapOnRefs
#define MessageBox_virtual_clone Object_virtual_clone_unimplemented

static void MessageBox_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);
    // delete as_MessageBox(self)->ptr;
}

OBJECT_VTABLE(MessageBox)

static Object *MessageBoxClass_virtual_newInstance(Esther *es, Object *, Object *) {
    MessageBox *instance = reinterpret_cast<MessageBox *>(gc_alloc(sizeof(MessageBox)));
    Object_init(es, &instance->base, TObject, messageBoxClass);
    instance->ptr = new QMessageBox;
    instance->ptr->setAttribute(Qt::WA_DeleteOnClose);
    *reinterpret_cast<void **>(instance) = &vtable_for_MessageBox;
    return reinterpret_cast<Object *>(instance);
}

CLASS_VTABLE(MessageBox)

static Object *Application_exec(Esther *es, Object *self) {
    return ValueObject_new_int(es, as_Application(self)->ptr->exec());
}

static Object *MessageBox_show(Esther *es, Object *self) {
    as_MessageBox(self)->ptr->show();
    return es->nullObject;
}

static Object *MessageBox_setTitle(Esther *es, Object *self, Object *str) {
    as_MessageBox(self)->ptr->setWindowTitle(String_c_str(str));
    return es->nullObject;
}

static Object *MessageBox_setText(Esther *es, Object *self, Object *str) {
    as_MessageBox(self)->ptr->setText(String_c_str(str));
    return es->nullObject;
}

static void GlobalMapper_mapOnRefs(Mapper *UNUSED(self), MapFunction f) {
    f(applicationClass);
    f(messageBoxClass);
}

static MapperVTable vtable_for_GlobalMapper = {
    GlobalMapper_mapOnRefs
};

EXPORT void Qt_initialize(Esther *es, Context *context) {
    gc_registerMapper(globalMapper = new Mapper{ &vtable_for_GlobalMapper });

    applicationClass = Class_new(es, string_const("QApplication"), NULL);
    *(void **) applicationClass = &vtable_for_ApplicationClass;

    Class_setMethod_func(applicationClass, Function_new(es, string_const("exec"), (Object * (*) ()) Application_exec, 0));

    Context_setLocal(context, str_to_id(Class_getName(applicationClass)), applicationClass);

    messageBoxClass = Class_new(es, string_const("QMessageBox"), NULL);
    *(void **) messageBoxClass = &vtable_for_MessageBoxClass;

    Class_setMethod_func(messageBoxClass, Function_new(es, string_const("show"), (Object * (*) ()) MessageBox_show, 0));
    Class_setMethod_func(messageBoxClass, Function_new(es, string_const("setTitle"), (Object * (*) ()) MessageBox_setTitle, 1));
    Class_setMethod_func(messageBoxClass, Function_new(es, string_const("setText"), (Object * (*) ()) MessageBox_setText, 1));

    Context_setLocal(context, str_to_id(Class_getName(messageBoxClass)), messageBoxClass);
}

EXPORT void Qt_finalize(Esther *UNUSED(es)) {
    delete globalMapper;
}
