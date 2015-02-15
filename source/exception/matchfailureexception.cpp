#include "matchfailureexception.h"

string MatchFailureException::message() {
    return "match failure";
}

void MatchFailureException::raise() {
    throw this;
}
