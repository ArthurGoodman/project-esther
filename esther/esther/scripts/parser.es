class Parser {
    class Node
        function eval
            null

    class BinaryNode < Node {
        super = function initialize(left, right) {
            @left = left
            @right = right
        }

        function eval
            @oper.call(@left.eval(), @right.eval())

        function inspect(indent) {
            console.write(indent)
            console.writeLine(self)
            @left.inspect(indent + "  ")
            @right.inspect(indent + "  ")
        }
    }

    class PlusNode < BinaryNode
        function initialize(left, right) {
            @super(left, right)
            @oper = Float.+
        }

    class MinusNode < BinaryNode
        function initialize(left, right) {
            @super(left, right)
            @oper = Float.-
        }

    class MultiplyNode < BinaryNode
        function initialize(left, right) {
            @super(left, right)
            @oper = Float.*
        }

    class DivideNode < BinaryNode
        function initialize(left, right) {
            @super(left, right)
            @oper = Float./
        }

    class PowerNode < BinaryNode
        function initialize(left, right) {
            @super(left, right)
            @oper = Float.**
        }

    class ValueNode < Node {
        function initialize(value)
            @value = value

        function eval
            @value

        function inspect(indent) {
            console.write(indent)
            console.writeLine(@value)
        }
    }

    class Token {
        function initialize(id) {
            @text = String(id)
            @id = id
        }

        function inspect
            console.writeLine("<" + @text + ", " + @id + ">")
    }

    function initialize {
        @operators = "+-/*^()[]"

        @debugLexer = false
        @debugAST = false
    }

    function at(pos) {
        if pos >= @code.size() '\0'
        else @code[pos]
    }

    function getToken {
        p = self

        while (at(@pos).isSpace())
            @pos = @pos + 1

        if (at(@pos) == '\0')
            @token = new Token('e')
        else if (at(@pos).isDigit())
            @token = new Token('e') {
                @id = 'n'
                @text = ""

                while (p.at(p.pos).isDigit()) {
                    @text += p.at(p.pos)
                    p.pos = p.pos + 1
                }
                
                if (p.at(p.pos) == '.') {
                    @text += p.at(p.pos)
                    p.pos = p.pos + 1

                    while (p.at(p.pos).isDigit()) {
                        @text += p.at(p.pos)
                        p.pos = p.pos + 1
                    }
                }
            }
        else if (@operators.contains(at(@pos))) {
            @token = new Token(at(@pos))
            @pos = @pos + 1
        } else if (at(@pos).isLetter() || at(@pos) == '_')
            @token = new Token('e') {
                @id = 'u'
                @text = ""
                
                while (p.at(p.pos).isLetter() || p.at(p.pos) == '_') {
                    @text += p.at(p.pos)
                    p.pos = p.pos + 1
                }
            }
        else
            @token = new Token('e') {
                @id = 'u'
                @text = p.at(p.pos)
                p.pos = p.pos + 1
            }
    }

    function accept(id) {
        value = false

        if (@token.id == id) {
            getToken()
            value = true
        }

        value
    }

    function check(id)
        @token.id == id

    function error(message)
        if (!@error)
            @error = message

    function parse(code) {
        @code = code
        @pos = 0
        @token = null
        @error = null

        getToken()

        node = null

        if (@debugLexer) {
            while (!check('e')) {
               @token.inspect()
               getToken()
            }
        } else {
            node = addSub()

            if (!check('e'))
                error("there is an excess part of expression")

            if (@debugAST)
                node.inspect("")
        }

        if (node == null)
            node = new ValueNode(0)

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
            node = new ValueNode(Float(@token.text))
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
            error("unknown token '" + @token.text + "'")
        else
            error("unexpected token '" + @token.text + "'")

        node
    }
}

parser = new Parser
// parser.debugLexer = true
// parser.debugAST = true

node = parser.parse("2 * (3 + 2^-1) - 6")

if (parser.error)
    console.writeLine("error: " + parser.error)
else
    node.eval()
