class BinaryNode
    method initialize(left, right) {
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

class ValueNode {
    method initialize(value)
        self.value = value

    method eval
        value
}

class Parser {
    method parse : Integer(code) {
        "This is ast!\n"
    }
}

//forever {
//    "$ ".print()

//    str = scanLine()

//    if (str.size() == 0) continue
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
