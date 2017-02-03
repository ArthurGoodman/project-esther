#include "expression/expression.h"

#include "runtime/esther.h"
#include "exception/errorexception.h"

Expression::~Expression() {
}

Ptr<Object> Expression::eval(Esther *esther) {
    Object *value = nullptr;

    try {
        value = exec(esther);
    } catch (ErrorException *e) {
        if (!e->getPosition().isValid())
            e->setPosition(getPosition());

        e->raise();
    }

    esther->setReg(value);

    return value;
}

Position Expression::getPosition() const {
    return position;
}

void Expression::setPosition(Position position) {
    this->position = position;
}
