#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

typedef unsigned long int Id;

extern Id id_empty;
extern Id id_brace;
extern Id id_class;
extern Id id_eq;
extern Id id_self;
extern Id id_attr;
extern Id id_new;
extern Id id_function;
extern Id id_call;
extern Id id_id;
extern Id id_sharp;
extern Id id_dot;

const char *idToString(Id id);
Id stringToId(const char *str);

#ifdef __cplusplus
}
#endif
