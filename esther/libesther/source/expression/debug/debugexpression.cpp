#include "debugexpression.h"

#include "context.h"
#include "runtime.h"
#include "logger.h"

#if DEBUG_PARSER

int DebugExpression::indent = 0;

DebugExpression::DebugExpression(const std::string &name, const std::list<DebugExpression *> &args)
    : name(name), args(args) {
}

DebugExpression::~DebugExpression() {
    for (Expression *e : args)
        delete e;
}

Object *DebugExpression::exec(Context *context) {
    Logger::write("parser", toString() + "\n");

    return context->getRuntime()->getNull();
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

    return spacing + name + " {" + str + "}";
}

#endif
