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
            self.oper = function (a) self * a
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
    }

    class Token {
        function initialize(id) {
            self.text = String(id)
            self.id = id
        }

        function inspect
            print("<" + text + ", " + id + ">\n")
    }

    function initialize
        self.operators = "+-/*^()[]"

    function at(pos)
        if pos >= code.size() '\0'
        else code[pos]

    function getToken {
        while (at(pos).isSpace())
            pos = pos + 1

        if (at(pos) == '\0') token = new Token('e')
        else if (at(pos).isDigit()) token = new Token('e') {
            self.id = 'n'
            self.text = ""

            while (at(pos).isDigit()) {
                text += at(pos)
                pos = pos + 1
            }
            
            if (at(pos) == '.') {
                text += at(pos)
                pos = pos + 1

                while (at(pos).isDigit()) {
                    text += at(pos)
                    pos = pos + 1
                }
            }
        } else if (operators.contains(at(pos))) {
            token = Token(at(pos))
            pos = pos + 1
        } else if (at(pos).isLetter() || at(pos) == '_') token = new Token('e') {
            self.id = 'u'
            self.text = ""
            
            while (at(pos).isLetter() || at(pos) == '_') {
                text += at(pos)
                pos = pos + 1
            }
        } else token = new Token {
            self.id = 'u'
            self.text = at(pos)
            pos = pos + 1
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

        // while (token) {
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

        forever {
            if (accept('+'))
                node = new PlusNode(node, mulDiv())
            else if (accept('-'))
                node = new MinusNode(node, mulDiv())
            else
                break
        }

        node
    }

    function mulDiv {
        node = power()

        forever {
            if (accept('*'))
                node = new MultiplyNode(node, power())
            else if (accept('/'))
                node = new DivideNode(node, power())
            else
                break
        }

        node
    }

    function power {
        node = unary()

        forever {
            if (accept('^'))
                node = new PowerNode(node, unary())
            else
                break
        }

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

new Parser.parse("2 * (3 + 2^-1) - 6").eval()

// forever {
//     "$ ".print()

//     str = scanLine()

//     if (str.empty()) continue
//     else if (str == "help" || str == "?")
//         print("This is help!\n")
//     else if (str == "exit" || str == "quit")
//         break;
//     else {
//         parser = new Parser()
//         ast = parser.parse(str)
//         ast.eval().print()
//         "\n".print()
//     }

//     "\n".print()
// }
