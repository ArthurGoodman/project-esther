#include "nativecallexpression.h"

#include "common.h"

NativeCallExpression::NativeCallExpression(Object *(*f)(Context *...), const std::list<Expression *> &args)
    : f((Object * (*)())f), args(args) {
}

NativeCallExpression::~NativeCallExpression() {
    for (Expression *e : args)
        delete e;
}

Object *NativeCallExpression::exec(Context *context) {
    std::vector<void *> evaledArgs;
    evaledArgs.reserve(args.size() + 1);

    evaledArgs << context;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    void *const *argsData = evaledArgs.data();

    for (int i = evaledArgs.size() - 1; i >= 0; i--)
        asm("push %0"
            :
            : "g"(argsData[i]));

    Object *result = f();

    asm("add esp, %0"
        :
        : "g"(evaledArgs.size() * sizeof(void *)));

    return result;
}
