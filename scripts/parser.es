class Node {
    method eval
        null
}

class BinaryNode < Node
    method initialize(Node left, Node right) {
        self.left = left
        self.right = right
    }

class PlusNode < BinaryNode
    method eval
        left.eval() + right.eval()

class MinusNode < BinaryNode
    method eval 
        left.eval() - right.eval()

class MultiplyNode < BinaryNode
    method eval
        left.eval() * right.eval()

class DivideNode < BinaryNode
    method eval
        left.eval() / right.eval()

class PowerNode < BinaryNode
    method eval
        left.eval() ** right.eval()

class ValueNode < Node {
    method initialize(value)
        self.value = value

    method eval
        value
}

class Parser {
    method getToken {
        if (pos >= code.size())
            token = null
        elif (code[pos].isDigit())
            token = new {
                text = ""
                while (pos < code.size() && code[pos].isDigit())
                    //text += code[pos++ - 1]
                    text = text + code[pos++ - 1]

                type = 'n'
            }
        else
            token = new {
                text = code[pos++ - 1]
                type = 'u'
            }
    }

    method parse : Node(String code) {
        self.code = code
        self.pos = 0
        self.token = null

        getToken()

        while (token) {
            print(token.text)
            getToken()
        }

        new ValueNode(123)
    }
}

new Parser.parse("1 2 3 4 5").eval()

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
