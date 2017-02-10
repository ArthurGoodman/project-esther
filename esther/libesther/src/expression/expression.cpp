#include "expression/expression.h"

#include "esther.h"
#include "exception/errorexception.h"

namespace es {

Expression::~Expression() {
}

Object *Expression::eval(Esther *esther) {
    Object *volatile value = nullptr;

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
}
