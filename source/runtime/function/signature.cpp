#include "signature.h"

#include "runtime.h"
#include "class.h"
#include "tuple.h"
#include "parameter.h"

Signature::Signature()
    : returnClass(Runtime::getObjectClass()) {
}

Signature::Signature(Class *returnClass, list<Class *> paramsClasses)
    : returnClass(returnClass) {
    foreach (i, paramsClasses)
        params << new Parameter(*i, "", 0);
}

Signature::Signature(string returnClassName, list<string> argsClassesNames)
    : returnClass(Runtime::getRootClass(returnClassName)) {
    foreach (i, argsClassesNames)
        params << new Parameter(Runtime::getRootClass(*i), "", 0);
}

Signature::Signature(Class *returnClass, list<Parameter *> params)
    : returnClass(returnClass), params(params) {
}

bool Signature::accepts(Tuple *args) {
    if (args->size() > (int)params.size())
        return false;

    int c = 0;

    foreach (i, params) {
        if ((c >= args->size() && !(*i)->getValue()) || (c < args->size() && !args->at(c)->converts((*i)->getType())))
            return false;

        c++;
    }

    return true;
}

bool Signature::check(Tuple *args) {
    if (args->size() > (int)params.size())
        return false;

    int c = 0;

    foreach (i, params) {
        if ((c >= args->size() && !(*i)->getValue()) || (c < args->size() && !args->at(c)->converts((*i)->getType())))
            return false;

        c++;
    }

    return true;
}

Tuple *Signature::convert(Tuple *args) {
    Tuple *convertedArgs = new Tuple(params.size());

    int c = 0;

    foreach (i, params) {
        if (c >= args->size())
            convertedArgs->at(c) = (*i)->getValue();
        else
            convertedArgs->at(c) = args->at(c)->as((*i)->getType());

        c++;
    }

    return convertedArgs;
}

bool Signature::equals(Signature *other) {
    if (returnClass != other->returnClass)
        return false;

    if(params.size() != other->params.size())
        return false;

    list<Parameter *>::iterator j = other->params.begin();

    foreach (i, params)
        if (*i != *j++)
            return false;

    return true;
}

list<string> Signature::paramsNames() {
    list<string> names;

    foreach (i, params)
        names << (*i)->getName();

    return names;
}
