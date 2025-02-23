#include "calculator.h"

int getp(char c) { //used for evaluating the priority between two operators when they are being pushed on the stack
    switch (c) {
        case '(':
            return LPAREN;
        case ')':
            return RPAREN;
        case '^':
            return POW;
        case '*':
            return MULT;
        case '/':
            return DIV;
        case '+':
            return ADD;
        case '-':
            return SUB;
        default:
            //printf("FATAL FAILURE, received unexpected character: '%c' (ASCII: %d)\n", c, c);
            return -1;
    }
}

int getsign(char c) {
    int d = c - '0';
    if (!isdigit(&c)) {
        return getp(c);
    }
    switch (d) {
        case 0:
            return ZERO;
        case 1:
            return ONE;
        case 2:
            return TWO;
        case 3:
            return THREE;
        case 4:
            return FOUR;
        case 5:
            return FIVE;
        case 6:
            return SIX;
        case 7:
            return SEVEN;
        case 8:
            return EIGHT;
        case 9:
            return NINE;
        default:
            printf("FATAL FAILURE, EXIT CODE -1\n");
            return -1;
    }
}

char *pformat(char *arg) {
    char *fstr = malloc(sizeof(char) * INPUTLIM);
    int j = 0;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '(') {
            fstr[j] = arg[i];
            fstr[j + 1] = ' ';
            j += 2;
        } else if (arg[i] == ')') {
            fstr[j] = ' ';
            fstr[j + 1] = arg[i];
            j += 2;
        } else {
            fstr[j] = arg[i];
            j++;
        }
    }
    fstr[j] = '\0';
    return fstr;
}

void feed(stack *s, char *arg) { 
    //char *narg = pformat(arg);
    char buffer[TOKLIM];
    int i = 0;
    while (arg[i] != '\0') { //processes entire string
        int j = 0;
        while (arg[i] != '\0' && arg[i] == ' ') {
            i++;
        }
        while (arg[i] != '\0' && arg[i] != ' ') {
            buffer[j] = arg[i];
            i++;
            j++;
        }
        buffer[j] = '\0';
        push(s, buffer);
    }
    //free(narg);
}

double calc(char *arg1, char *arg2, char op) {
    switch (op) {
        case '^':
            return pow(cformat(arg1), cformat(arg2));
        case '*':
            return cformat(arg1) * cformat(arg2);
        case '/':
            return cformat(arg1) / cformat(arg2);
        case '+':
            return cformat(arg1) + cformat(arg2);
        case '-':
            return cformat(arg1) - cformat(arg2);
        default:
            printf("FATAL FAILURE, EXIT CODE -1\n");
            exit(-1);
    }
}

//THIS WORKS DON'T CHANGE IT:

/*
stack *parse(stack *arg) {
    stack *res = create();
    stack *op = create();
    int i = 0;
    while (i < arg->len) {
        printf("OPERATING STACK: ");
        pstack(op);
        printf("\n");
        printf("RESULT STACK: ");
        pstack(res);
        printf("\n");
        char *cur = arg->args[i];
        if (isdigit(cur)) {
            push(res, cur);
        } else if (*cur != ' ') { //check if token isn't space
            if (*cur == '(') { 
                push(op, cur);
            } else if (*cur == ')') { //rparen
                while (op->len > 0 && *op->args[op->len -1] != '(') { //pop off until '(' is found and pop off that too
                    push(res, op->args[op->len -1]);
                    pop(op);
                }
                //pstack(op);
                pop(op);
                //pstack(op);
            } else { //operator precedence logic must be used here! && higher getp = higher precedence
                while (op->len > 0 && getp(*cur) <= getp(*op->args[op->len - 1]) && *op->args[op->len - 1] != '(') {
                    push(res, op->args[op->len - 1]);
                    pop(op);
                }
                push(op, cur);
            }
        }
        i++;
    }
    while (op->len != 0) { //ensure operators are empty
        push(res, op->args[op->len - 1]);
        pop(op);
    }
    sfree(op);
    return res;
}*/


stack *parse(stack *arg) {
    stack *res = create();
    stack *op = create();
    int i = 0;
    while (i < arg->len) {
        char *cur = arg->args[i];
        if (isdigit(cur)) {
            push(res, cur);
        } else if (*cur != ' ') { //check if token isn't space
            if (*cur == '(') { 
                push(op, cur);
            } else if (*cur == ')') { //rparen
                while (op->len > 0 && *op->args[op->len -1] != '(') { //pop off until '(' is found and pop off that too
                    push(res, op->args[op->len -1]);
                    pop(op);
                }
                //pstack(op);
                pop(op);
                //pstack(op);
            } else { //operator precedence logic must be used here! && higher getp = higher precedence
                while (op->len > 0 && getp(*cur) <= getp(*op->args[op->len - 1]) && *op->args[op->len - 1] != '(') {
                    push(res, op->args[op->len - 1]);
                    pop(op);
                }
                push(op, cur);
            }
        }
        i++;
    }
    while (op->len != 0) { //ensure operators are empty
        push(res, op->args[op->len - 1]);
        pop(op);
    }
    sfree(op);
    return res;
}

char *charcv(double d) {
    char *c = malloc(sizeof(char) * TOKLIM);
    int pint = (int)d;
    d -= pint;
    int j = 0;
    c[0] = '0';
    bool raised = false;
     while (pint >= 1) {
         raised = true;
         c[j] = pint % 10 + '0'; 
         pint /= 10;
         j++;  
     }
    for (int i = 0; i < j / 2; i++) {
         char temp = c[i];
         c[i] = c[j - 1 - i];
         c[j - 1 - i] = temp;
     }
     if (!raised) {
         j++;
     }
     c[j] = '.';
     j++;
     int plim = 10;
     while (plim > 0) {
         d *= 10;
         c[j] = (int)d + '0';
         d-= (int)d;
         j++;
         plim--;
     }
     c[j] = '\0';
     c = realloc(c, (j + 1) * sizeof(char));
    return c;
 }

/**
 * double calc(char *arg1, char *arg2, char op) here is the calc signature, i put this to not confuse you
 * 
 */



 double eval(stack *res) { //converts from rpn to an actual answer
    stack *mempt = create();
    int i = 0;
    while (i < res->len) {
        char *c = res->args[i];
        if (isdigit(c)) {
            push(mempt, c);
        } else { //we have found an operator here
            double temp = calc(mempt->args[mempt->len - 2], mempt->args[mempt->len - 1], *c);
            pop(mempt);
            pop(mempt);
            push(mempt, charcv(temp));
        }
        i++;
    }
    double d = cformat(mempt->args[0]);
    free(mempt);
    free(res);
    return d;
}
