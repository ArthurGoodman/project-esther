class Parser {
    class Node {
        method eval
            null
    }

    class BinaryNode < Node {
        method initialize(Node left, Node right) {
            self.left = left
            self.right = right
        }

        super = initialize

        method eval
            left.eval().oper(right.eval())
    }

    class PlusNode < BinaryNode
        method initialize(left, right) {
            super(left, right)
            self.oper = Float.+
        }

    class MinusNode < BinaryNode
        method initialize(left : Node, right : Node) {
            super(left, right)
            self.oper = Float.-
        }

    class MultiplyNode < BinaryNode
        method initialize(Node left, right) {
            super(left, right)
            self.oper = function (Float a) self * a
        }

    class DivideNode < BinaryNode
        method initialize(left, ...) {
            super(left, arguments[1])
            self.oper = Float./
        }

    class PowerNode < BinaryNode
        method initialize(...) {
            super(arguments[0], arguments[1])
            self.oper = Float.**
        }

    class ValueNode < Node {
        method initialize(value : Float = 0)
            self.value = value

        method eval
            value
    }

    class Token {
        method initialize {}

        method initialize(id) {
            self.text = String(id)
            self.id = id
        }

        method inspect
            print("<" + text + ", " + id + ">\n")
    }

    method initialize
        self.operators = "+-/*^()[]"

    method at(pos)
        if pos >= code.size() '\0'
        else code[pos]

    method getToken {
        p = self

        while (at(pos).isSpace())
            pos++

        if (at(pos) == '\0') token = new Token('e')
        elif (at(pos).isDigit()) token = new Token {
            id = 'n'
            text = ""

            while (p.at(pos).isDigit())
                text += p.at(pos++ - 1)
            
            if (p.at(pos) == '.') do
                text += p.at(pos++ - 1)
            while (p.at(pos).isDigit())
        } elif (operators.contains(at(pos))) token = Token(at(pos++ - 1))
        elif (at(pos).isLetter() || at(pos) == '_') token = new Token {
            id = 'u'
            text = ""   
            
            while (p.at(pos).isLetter() || p.at(pos) == '_')
                text += p.at(pos++ - 1)
        } else token = new Token {
            id = 'u'
            text = p.at(pos++ - 1)
        }
    }

    method accept(id) {
        if (token.id == id) {
            getToken()
            return true
        }

        false
    }

    method check(id)
        token.id == id

    method parse : Node(String code) {
        self.code = code
        self.pos = 0
        self.token = null

        getToken()

        //while (token) {
        //    token.inspect()
        //    getToken()
        //}

        node = addSub()

        if (node == null)
            node = new ValueNode

        //if(!check('e'))
        //    ...

        node
    }

    method addSub {
        node = mulDiv()

        forever {
            if (accept('+'))
                node = new PlusNode(node, mulDiv())
            elif (accept('-'))
                node = new MinusNode(node, mulDiv())
            else
                break
        }

        node
    }

    method mulDiv {
        node = power()

        forever {
            if (accept('*'))
                node = new MultiplyNode(node, power())
            elif (accept('/'))
                node = new DivideNode(node, power())
            else
                break
        }

        node
    }

    method power {
        node = unary()

        forever {
            if (accept('^'))
                node = new PowerNode(node, unary())
            else
                break
        }

        node
    }

    method unary {
        node = null

        if (accept('+'))
            node = new PlusNode(new ValueNode, term())
        else if (accept('-'))
            node = new MinusNode(ValueNode(), term())
        else
            node = term()

        node
    }

    method term {
        node = null

        if (check('n')) {
            node = new ValueNode(new Float(token.text))
            getToken()
        } elif (accept('(')) {
            node = addSub()

            if (!accept(')'))
                node = null
        } elif (accept('[')) {
            node = addSub()

            if (!accept(']'))
                node = null
        }

        node
    }
}

new Parser.parse("").eval()

//forever {
//    "$ ".print()

//    str = scanLine()

//    if (str.empty() continue
//    elif (str == "help" || str == "?")
//        print("This is help!\n")
//    elif (str == "exit" || str == "quit")
//        break;
//    else {
//        parser = new Parser()
//        ast = parser.parse("")
//        ast.print()
//    }

//    "\n".print()
//}
