#include "debugexpression.h"

#include "runtime/context.h"
#include "runtime/esther.h"
#include "common/logger.h"

#if DEBUG_PARSER

int DebugExpression::indent = 0;

DebugExpression::DebugExpression(const std::string &name, const std::list<DebugExpression *> &args)
    : name(name)
    , args(args) {
}

DebugExpression::~DebugExpression() {
    for (Expression *e : args)
        delete e;
}

Object *DebugExpression::exec(Esther *esther) {
    Logger::write("parser", toString() + "\n");
    return esther->getNull();
}

std::string DebugExpression::toString() const {
    std::string spacing;
    spacing.insert(0, 4 * indent, ' ');

    std::string str = "\n";

    bool fp = true;

    for (DebugExpression *expr : args) {
        if (!fp)
            str += ",\n";
        else
            fp = false;

        indent++;
        str += expr->toString();
        indent--;
    }

    str += (args.empty() ? "" : "\n") + spacing;

    return spacing + name + (getPosition().isValid() ? " (" + getPosition().toString() + ")" : "") + " {" + str + "}";
}

#endif
