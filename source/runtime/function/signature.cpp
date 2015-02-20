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

    //    Tuple::iterator j = args->begin();

    //    foreach (i, params)
    //        if (!(*j++)->converts((*i)->getType()))
    //            return false;

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

    //    list<Parameter *>::iterator j = params.begin();

    //    for (int i = 0; i < args->size(); i++)
    //        convertedArgs->at(i) = args->at(i)->as((*j++)->getType());

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

bool Signature::equals(Object *other) {
    if (!dynamic_cast<Signature *>(other))
        return false;

    Signature *otherSignature = (Signature *)other;

    if (!returnClass->equals(otherSignature->returnClass))
        return false;

    list<Parameter *>::iterator j = otherSignature->params.begin();

    foreach (i, params)
        if (!(*i)->equals(*j++))
            return false;

    return true;
}

list<string> Signature::paramsNames() {
    list<string> names;

    foreach (i, params)
        names << (*i)->getName();

    return names;
}
