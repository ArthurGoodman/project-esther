#include "estherengine.h"

#include "esther.h"

#include "expression.h"
#include "defaultexpressionmanager.h"
#include "defaultparser.h"
#include "defaultlexer.h"
#include "errorexception.h"

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
        Esther::parser->parse(script);
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
