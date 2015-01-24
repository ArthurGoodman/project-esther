#include "estherengine.h"

#include "esther.h"
#include "expression.h"
#include "defaultexpressionmanager.h"
#include "defaultparser.h"
#include "defaultlexer.h"
#include "errorexception.h"
#include "logger.h"

namespace esther {

EstherEngine::EstherEngine() {
    initialize();
}

EstherEngine::~EstherEngine() {
    release();
}

void EstherEngine::run(const string &script) {
    Esther::pushSource(script);

    try {
        Expression *expr = Esther::parser->parse(Esther::lexer->lex(script));
#if DEBUG_PARSER
        Logger::setActiveLog("parser");
#endif
        expr->eval(0);
    } catch (ErrorException *e) {
        cout << e->msg() << endl;
        delete e;
    } catch (...) {
        cout << "something bad happened...\n";
    }

    Esther::popSource();
}

void EstherEngine::initialize() {
    Esther::initialize();
}

void EstherEngine::release() {
    Esther::release();
}
}
