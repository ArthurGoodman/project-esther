ast = (:"{}", [(:class, "A", (:call, (:attr, (:self), "setMethod"), [(:"#", "m"), (:new, (:"=", (:attr, (:self), "()"), (:function, "", ["this", "args"], (:call, (:attr, (:id, "IO"), "writeLine"), [(:id, "this"), (:id, "args")]))))])), (:"=", (:id, "a"), (:new, "A", [], ())), (:call, (:attr, (:id, "a"), "m"), [(:"#", "arg1"), (:"#", "arg2")])])
esther.eval(ast)
