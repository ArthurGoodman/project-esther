#include "expression/debug/debugexpression.h"

#include "esther.h"
#include "runtime/context.h"
#include "common/log.h"

#ifdef DEBUG_EXPRESSION

namespace es {

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
    Log::write("parser", "%s\n", toString().c_str());
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
}

#endif
