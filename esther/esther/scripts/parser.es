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
            left.eval().oper(right.eval())

        function inspect(indent) {
            write(indent)
            writeLine(self)
            left.inspect(indent + "  ")
            right.inspect(indent + "  ")
        }
    }

    class PlusNode < BinaryNode
        function initialize(left, right) {
            super(left, right)
            self.oper = Float.+
        }

    class MinusNode < BinaryNode
        function initialize(left, right) {
            super(left, right)
            self.oper = Float.-
        }

    class MultiplyNode < BinaryNode
        function initialize(left, right) {
            super(left, right)
            self.oper = Float.*
        }

    class DivideNode < BinaryNode
        function initialize(left, right) {
            super(left, right)
            self.oper = Float./
        }

    class PowerNode < BinaryNode
        function initialize(left, right) {
            super(left, right)
            self.oper = Float.**
        }

    class ValueNode < Node {
        function initialize(value)
            self.value = value

        function eval
            value

        function inspect(indent) {
            write(indent)
            writeLine(value)
        }
    }

    class Token {
        function initialize(id) {
            self.text = String(id)
            self.id = id
        }

        function inspect
            writeLine("<" + text + ", " + id + ">")
    }

    function initialize
        self.operators = "+-/*^()[]"

    function at(pos)
        if pos >= code.size() '\0'
        else code[pos]

    function getToken {
        this = self

        while (at(pos).isSpace())
            self.pos = pos + 1

        if (at(pos) == '\0') self.token = new Token('e')
        else if (at(pos).isDigit()) self.token = new Token('e') {
            self.id = 'n'
            self.text = ""

            while (at(pos).isDigit()) {
                text += at(pos)
                this.pos = pos + 1
            }
            
            if (at(pos) == '.') {
                text += at(pos)
                this.pos = pos + 1

                while (at(pos).isDigit()) {
                    text += at(pos)
                    this.pos = pos + 1
                }
            }
        } else if (operators.contains(at(pos))) {
            self.token = new Token(at(pos))
            self.pos = pos + 1
        } else if (at(pos).isLetter() || at(pos) == '_') self.token = new Token('e') {
            self.id = 'u'
            self.text = ""
            
            while (at(pos).isLetter() || at(pos) == '_') {
                text += at(pos)
                this.pos = pos + 1
            }
        } else self.token = new Token {
            self.id = 'u'
            self.text = at(pos)
            this.pos = pos + 1
        }
    }

    function accept(id) {
        value = false

        if (token.id == id) {
            getToken()
            value = true
        }

        value
    }

    function check(id)
        token.id == id

    function parse(code) {
        self.code = code
        self.pos = 0
        self.token = null

        getToken()

        // while (token.id != 'e') {
        //    token.inspect()
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
            node = new ValueNode(new Float(token.text))
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

node = new Parser.parse("(1 + 6) - (1 * 9)")
node.inspect("")
node.eval()
