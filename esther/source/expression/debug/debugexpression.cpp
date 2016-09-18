#include "debugexpression.h"

#include "runtime.h"
#include "logger.h"

#if DEBUG_PARSER

int DebugExpression::indent = 0;

DebugExpression::DebugExpression(const std::string &name, std::list<DebugExpression *> args)
    : name(name), args(args) {
}

Object *DebugExpression::exec(Context *) {
    Logger::write("parser", toString());

    return Runtime::getNull();
}

std::string DebugExpression::toString() {
    std::string spacing;
    spacing.insert(0, 4 * indent, ' ');

    std::string str = "\n";

    bool fp = true;

    for (DebugExpression *expr : args) {
        if (!fp)
            str += ",\n";
        else
            fp = false;

        if (dynamic_cast<Expression *>(expr) == 0)
            str += spacing + "    ";

        indent++;
        str += expr->toString();
        indent--;
    }

    str += "\n" + spacing;

    return spacing + name + " {" + str + "}";
}

#endif
