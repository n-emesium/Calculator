#ifndef __STACK__
#define __STACK__
#define DEFSIZE 10
#define TOKLIM 32
#define INPUTLIM 256
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
typedef struct stack {
    char **args;
    size_t len;
    size_t capac;
} stack;
bool isdigit(char *);
double cformat(char *);
stack *create(void);
void push(stack *, char *);
void pop(stack *);
void sfree(stack *);
void pstack(stack *);

#endif
