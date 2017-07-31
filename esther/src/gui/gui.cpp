#if defined(_WIN64)
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

#if defined(_WIN64)
#undef CLASS_VTABLE
#define CLASS_VTABLE(name)                          \
    static ClassVTable vtable_for_##name##Class = { \
        { { { Class_virtual_mapOnRefs },            \
            Class_virtual_finalize },               \
          Class_virtual_toString,                   \
          Class_virtual_toString,                   \
          Object_virtual_equals,                    \
          Object_virtual_less,                      \
          Object_virtual_isTrue },                  \
        name##Class_virtual_newInstance             \
    };

#undef OBJECT_VTABLE
#define OBJECT_VTABLE(name)                   \
    static ObjectVTable vtable_for_##name = { \
        { { name##_virtual_mapOnRefs },       \
          name##_virtual_finalize },          \
        Object_virtual_toString,              \
        Object_virtual_toString,              \
        Object_virtual_equals,                \
        Object_virtual_less,                  \
        Object_virtual_isTrue                 \
    };
#endif

#include <QApplication>
#include <QMessageBox>

static Object *applicationClass;
static Object *messageBoxClass;

struct Application {
    Object base;
    int argc;
    QApplication *ptr;
};

#define as_Application(obj) ((Application *) (obj))

#define Application_virtual_mapOnRefs Object_virtual_mapOnRefs

static void Application_virtual_finalize(ManagedObject *self) {
    delete as_Application(self)->ptr;
}

OBJECT_VTABLE(Application)

static Object *ApplicationClass_virtual_newInstance(Esther *es, Object *, Object *) {
    Application *instance = new Application;
    Object_init(es, &instance->base, TObject, messageBoxClass);
    instance->ptr = new QApplication(instance->argc, 0);
    //*reinterpret_cast<void **>(instance) = &vtable_for_Application;
    return reinterpret_cast<Object *>(instance);
}

CLASS_VTABLE(Application)

struct MessageBox {
    Object base;
    QMessageBox *ptr;
};

#define as_MessageBox(obj) ((MessageBox *) (obj))

#define MessageBox_virtual_mapOnRefs Object_virtual_mapOnRefs

static void MessageBox_virtual_finalize(ManagedObject *self) {
    delete as_MessageBox(self)->ptr;
}

OBJECT_VTABLE(MessageBox)

static Object *MessageBoxClass_virtual_newInstance(Esther *es, Object *, Object *) {
    MessageBox *instance = new MessageBox;
    Object_init(es, &instance->base, TObject, messageBoxClass);
    instance->ptr = new QMessageBox;
    //*reinterpret_cast<void **>(instance) = &vtable_for_MessageBox;
    return reinterpret_cast<Object *>(instance);
}

CLASS_VTABLE(MessageBox)

EXPORT void GUI_initialize(Esther *es, Context *context) {
    int argc = 0;
    char **argv = 0;

    QApplication app(argc, argv);

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("GUI_initialize");
    msgBox.show();

    app.exec();
}

EXPORT void GUI_finalize(Esther *es) {
}
