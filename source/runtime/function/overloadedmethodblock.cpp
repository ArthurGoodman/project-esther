#include "overloadedmethodblock.h"

#include "runtime.h"
#include "overloadedmethod.h"
#include "signature.h"

OverloadedMethodBlock::OverloadedMethodBlock(OverloadedMethod *method)
    : NativeBlock([method](Object *self, Tuple * args) -> Object * {
          list<Method *> methods = method->getMethods();

          Method *firstAccept = 0;

          for (Method *m : methods) {
              if (m->getSignature()->accepts(args) && !firstAccept)
                  firstAccept = m;

              if (m->getSignature()->check(args))
                  return m->invoke(self, args);
          }

          return firstAccept->invoke(self, args);
      }) {
}
