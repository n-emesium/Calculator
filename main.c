#include "stack.h"
#include "calculator.h"
int main(int argc, char *args[]) { 
    stack *s = create();
    char *formatted = pformat(args[1]);
    feed(s, formatted);
    free(formatted);
    //pstack(s);
    stack *res = parse(s);
    //char c[] = {'1', '2', '.', '3', '4'};
    //char *pt = c;
    //printf("%lf     ", cformat(pt));
    //pstack(res);
    //printf("The RPN conversion is: \n");
    //pstack(res);
    //printf("%lf    ", cformat("93.31"));
    printf(" = %lf\n", eval(res));
    sfree(s); 
    if (res) {
        sfree(res);
    }
    return 0;
}