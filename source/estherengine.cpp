#include "estherengine.h"

#include "runtime.h"

#include "expression.h"
#include "defaultexpressionmanager.h"

namespace Esther {

EstherEngine::EstherEngine() { initialize(); }
EstherEngine::~EstherEngine() { release(); }

void EstherEngine::run(string /*script*/)
{
}


void EstherEngine::initialize()
{
    Runtime::initialize();
    Expression::manager = new DefaultExpressionManager;
}

void EstherEngine::release()
{
    Runtime::release();
}

}
