#include "overloadedmethodblock.h"

#include "runtime.h"
#include "overloadedmethod.h"
#include "signature.h"

OverloadedMethodBlock::OverloadedMethodBlock(OverloadedMethod *method)
    : NativeBlock([method](Object * self, Tuple * args) -> Object * {
          list<Method *> methods = method->getMethods();

          Method *firstAccept = 0;

          foreach (i, methods) {
              if ((*i)->getSignature()->accepts(args) && !firstAccept)
                  firstAccept = *i;

              if ((*i)->getSignature()->check(args))
                  return (*i)->invoke(self, args);
          }

          return firstAccept->invoke(self, args);
      }) {
}
