#include "signature.h"

#include "runtime.h"
#include "class.h"
#include "tuple.h"
#include "parameter.h"
#include "utility.h"

Signature::Signature()
    : returnClass(Runtime::getObjectClass()) {
}

Signature::Signature(Class *returnClass, list<Class *> paramsClasses, bool variadic)
    : returnClass(returnClass), variadic(variadic) {
    for (Class *c : paramsClasses)
        params << new Parameter(c, "", 0);
}

Signature::Signature(string returnClassName, list<string> argsClassesNames, bool variadic)
    : returnClass(Runtime::getRootClass(returnClassName)), variadic(variadic) {
    for (string name : argsClassesNames)
        params << new Parameter(Runtime::getRootClass(name), "", 0);
}

Signature::Signature(Class *returnClass, list<Parameter *> params, bool variadic)
    : returnClass(returnClass), params(params), variadic(variadic) {
}

bool Signature::accepts(Tuple *args) {
    if (!variadic && args->size() > (int)params.size())
        return false;

    int c = 0;

    for (Parameter *p : params) {
        if ((c >= args->size() && !p->getValue()) || (c < args->size() && !args->at(c)->converts(p->getType())))
            return false;

        c++;
    }

    return true;
}

void Signature::apply(Tuple *args) {
    if (!variadic && args->size() > (int)params.size())
        Runtime::runtimeError("invalid number of arguments (" + Utility::toString(args->size()) + "/" + Utility::toString(params.size()) + ")");

    int c = 0;

    for (Parameter *p : params) {
        if(c >= args->size() && !p->getValue())
            Runtime::runtimeError("invalid number of arguments (" + Utility::toString(args->size()) + "/" + Utility::toString(params.size()) + ")");

        if(c < args->size() && !args->at(c)->converts(p->getType()))
            Runtime::runtimeError("can't convert argument #" + Utility::toString(c + 1) + " from " + args->at(c)->getClass()->callToString() + " to " + p->getType()->callToString());

        c++;
    }
}

bool Signature::check(Tuple *args) {
    if (!variadic && args->size() > (int)params.size())
        return false;

    int c = 0;

    for (Parameter *p : params) {
        if ((c >= args->size() && !p->getValue()) || (c < args->size() && args->at(c)->getClass() != p->getType()))
            return false;

        c++;
    }

    return true;
}

Tuple *Signature::convert(Tuple *args) {
    Tuple *convertedArgs = new Tuple(variadic ? max((int)params.size(), args->size()) : params.size());

    int c = 0;

    for (Parameter *p : params) {
        if (c >= args->size())
            convertedArgs->at(c) = p->getValue();
        else
            convertedArgs->at(c) = args->at(c)->as(p->getType());

        c++;
    }

    for (; c < args->size(); c++)
        convertedArgs->at(c) = args->at(c);

    return convertedArgs;
}

Object *Signature::convertReturnValue(Object *value) {
    return value->as(returnClass);
}

bool Signature::equals(Signature *other) {
    if (variadic != other->variadic)
        return false;

    if (returnClass != other->returnClass)
        return false;

    return weakEquals(other);
}

bool Signature::weakEquals(Signature *other) {
    if (params.size() != other->params.size())
        return false;

    auto i = other->params.begin();

    for (Parameter *p : params)
        if (!p->equals(*i++))
            return false;

    return true;
}

list<string> Signature::paramsNames() {
    list<string> names;

    for (Parameter *p : params)
        names << p->getName();

    return names;
}

Object *Signature::clone() {
    return new Signature(returnClass, params, variadic);
}
