#pragma once
#include <common.h>

#include "scriptengine.h"

namespace esther {

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
