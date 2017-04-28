class A {
    self.setMethod("m", new {
        self.() = function(this, args) {
            IO.writeLine(this, args)
        }
    })
}

a = new A

a.m("arg1", "arg2")
