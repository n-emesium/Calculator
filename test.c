#include "stack.h"

int main() {
    stack *s = create();
    push(s, "10");
    push(s, "20");
    push(s, "+");
    push(s, "*");
    pstack(s);
    pop(s);
    pstack(s);
    sfree(s);
}
