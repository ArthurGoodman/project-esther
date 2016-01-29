#pragma once

class Context;
class Tuple;

class Call {
    Context *context;
    Tuple *args;

public:
    Call(Context *context, Tuple *args);

    Context *getContext();
    Tuple *getArgs();
};
