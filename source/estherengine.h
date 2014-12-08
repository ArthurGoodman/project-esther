#pragma once
#include <common.h>

#include "scriptengine.h"

namespace Esther {

class EstherEngine : public ScriptEngine {
public:
    EstherEngine();
    ~EstherEngine();

    void run(const string &script);

private:
    void initialize();
    void release();
};
}
