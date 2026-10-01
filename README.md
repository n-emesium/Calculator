Expression calculator in C.

This parses and evaluates math expressions. It tokenizes the input, converts infix to postfix with the shunting-yard algorithm (operator precedence, parentheses, ^ for powers), then evaluates the postfix on a custom stack.

The stacks are my own with capacity doubling, and the decimal conversion routines are written from scratch. No parser generators.

Build it with:

cc calculator.c stack.c main.c -o calc

Run it with the expression as an argument:

./calc "3 + 4 * 2"

--EGE
