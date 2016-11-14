class BinaryNode {
    function initialize(oper, left, right) {
        self.left = left
        self.right = right
        self.oper = oper
    }

    function eval {
        (left.eval()).oper(right.eval())
    }
}

class ValueNode {
    function initialize(value)
        self.value = value

    function eval
        value
}

new BinaryNode(Float.*, new ValueNode(1), new BinaryNode(Float.-, new ValueNode(3), new ValueNode(10))).eval()
