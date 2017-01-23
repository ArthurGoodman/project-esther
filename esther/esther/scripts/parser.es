class Parser {
    class Node {
        function eval
            null
    }

    class BinaryNode < Node {
        super = function initialize(left, right) {
            self.left = left
            self.right = right
        }

        function eval
            self.oper.'()'(self.left.eval(), self.right.eval())

        function inspect(indent) {
            console.write(indent)
            console.writeLine(self)
            self.left.inspect(indent + "  ")
            self.right.inspect(indent + "  ")
        }
    }

    class PlusNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Float.+
        }

    class MinusNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Float.-
        }

    class MultiplyNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Float.*
        }

    class DivideNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Float./
        }

    class PowerNode < BinaryNode
        function initialize(left, right) {
            self.super(left, right)
            self.oper = Float.**
        }

    class ValueNode < Node {
        function initialize(value)
            self.value = value

        function eval
            self.value

        function inspect(indent) {
            console.write(indent)
            console.writeLine(self.value)
        }
    }

    class Token {
        function initialize(id) {
            self.text = String(id)
            self.id = id
        }

        function inspect
            console.writeLine("<" + self.text + ", " + self.id + ">")
    }

    function initialize
        self.operators = "+-/*^()[]"

    function at(pos)
        if pos >= self.code.size() '\0'
        else self.code[pos]

    function getToken {
        parser = self

        while (at(self.pos).isSpace())
            self.pos = self.pos + 1

        if (at(self.pos) == '\0') self.token = new Token('e')
        else if (at(self.pos).isDigit()) self.token = new Token('e') {
            id = 'n'
            text = ""

            while (parser.at(parser.pos).isDigit()) {
                text = self.text + parser.at(parser.pos)
                parser.pos = parser.pos + 1
            }
            
            if (parser.at(parser.pos) == '.') {
                text = self.text + parser.at(parser.pos)
                parser.pos = parser.pos + 1

                while (parser.at(parser.pos).isDigit()) {
                    text = self.text + parser.at(parser.pos)
                    parser.pos = parser.pos + 1
                }
            }
        } else if (self.operators.contains(at(self.pos))) {
            self.token = new Token(at(self.pos))
            self.pos = self.pos + 1
        } else if (at(self.pos).isLetter() || at(self.pos) == '_') self.token = new Token('e') {
            id = 'u'
            text = ""
            
            while (parser.at(parser.pos).isLetter() || parser.at(parser.pos) == '_') {
                text = text + parser.at(parser.pos)
                parser.pos = parser.pos + 1
            }
        } else self.token = new Token('e') {
            id = 'u'
            text = parser.at(parser.pos)
            parser.pos = parser.pos + 1
        }
    }

    function accept(id) {
        value = false

        if (self.token.id == id) {
            getToken()
            value = true
        }

        value
    }

    function check(id)
        self.token.id == id

    function parse(code) {
        self.code = code
        self.pos = 0
        self.token = null

        getToken()

        // while (self.token.id != 'e') {
        //    self.token.inspect()
        //    getToken()
        // }

        node = addSub()

        if (node == null)
            node = new ValueNode(0)

        // if (!check('e'))
        //     ...

        node
    }

    function addSub {
        node = mulDiv()

        while (check('+') || check('-')) {
            if (accept('+'))
                node = new PlusNode(node, mulDiv())
            else if (accept('-'))
                node = new MinusNode(node, mulDiv())
        }

        node
    }

    function mulDiv {
        node = power()

        while (check('*') || check('/')) {
            if (accept('*'))
                node = new MultiplyNode(node, power())
            else if (accept('/'))
                node = new DivideNode(node, power())
        }

        node
    }

    function power {
        node = unary()

        while (accept('^'))
            node = new PowerNode(node, unary())

        node
    }

    function unary {
        node = null

        if (accept('+'))
            node = new PlusNode(new ValueNode(0), term())
        else if (accept('-'))
            node = new MinusNode(new ValueNode(0), term())
        else
            node = term()

        node
    }

    function term {
        node = null

        if (check('n')) {
            node = new ValueNode(new Float(self.token.text))
            getToken()
        } else if (accept('(')) {
            node = addSub()

            if (!accept(')'))
                node = null
        } else if (accept('[')) {
            node = addSub()

            if (!accept(']'))
                node = null
        }

        node
    }
}

new Parser.parse("2 * (3 + 2^-1) - 6").eval()
