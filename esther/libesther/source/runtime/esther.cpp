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

Object *Esther::getTrue() const {
    return trueObject;
}

Object *Esther::getFalse() const {
    return falseObject;
}

Object *Esther::getNull() const {
    return nullObject;
}

ClassClass *Esther::getClassClass() const {
    return classClass;
}

NumericClass *Esther::getNumericClass() const {
    return numericClass;
}

StringClass *Esther::getStringClass() const {
    return stringClass;
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

ValueObject *Esther::createValueObject(const Variant &value) {
    switch (value.getType()) {
    case Variant::Integer:
        return createInteger(value.toInteger());

    case Variant::Real:
        return createFloat(value.toReal());

    case Variant::Char:
        return createCharacter(value.toChar());

    case Variant::String:
        return createString(value.toString());

    default:
        return nullptr;
    }
}

ValueObject *Esther::createCharacter(char value) {
    return characterClass->createCharacter(value);
}

ValueObject *Esther::createFloat(double value) {
    return floatClass->createFloat(value);
}

ValueObject *Esther::createInteger(int value) {
    return integerClass->createInteger(value);
}

ValueObject *Esther::createString(const std::string &value) {
    return stringClass->createString(value);
}

Class *Esther::createClass(const std::string &name, Class *superclass) {
    return classClass->createClass(name, superclass);
}

Function *Esther::createNativeFunction(const std::string &name, int arity, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body) {
    return functionClass->createNativeFunction(name, arity, body);
}

Function *Esther::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context) {
    return functionClass->createInterpretedFunction(name, params, body, context);
}

void Esther::initialize() {
    rootClasses.clear();

    classClass = new ClassClass(this);
    classClass->setClass(classClass);

    objectClass = new ObjectClass(this);
    classClass->setSuperclass(objectClass);

    mainObject = createObject();

    BooleanClass *booleanClass = new BooleanClass(this);

    trueObject = new True(booleanClass);
    falseObject = new False(booleanClass);

    NullClass *nullClass = new NullClass(this);

    nullObject = new Null(nullClass);

    numericClass = new NumericClass(this);

    characterClass = new CharacterClass(this);
    floatClass = new FloatClass(this);
    integerClass = new IntegerClass(this);
    stringClass = new StringClass(this);

    functionClass = new FunctionClass(this);

    setupMethods();

    Object *console = createObject();
    mainObject->setAttribute("console", console);

    console->setAttribute("write", createNativeFunction("write", -1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
                              if (!args.empty())
                                  for (Object *arg : args)
                                      IO::write(arg->call(esther, "toString", {}, getStringClass())->toString());
                              else
                                  IO::write(self->call(esther, "toString", {}, getStringClass())->toString());

                              return getNull();
                          }));

    console->setAttribute("writeLine", createNativeFunction("writeLine", -1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
                              if (!args.empty())
                                  for (Object *arg : args)
                                      IO::writeLine(arg->call(esther, "toString", {}, getStringClass())->toString());
                              else
                                  IO::writeLine(self->call(esther, "toString", {}, getStringClass())->toString());

                              return getNull();
                          }));

    pushContext(new Context(this));
}

void Esther::release() {
}

void Esther::setupMethods() {
    for (auto &rootClass : rootClasses)
        rootClass.second->setupMethods(this);
}

Object *Esther::run(const std::string &script) {
    Object *value = 0;

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

Object *Esther::runFile(const std::string &fileName) {
    pushFileName(IO::fullPath(fileName));

    Object *value = run(IO::readFile(fileName));

    popFileName();

    return value;
}

Context *Esther::context() const {
    return contexts.top();
}

void Esther::pushContext(Object *self, Object *here) {
    pushContext(context()->childContext(self, here));
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
