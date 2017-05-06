class Parser {
    class Node
        function eval
            null

    class BinaryNode < Node {
        self.setMethod("super", function initialize(left, right) {
            self.left = left
            self.right = right
        })

        function eval
            self.oper.call(self.left.eval(), (self.right.eval()))

        function inspect(indent) {
            IO.write(indent)
            IO.writeLine(self)
            self.left.inspect(indent + "  ")
            self.right.inspect(indent + "  ")
        }
    }

    class PlusNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Numeric.getMethod("+")
        }

    class MinusNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Numeric.getMethod("-")
        }

    class MultiplyNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Numeric.getMethod("*")
        }

    class DivideNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Numeric.getMethod("/")
        }

    class PowerNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Numeric.getMethod("**")
        }

    class ValueNode < Node {
        function initialize(value)
            self.value = value

        function eval
            self.value

        function inspect(indent) {
            IO.write(indent)
            IO.writeLine(self.value)
        }
    }

    class Token {
        function initialize(id) {
            self.text = String(id)
            self.id = id
        }

        function inspect
            IO.writeLine("<" + self.text + ", " + self.id + ">")
    }

    function initialize {
        self.operators = "+-/*^()[]"

        self.debugLexer = false
        self.debugAST = false
    }

    function symbol
        if (self.pos >= self.code.size())
            '\0'
        else
            self.code.at(self.pos)

    function getToken {
        var parser = self

        while (symbol().isSpace())
            self.pos += 1

        if (symbol() == '\0')
            self.token = new Token('e')
        else if (symbol().isDigit())
            self.token = new Token('e') {
                self.id = 'n'
                self.text = ""

                while (parser.symbol().isDigit()) {
                    self.text += parser.symbol()
                    parser.pos += 1
                }
                
                if (parser.symbol() == '.') {
                    self.text += parser.symbol()
                    parser.pos += 1

                    while (parser.symbol().isDigit()) {
                        self.text += parser.symbol()
                        parser.pos += 1
                    }
                }
            }
        else if (self.operators.contains(symbol())) {
            self.token = new Token(symbol())
            self.pos += 1
        } else if (symbol().isLetter() || symbol() == '_')
            self.token = new Token('e') {
                self.id = 'u'
                self.text = ""

                while (parser.symbol().isLetter() || parser.symbol() == '_') {
                    self.text += parser.symbol()
                    parser.pos += 1
                }
            }
        else
            self.token = new Token('e') {
                self.id = 'u'
                self.text = parser.symbol()
                parser.pos += 1
            }

        if (self.debugLexer)
            self.token.inspect()
    }

    function accept(id) {
        var value = false

        if (self.token.id == id) {
            getToken()
            value = true
        }

        value
    }

    function check(id)
        self.token.id == id

    function error(message)
        if (!self.error)
            self.error = message

    function parse(code) {
        self.code = code
        self.pos = 0
        self.token = null
        self.error = null

        getToken()

        var node = addSub()

        if (!check('e'))
            error("there is an excess part of expression")

        if (node == null)
            node = new ValueNode(0)

        if (self.debugLexer)
            IO.writeLine("");

        if (self.debugAST) {
            node.inspect("")
            IO.writeLine("");
        }

        node
    }

    function addSub {
        var node = mulDiv()

        while (check('+') || check('-')) {
            if (accept('+'))
                node = new PlusNode(node, mulDiv())
            else if (accept('-'))
                node = new MinusNode(node, mulDiv())
        }

        node
    }

    function mulDiv {
        var node = power()

        while (check('*') || check('/')) {
            if (accept('*'))
                node = new MultiplyNode(node, power())
            else if (accept('/'))
                node = new DivideNode(node, power())
        }

        node
    }

    function power {
        var node = unary()

        while (accept('^'))
            node = new PowerNode(node, unary())

        node
    }

    function unary {
        var node

        if (accept('+'))
            node = new PlusNode(new ValueNode(0), term())
        else if (accept('-'))
            node = new MinusNode(new ValueNode(0), term())
        else
            node = term()

        node
    }

    function term {
        var node

        if (check('n')) {
            node = new ValueNode(Float(self.token.text))
            getToken()
        } else if (accept('(')) {
            node = addSub()

            if (!accept(')'))
                error("unmatched parentheses")
        } else if (accept('[')) {
            node = addSub()

            if (!accept(']'))
                error("unmatched brackets")
        } else if(check('e'))
            error("unexpected end of expression")
        else if(check('u'))
            error("unknown token '" + self.token.text + "'")
        else
            error("unexpected token '" + self.token.text + "'")

        node
    }
}

parser = new Parser
// parser.debugLexer = true
// parser.debugAST = true

node = parser.parse("2 * (3 + 2^-1) - 6")

if (parser.error)
    IO.writeLine("error: " + parser.error)
else
    node.eval()
