#include "esther.h"

#include <cstdarg>

#include "common/config.h"
#include "common/io.h"
#include "common/utility.h"
#include "exception/runtimeerror.h"
#include "expression/expression.h"
#include "lexer/ilexer.h"
#include "memory/memorymanager.h"
#include "parser/iparser.h"
#include "runtime/class.h"
#include "runtime/context.h"
#include "runtime/false.h"
#include "runtime/function.h"
#include "runtime/nativefunction.h"
#include "runtime/null.h"
#include "runtime/rootclass/booleanclass.h"
#include "runtime/rootclass/characterclass.h"
#include "runtime/rootclass/classclass.h"
#include "runtime/rootclass/floatclass.h"
#include "runtime/rootclass/functionclass.h"
#include "runtime/rootclass/integerclass.h"
#include "runtime/rootclass/nullclass.h"
#include "runtime/rootclass/numericclass.h"
#include "runtime/rootclass/objectclass.h"
#include "runtime/rootclass/stringclass.h"
#include "runtime/true.h"
#include "runtime/valueobject.h"

namespace es {

void Esther::runtimeError(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    throw new RuntimeError(Utility::vformat(fmt, ap));
    va_end(ap);
}

Esther::Esther() {
    initialize();
}

Esther::~Esther() {
    release();
}

Object *Esther::getMainObject() const {
    return mainObject;
}

Class *Esther::getObjectClass() const {
    return objectClass;
}

ClassClass *Esther::getClassClass() const {
    return classClass;
}

Object *Esther::getTrue() const {
    return trueObject;
}

Object *Esther::getFalse() const {
    return falseObject;
}

Object *Esther::getNull() const {
    return nullObject;
}

bool Esther::hasRootClass(const std::string &name) const {
    return rootClasses.find(name) != rootClasses.end();
}

Class *Esther::getRootClass(const std::string &name) const {
    return rootClasses.at(name);
}

void Esther::registerRootClass(RootClass *volatile rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

Object *Esther::toBoolean(bool value) const {
    return value ? trueObject : falseObject;
}

Object *Esther::createObject() {
    return objectClass->newInstance(this);
}

void Esther::initialize() {
#ifdef CONSERVATIVE_GC
#ifdef __x86_64
    register ptr_ptr_t bp asm("rbp");
#elif __i386
    register ptr_ptr_t bp asm("ebp");
#endif

    ConservativeMemoryManager::initStack(bp);
#endif

    class GlobalMapper : public Mapper {
        Esther *esther;

    public:
        GlobalMapper(Esther *esther)
            : esther(esther) {
        }

        void mapOnReferences(void (*f)(es::ManagedObject *&)) override {
            f(reinterpret_cast<ManagedObject *&>(esther->mainObject));
            f(reinterpret_cast<ManagedObject *&>(esther->objectClass));

            f(reinterpret_cast<ManagedObject *&>(esther->trueObject));
            f(reinterpret_cast<ManagedObject *&>(esther->falseObject));
            f(reinterpret_cast<ManagedObject *&>(esther->nullObject));

            f(reinterpret_cast<ManagedObject *&>(esther->booleanClass));
            f(reinterpret_cast<ManagedObject *&>(esther->nullClass));

            f(reinterpret_cast<ManagedObject *&>(esther->numericClass));
            f(reinterpret_cast<ManagedObject *&>(esther->characterClass));
            f(reinterpret_cast<ManagedObject *&>(esther->floatClass));
            f(reinterpret_cast<ManagedObject *&>(esther->integerClass));
            f(reinterpret_cast<ManagedObject *&>(esther->stringClass));

            f(reinterpret_cast<ManagedObject *&>(esther->classClass));
            f(reinterpret_cast<ManagedObject *&>(esther->functionClass));

            for (Context *context : esther->contexts)
                context->mapOnReferences(f);

            for (Object *object : esther->stack)
                f(reinterpret_cast<ManagedObject *&>(object));

            f(reinterpret_cast<ManagedObject *&>(esther->reg));
        }
    };

    MemoryManager::registerMapper(new GlobalMapper(this));

    rootClasses.clear();

    classClass = new ClassClass(this);
    classClass->setClass(classClass);

    objectClass = new ObjectClass(this);
    classClass->setSuperclass(objectClass);

    mainObject = createObject();

    booleanClass = new BooleanClass(this);

    trueObject = new True(this);
    falseObject = new False(this);

    nullClass = new NullClass(this);

    nullObject = new Null(this);

    numericClass = new NumericClass(this);

    characterClass = new CharacterClass(this);
    floatClass = new FloatClass(this);
    integerClass = new IntegerClass(this);
    stringClass = new StringClass(this);

    functionClass = new FunctionClass(this);

    setupMethods();

    Object *volatile console = createObject();
    mainObject->setAttribute("console", console);

    console->setAttribute("write", new NativeFunction(this, "write", -1, [](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
                              if (!args.empty())
                                  for (auto &arg : args)
                                      IO::write(arg->call(esther, "toString", {}, esther->getRootClass("String"))->toString());
                              else
                                  IO::write(self->call(esther, "toString", {}, esther->getRootClass("String"))->toString());

                              return esther->getNull();
                          }));

    console->setAttribute("writeLine", new NativeFunction(this, "writeLine", -1, [](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
                              if (!args.empty())
                                  for (auto &arg : args)
                                      IO::writeLine(arg->call(esther, "toString", {}, esther->getRootClass("String"))->toString());
                              else
                                  IO::writeLine(self->call(esther, "toString", {}, esther->getRootClass("String"))->toString());

                              return esther->getNull();
                          }));

    pushContext(new Context(this));
}

void Esther::release() {
}

void Esther::setupMethods() {
    for (auto &rootClass : rootClasses)
        rootClass.second->setupMethods(this);
}

void Esther::run(const std::string &script) {
    std::string src = Utility::expandTabs(script);

    pushSource(src);

    try {
        Expression *e = IParser::instance()->parse(this, ILexer::instance()->lex(src));
        Object *volatile value = e ? e->eval(this) : nullptr;
        if (value)
            IO::writeLine("=> %s", value->call(this, "toString", {}, getRootClass("String"))->toString().c_str());
        delete e;
    } catch (ErrorException *e) {
        IO::writeLine("%s:%s %s", fileName().c_str(), (e->getPosition().isValid() ? e->getPosition().toString() + ":" : "").c_str(), e->message().c_str());
        if (e->getPosition().isValid())
            IO::writeLine(source().quote(e->getPosition()));
        delete e;
    } catch (Exception *e) {
        IO::writeLine(e->message());
        delete e;
    } catch (std::exception e) {
        IO::writeLine("error: %s", e.what());
    } catch (...) {
        IO::writeLine("something bad happened...");
    }

    popSource();
}

void Esther::runFile(const std::string &fileName) {
    pushFileName(IO::fullPath(fileName));
    run(IO::readFile(fileName));
    popFileName();
}

Context *Esther::context() const {
    return contexts.back();
}

void Esther::pushContext(Context *context) {
    contexts.push_back(static_cast<Context *>(context));
}

void Esther::popContext() {
    contexts.pop_back();
}

void Esther::push(Object *volatile value) {
    stack.push_back(static_cast<Object *>(value));
}

void Esther::pop(int count) {
    stack.erase(stack.end() - count, stack.end());
}

Object *Esther::top(int index) {
    return stack[stack.size() - 1 - index];
}

Object *Esther::getReg() const {
    return reg;
}

void Esther::setReg(Object *volatile value) {
    reg = value;
}

void Esther::pushSource(const std::string &source) {
    sources.push(Source(source));
}

void Esther::popSource() {
    if (!sources.empty())
        sources.pop();
}

void Esther::pushFileName(const std::string &fileName) {
    fileNames.push(fileName);
}

void Esther::popFileName() {
    if (!fileNames.empty())
        fileNames.pop();
}

const Source &Esther::source() {
    return sources.top();
}

const std::string &Esther::fileName() {
    return fileNames.top();
}
}
