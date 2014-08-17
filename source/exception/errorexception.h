#pragma once
#include <common.h>

#include "exception.h"

namespace Esther {

class ErrorException : public Exception
{
    string message;
    int line, column;

public:
};

}
