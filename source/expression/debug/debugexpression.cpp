#include "debugexpression.h"

#include "runtime.h"
#include "logger.h"

#if DEBUG_PARSER

int DebugExpression::indent = 0;

DebugExpression::DebugExpression(string name, list<Object *> args)
    : name(name), args(args) {
}

Object *DebugExpression::eval(Context *) {
    Logger::write("parser", toString());

    return Runtime::getNull();
}

string DebugExpression::toString() {
    string spacing;
    spacing.insert(0, 4 * indent, ' ');

    string str = "\n";

    bool fp = true;

    foreach (i, args) {
        if (!fp)
            str += ",\n";
        else
            fp = false;

        if (dynamic_cast<Expression *>(*i) == 0)
            str += spacing + "    ";

        indent++;
        str += (*i)->toString();
        indent--;
    }

    str += "\n" + spacing;

    return spacing + name + " {" + str + "}";
}

#endif
