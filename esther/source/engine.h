#pragma once

#include "iengine.h"

class Engine : public IEngine {
public:
    Object *run(const std::string &script);
    Object *runFile(const std::string &fileName);
};
