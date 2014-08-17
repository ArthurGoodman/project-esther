#pragma once
#include <common.h>

#include "scriptengine.h"

namespace Esther {

class EstherEngine : public ScriptEngine
{
public:
    EstherEngine();
    ~EstherEngine();

    void run(string script);

private:
    void initialize();
    void release();
};

}
