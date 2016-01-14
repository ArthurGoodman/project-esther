#include "debugexpression.h"

#include "runtime.h"
#include "logger.h"

#if DEBUG_PARSER

int DebugExpression::indent = 0;

DebugExpression::DebugExpression(string name, list<Object *> args)
    : name(name), args(args) {
}

Object *DebugExpression::exec(Context *) {
    Logger::write("parser", immediateToString());

    return Runtime::getNull();
}

string DebugExpression::immediateToString() {
    string spacing;
    spacing.insert(0, 4 * indent, ' ');

    string str = "\n";

    bool fp = true;

    for (Object *obj : args) {
        if (!fp)
            str += ",\n";
        else
            fp = false;

        if (dynamic_cast<Expression *>(obj) == 0)
            str += spacing + "    ";

        indent++;
        str += obj->immediateToString();
        indent--;
    }

    str += "\n" + spacing;

    return spacing + name + " {" + str + "}";
}

#endif
