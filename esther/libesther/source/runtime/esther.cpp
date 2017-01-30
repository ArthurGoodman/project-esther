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

Pointer<Object> Esther::getMainObject() const {
    return mainObject;
}

Pointer<Class> Esther::getObjectClass() const {
    return *objectClass;
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

Pointer<ClassClass> Esther::getClassClass() const {
    return classClass;
}

Pointer<NumericClass> Esther::getNumericClass() const {
    return numericClass;
}

Pointer<StringClass> Esther::getStringClass() const {
    return stringClass;
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

Pointer<ValueObject> Esther::createValueObject(const Variant &value) {
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

Pointer<ValueObject> Esther::createCharacter(char value) {
    return characterClass->createCharacter(value);
}

Pointer<ValueObject> Esther::createFloat(double value) {
    return floatClass->createFloat(value);
}

Pointer<ValueObject> Esther::createInteger(int value) {
    return integerClass->createInteger(value);
}

Pointer<ValueObject> Esther::createString(const std::string &value) {
    return stringClass->createString(value);
}

Pointer<Class> Esther::createClass(const std::string &name, Pointer<Class> superclass) {
    return classClass->createClass(name, superclass);
}

Pointer<Function> Esther::createNativeFunction(const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body) {
    return functionClass->createNativeFunction(name, arity, body);
}

Pointer<Function> Esther::createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context) {
    return functionClass->createInterpretedFunction(name, params, body, context);
}

void Esther::initialize() {
    rootClasses.clear();

    classClass = new ClassClass(this);
    classClass->setClass(*classClass);

    objectClass = new ObjectClass(this);
    classClass->setSuperclass(*objectClass);

    mainObject = createObject();

    Pointer<BooleanClass> booleanClass = new BooleanClass(this);

    trueObject = new True(*booleanClass);
    falseObject = new False(*booleanClass);

    Pointer<NullClass> nullClass = new NullClass(this);

    nullObject = new Null(*nullClass);

    numericClass = new NumericClass(this);

    characterClass = new CharacterClass(this);
    floatClass = new FloatClass(this);
    integerClass = new IntegerClass(this);
    stringClass = new StringClass(this);

    functionClass = new FunctionClass(this);

    setupMethods();

    Pointer<Object> console = createObject();
    mainObject->setAttribute("console", console);

    console->setAttribute("write", *createNativeFunction("write", -1, [=](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
                              if (!args.empty())
                                  for (auto &arg : args)
                                      IO::write(arg->call(esther, "toString", {}, *getStringClass())->toString());
                              else
                                  IO::write(self->call(esther, "toString", {}, *getStringClass())->toString());

                              return getNull();
                          }));

    console->setAttribute("writeLine", *createNativeFunction("writeLine", -1, [=](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
                              if (!args.empty())
                                  for (auto &arg : args)
                                      IO::writeLine(arg->call(esther, "toString", {}, *getStringClass())->toString());
                              else
                                  IO::writeLine(self->call(esther, "toString", {}, *getStringClass())->toString());

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

void Esther::pushContext(Pointer<Object> self, Pointer<Object> here) {
    pushContext(context()->childContext(self, here));
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
