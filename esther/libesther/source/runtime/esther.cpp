#include "esther.h"

#include "class.h"
#include "runtimeerror.h"
#include "booleanclass.h"
#include "characterclass.h"
#include "floatclass.h"
#include "classclass.h"
#include "functionclass.h"
#include "numericclass.h"
#include "integerclass.h"
#include "nullclass.h"
#include "objectclass.h"
#include "stringclass.h"
#include "true.h"
#include "false.h"
#include "null.h"
#include "function.h"
#include "valueobject.h"
#include "context.h"
#include "io.h"
#include "utility.h"
#include "iparser.h"
#include "ilexer.h"
#include "expression.h"
#include "nativefunction.h"

void Esther::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
}

Esther::Esther() {
    initialize();
}

Esther::~Esther() {
    release();
}

Pointer<Object> Esther::getMainObject() const {
    return mainObject;
}

Pointer<Class> Esther::getObjectClass() const {
    return *objectClass;
}

Pointer<ClassClass> Esther::getClassClass() const {
    return classClass;
}

Pointer<Object> Esther::getTrue() const {
    return trueObject;
}

Pointer<Object> Esther::getFalse() const {
    return falseObject;
}

Pointer<Object> Esther::getNull() const {
    return nullObject;
}

bool Esther::hasRootClass(const std::string &name) const {
    return rootClasses.find(name) != rootClasses.end();
}

Pointer<Class> Esther::getRootClass(const std::string &name) const {
    return *rootClasses.at(name);
}

void Esther::registerRootClass(Pointer<RootClass> rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

Pointer<Object> Esther::toBoolean(bool value) const {
    return value ? trueObject : falseObject;
}

Pointer<Object> Esther::createObject() {
    return objectClass->newInstance(this);
}

void Esther::initialize() {
    rootClasses.clear();

    classClass = new ClassClass(this);
    classClass->setClass(*classClass);

    objectClass = new ObjectClass(this);
    classClass->setSuperclass(*objectClass);

    mainObject = createObject();

    new BooleanClass(this);

    trueObject = new True(this);
    falseObject = new False(this);

    new NullClass(this);

    nullObject = new Null(this);

    numericClass = new NumericClass(this);

    characterClass = new CharacterClass(this);
    floatClass = new FloatClass(this);
    integerClass = new IntegerClass(this);
    stringClass = new StringClass(this);

    functionClass = new FunctionClass(this);

    setupMethods();

    Pointer<Object> console = createObject();
    mainObject->setAttribute("console", console);

    console->setAttribute("write", new NativeFunction(this, "write", -1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
                              if (!args.empty())
                                  for (auto &arg : args)
                                      IO::write(arg->call(esther, "toString", {}, esther->getRootClass("String"))->toString());
                              else
                                  IO::write(self->call(esther, "toString", {}, esther->getRootClass("String"))->toString());

                              return esther->getNull();
                          }));

    console->setAttribute("writeLine", new NativeFunction(this, "writeLine", -1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
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

Pointer<Object> Esther::run(const std::string &script) {
    Pointer<Object> value = 0;

    std::string src = Utility::expandTabs(script);

    pushSource(src);

    try {
        Expression *e = IParser::instance()->parse(this, ILexer::instance()->lex(src));
        value = e ? e->eval(this) : nullptr;
        delete e;
    } catch (ErrorException *e) {
        IO::writeLine(fileName() + ":" + (e->getPosition().isValid() ? e->getPosition().toString() + ": " : " ") + e->message());
        if (e->getPosition().isValid())
            IO::writeLine(source().quote(e->getPosition()));
        delete e;
    } catch (Exception *e) {
        IO::writeLine(e->message());
        delete e;
    } catch (std::exception e) {
        IO::writeLine((std::string) "error: " + e.what());
    } catch (...) {
        IO::writeLine("something bad happened...");
    }

    popSource();

    return value;
}

Pointer<Object> Esther::runFile(const std::string &fileName) {
    pushFileName(IO::fullPath(fileName));

    Pointer<Object> value = run(IO::readFile(fileName));

    popFileName();

    return value;
}

Pointer<Context> Esther::context() const {
    return contexts.top();
}

void Esther::pushContext(Pointer<Context> context) {
    contexts.push(context);
}

void Esther::popContext() {
    contexts.pop();
}

void Esther::push(Pointer<Object> value) {
    stack.push_back(value);
}

void Esther::pop(int count) {
    stack.erase(stack.end() - count, stack.end());
}

Pointer<Object> Esther::top(int index) {
    return stack[stack.size() - 1 - index];
}

Pointer<Object> Esther::getReg() const {
    return reg;
}

void Esther::setReg(Pointer<Object> value) {
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
