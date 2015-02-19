#include "signature.h"

#include "runtime.h"
#include "class.h"
#include "tuple.h"

Signature::Signature()
    : returnClass(Runtime::getObjectClass()) {
}

Signature::Signature(Class *returnClass, list<Class *> argsClasses)
    : returnClass(returnClass), argsClasses(argsClasses) {
}

Signature::Signature(string returnClassName, list<string> argsClassesNames)
    : returnClass(Runtime::getRootClass(returnClassName)) {
    foreach (i, argsClassesNames)
        argsClasses << Runtime::getRootClass(*i);
}

bool Signature::accepts(Tuple *args) {
    if ((int)argsClasses.size() != args->size())
        return false;

    Tuple::iterator j = args->begin();

    foreach (i, argsClasses)
        if (!(*j++)->converts(*i))
            return false;

    return true;
}

Tuple *Signature::convert(Tuple *args) {
    Tuple *convertedArgs = new Tuple(args->size());

    list<Class *>::iterator j = argsClasses.begin();

    for(int i = 0; i < args->size(); i++)
        convertedArgs->at(i) = args->at(i)->as(*j++);

    return convertedArgs;
}

bool Signature::equals(Object *other) {
    if (!dynamic_cast<Signature *>(other))
        return false;

    Signature *otherSignature = (Signature *)other;

    if (!returnClass->equals(otherSignature->returnClass))
        return false;

    list<Class *>::iterator j = otherSignature->argsClasses.begin();

    foreach (i, argsClasses)
        if (!(*i)->equals(*j++))
            return false;

    return true;
}
