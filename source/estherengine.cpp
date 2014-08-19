#include "estherengine.h"

#include "runtime.h"

#include "expression.h"
#include "defaultexpressionmanager.h"
#include "defaultparser.h"
#include "defaultlexer.h"
#include "errorexception.h"

namespace Esther {

EstherEngine::EstherEngine() { initialize(); }
EstherEngine::~EstherEngine() { release(); }

void EstherEngine::run(const string &script)
{
    Runtime::pushSource(script);

    try
    {
        Runtime::parser->parse(script);
    }
    catch(ErrorException *e) { cout << e->msg() << endl; delete e; }
    catch(...) { cout << "something bad happened...\n"; }

    Runtime::popSource();
}

void EstherEngine::initialize()
{
    Runtime::initialize();
    DefaultLexer::initialize();

    Expression::manager = new DefaultExpressionManager;
    Runtime::parser = new DefaultParser;
}

void EstherEngine::release()
{
    Runtime::release();

    delete Expression::manager;
    delete Runtime::parser;
}

}
