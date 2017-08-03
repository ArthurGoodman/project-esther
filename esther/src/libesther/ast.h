#pragma once

#define EXPR_0(sym) (Tuple_new(es, 1, (sym)))
#define EXPR_1(sym, arg1) (Tuple_new(es, 2, (sym), (arg1)))
#define EXPR_2(sym, arg1, arg2) (Tuple_new(es, 3, (sym), (arg1), (arg2)))
#define EXPR_3(sym, arg1, arg2, arg3) (Tuple_new(es, 4, (sym), (arg1), (arg2), (arg3)))

#define EXPR_ARG1(e) (Tuple_get((e), 1))
#define EXPR_ARG2(e) (Tuple_get((e), 2))
#define EXPR_ARG3(e) (Tuple_get((e), 3))

#define EmptyExpression (Tuple_new(es, 0))

#define Expression_id(e) (Tuple_get((e), 0))

#define Expression_hasPosition(e) (Object_hasAttribute((e), c_str_to_id("pos")))
#define Expression_getPosition(e) (Object_getAttribute((e), c_str_to_id("pos")))
#define Expression_setPosition(e, position) (Object_setAttribute((e), c_str_to_id("pos"), (position)))

#define UnaryExpression_arg EXPR_ARG1

#define BinaryExpression_left EXPR_ARG1
#define BinaryExpression_right EXPR_ARG2

#define AssignExpression(left, right) EXPR_2(sym_assign, left, right)
#define PlusAssignExpression(left, right) EXPR_2(sym_plusAssign, left, right)
#define MinusAssignExpression(left, right) EXPR_2(sym_minusAssign, left, right)
#define MultiplyAssignExpression(left, right) EXPR_2(sym_multiplyAssign, left, right)
#define DivideAssignExpression(left, right) EXPR_2(sym_divideAssign, left, right)
#define ModAssignExpression(left, right) EXPR_2(sym_modAssign, left, right)
#define PowerAssignExpression(left, right) EXPR_2(sym_powerAssign, left, right)

#define LogicOrExpression(left, right) EXPR_2(sym_or, left, right)
#define LogicAndExpression(left, right) EXPR_2(sym_and, left, right)

#define EqExpression(left, right) EXPR_2(sym_eq, left, right)
#define NeExpression(left, right) EXPR_2(sym_ne, left, right)

#define LtExpression(left, right) EXPR_2(sym_lt, left, right)
#define GtExpression(left, right) EXPR_2(sym_gt, left, right)
#define LeExpression(left, right) EXPR_2(sym_le, left, right)
#define GeExpression(left, right) EXPR_2(sym_ge, left, right)

#define PlusExpression(left, right) EXPR_2(sym_plus, left, right)
#define MinusExpression(left, right) EXPR_2(sym_minus, left, right)
#define MultiplyExpression(left, right) EXPR_2(sym_multiply, left, right)
#define DivideExpression(left, right) EXPR_2(sym_divide, left, right)
#define ModExpression(left, right) EXPR_2(sym_mod, left, right)
#define PowerExpression(left, right) EXPR_2(sym_power, left, right)

#define NegateExpression(arg) EXPR_1(sym_not, arg)

#define CallExpression(self, args) EXPR_2(sym_call, self, args)
#define CallExpression_self EXPR_ARG1
#define CallExpression_args EXPR_ARG2

#define AttributeExpression(self, name) EXPR_2(sym_attr, self, name)
#define AttributeExpression_self EXPR_ARG1
#define AttributeExpression_name EXPR_ARG2

#define DotExpression(self, body) EXPR_2(sym_dot, self, body)
#define DotExpression_self EXPR_ARG1
#define DotExpression_body EXPR_ARG2

#define IdExpression(name) EXPR_1(sym_id, name)
#define IdExpression_name EXPR_ARG1

#define ValueExpression(value) EXPR_1(sym_sharp, value)
#define ValueExpression_value EXPR_ARG1

#define VarExpression(name) EXPR_1(sym_var, name)
#define VarAssignExpression(name, value) EXPR_2(sym_var, name, value)
#define VarExpression_name EXPR_ARG1
#define VarExpression_value EXPR_ARG2

#define SymbolExpression(name) EXPR_1(sym_colon, name)
#define SymbolExpression_name EXPR_ARG1

#define IfExpression(condition, body) EXPR_2(sym_if, condition, body)
#define IfElseExpression(condition, body, elseBody) EXPR_3(sym_if, condition, body, elseBody)
#define IfExpression_condition EXPR_ARG1
#define IfExpression_body EXPR_ARG2
#define IfExpression_elseBody EXPR_ARG3

#define WhileExpression(condition, body) EXPR_2(sym_while, condition, body)
#define DoExpression(condition, body) EXPR_2(sym_do, condition, body)
#define LoopExpression_condition EXPR_ARG1
#define LoopExpression_body EXPR_ARG2

#define TrueExpression EXPR_0(sym_true)
#define FalseExpression EXPR_0(sym_false)
#define NullExpression EXPR_0(sym_null)

#define SelfExpression EXPR_0(sym_self)
#define HereExpression EXPR_0(sym_here)

#define ContinueExpression EXPR_0(sym_continue)

#define BreakExpression EXPR_0(sym_break)
#define BreakValueExpression(value) EXPR_1(sym_break, value)
#define BreakExpression_value EXPR_ARG1

#define ReturnExpression EXPR_0(sym_return)
#define ReturnValueExpression(value) EXPR_1(sym_return, value)
#define ReturnExpression_value EXPR_ARG1

#define ClassExpression(name, body) EXPR_2(sym_class, name, body)
#define ClassInhExpression(name, superclass, body) EXPR_3(sym_class, name, body, superclass)
#define ClassExpression_name EXPR_ARG1
#define ClassExpression_body EXPR_ARG2
#define ClassExpression_superclass EXPR_ARG3

#define FunctionExpression(name, params, body) EXPR_3(sym_function, name, params, body)
#define FunctionExpression_name EXPR_ARG1
#define FunctionExpression_params EXPR_ARG2
#define FunctionExpression_body EXPR_ARG3

#define NewLiteralExpression(body) EXPR_1(sym_new, body)
#define NewExpression(name, args, body) EXPR_3(sym_new, body, name, args)
#define NewExpression_body EXPR_ARG1
#define NewExpression_name EXPR_ARG2
#define NewExpression_args EXPR_ARG3

#define ImportExpression(name) EXPR_1(sym_import, name)
#define ImportExpression_name EXPR_ARG1

#define TupleExpression(args) EXPR_1(sym_pars, args)
#define TupleExpression_args EXPR_ARG1

#define ArrayExpression(args) EXPR_1(sym_brackets, args)
#define ArrayExpression_args EXPR_ARG1

#define MapExpression(args) EXPR_1(sym_doubleArrow, args)
#define MapExpression_args EXPR_ARG1

#define BlockExpression(nodes) EXPR_1(sym_braces, nodes)
#define BlockExpression_nodes EXPR_ARG1
