#ifndef __CALCULATOR__
#define __CALCULATOR__
#include "stack.h"
typedef enum { //Don't use 0 because it messes up the sign calculation
    LPAREN = 4,
    RPAREN = 4,
    POW = 3,
    MULT = 2,
    DIV = 2,
    ADD = 1,
    SUB = 1,
    ONE = -1,
    TWO = -2,
    THREE = -3,
    FOUR = -4,
    FIVE = -5,
    SIX = -6,
    SEVEN = -7,
    EIGHT = -8,
    NINE = -9,
    ZERO = -10
} ops;

int getp(char);
int getsign(char);
char *pformat(char *);
void feed(stack *, char *);
double calc(char *, char *, char);
stack *parse(stack *);
double eval(stack *);

#endif