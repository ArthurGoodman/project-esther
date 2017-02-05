#include "esther.h"

#include "runtime/class.h"
#include "exception/runtimeerror.h"
#include "runtime/rootclass/booleanclass.h"
#include "runtime/rootclass/characterclass.h"
#include "runtime/rootclass/floatclass.h"
#include "runtime/rootclass/classclass.h"
#include "runtime/rootclass/functionclass.h"
#include "runtime/rootclass/numericclass.h"
#include "runtime/rootclass/integerclass.h"
#include "runtime/rootclass/nullclass.h"
#include "runtime/rootclass/objectclass.h"
#include "runtime/rootclass/stringclass.h"
#include "runtime/true.h"
#include "runtime/false.h"
#include "runtime/null.h"
#include "runtime/function.h"
#include "runtime/valueobject.h"
#include "runtime/context.h"
#include "common/io.h"
#include "common/utility.h"
#include "parser/iparser.h"
#include "lexer/ilexer.h"
#include "expression/expression.h"
#include "runtime/nativefunction.h"

namespace es {

void Esther::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
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

void Esther::registerRootClass(RootClass *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

Object *Esther::toBoolean(bool value) const {
    return value ? trueObject : falseObject;
}

Object *Esther::createObject() {
    return objectClass->newInstance(this);
}

void Esther::initialize() {
    rootClasses.clear();

    classClass = new ClassClass(this);
    classClass->setClass(classClass);

    objectClass = new ObjectClass(this);
    classClass->setSuperclass(objectClass);

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

    Object *console = createObject();
    mainObject->setAttribute("console", console);

    console->setAttribute("write", new NativeFunction(this, "write", -1, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
                              if (!args.empty())
                                  for (auto &arg : args)
                                      IO::write(arg->call(esther, "toString", {}, esther->getRootClass("String"))->toString());
                              else
                                  IO::write(self->call(esther, "toString", {}, esther->getRootClass("String"))->toString());

                              return esther->getNull();
                          }));

    console->setAttribute("writeLine", new NativeFunction(this, "writeLine", -1, [](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
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
        Object *value = e ? e->eval(this) : nullptr;
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
    return contexts.top();
}

void Esther::pushContext(Context *context) {
    contexts.push(context);
}

void Esther::popContext() {
    contexts.pop();
}

void Esther::push(Object *value) {
    stack.push_back(value);
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

void Esther::setReg(Object *value) {
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
