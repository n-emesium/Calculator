#include "stack.h"

bool isdigit(char *c) {
    return !(*c == '(' || *c == ')' || *c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '%' || *c == '^' || *c == ' ');  
}

double cformat(char *c) {
    if (isdigit(c)) {
        bool flag = false;
        double d = 0;
        int i = 0;
        while (c[i] != '\0') {
            if (c[i] == '.') {
                i++;
                flag = !flag;
                break;
            }
            d = 10 * d + (c[i] - '0');
            i++;
        }
        if (flag) {
            int db = 10;
            while (c[i] != '\0') { //guaranteed to start 1 point after . operator
                d += ((double) (c[i] - '0')) / db;
                db *= 10;
                i++;
            }
        }
        return d;
    }
    return -1;
}

stack *create(void) {
    stack *s = malloc(sizeof(stack));
    s->len = 0;
    s->capac = DEFSIZE;
    s->args = malloc(sizeof(char *) * s->capac);
    for (int i = 0; i < s->capac; i++) {
        (s->args)[i] = malloc(sizeof(char) * TOKLIM); //MAX 32 CHARS ALLOWED
    }
    return s;
}

void sfree(stack *s) {
    for (int i = 0; i < s->capac; i++) {
        free((s->args)[i]);
    }
    free(s->args);
    free(s);
} 

void push(stack *s, char *arg) {
    if (s->len >= s->capac) {
        s->capac *= 2;
        s->args = realloc(s->args, (s->capac * sizeof(char *)));
    }
    s->args[s->len] = malloc(sizeof(char) * TOKLIM);
    char *p = s->args[s->len];
    int i = 0;
    while (arg[i] != '\0') {
        *(p + i) = arg[i];
        i++;
    }
    *(p + i) = '\0';
    s->len++;
}

void pop(stack *s) {
    free(s->args[s->len - 1]);
    s->args[s->len - 1] = NULL;
    s->len--;
}

void pstack(stack *s) {
    printf("\n");
    for (int i = 0; i < s->len; i++) {
        printf("%s  ", s->args[i]);
    }
    printf("\n");
}

