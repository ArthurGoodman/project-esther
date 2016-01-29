#include "matchfailureexception.h"

std::string MatchFailureException::message() {
    return "match failure";
}

void MatchFailureException::raise() {
    throw this;
}
