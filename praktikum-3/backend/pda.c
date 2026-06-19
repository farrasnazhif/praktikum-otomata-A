#include <stdio.h>
#include <string.h>

int main() {
    char input[1024];
    char stack[1024];
    int top = 0;
    int step = 0;
    int state = 0; // 0=q0, 1=q1, 2=q2
    int pos = 0;
    int len;

    fgets(input, sizeof(input), stdin);
    len = strlen(input);
    if (len > 0 && input[len-1] == '\n') input[--len] = '\0';

    stack[top] = 'Z';

    // print initial step
    printf("STEP %d q%d %s %.*s\n", step++, state, len > 0 ? input : "ε", top+1, stack);

    while (pos < len) {
        if (state == 0) {
            if (input[pos] == 'a') {
                stack[++top] = 'A';
                pos++;
                printf("STEP %d q0 %s ", step++, pos < len ? input+pos : "ε");
                for (int i = top; i >= 0; i--) putchar(stack[i]);
                putchar('\n');
            } else if (input[pos] == 'b') {
                state = 1;
                if (top > 0 && stack[top] == 'A') {
                    top--;
                    pos++;
                    printf("STEP %d q1 %s ", step++, pos < len ? input+pos : "ε");
                    for (int i = top; i >= 0; i--) putchar(stack[i]);
                    putchar('\n');
                } else {
                    printf("STEP %d q1 %s ", step++, input+pos);
                    for (int i = top; i >= 0; i--) putchar(stack[i]);
                    putchar('\n');
                    printf("REJECTED\n");
                    return 0;
                }
            } else {
                printf("REJECTED\n");
                return 0;
            }
        } else if (state == 1) {
            if (input[pos] == 'b') {
                if (top > 0 && stack[top] == 'A') {
                    top--;
                    pos++;
                    printf("STEP %d q1 %s ", step++, pos < len ? input+pos : "ε");
                    for (int i = top; i >= 0; i--) putchar(stack[i]);
                    putchar('\n');
                } else {
                    printf("STEP %d q1 %s ", step++, input+pos);
                    for (int i = top; i >= 0; i--) putchar(stack[i]);
                    putchar('\n');
                    printf("REJECTED\n");
                    return 0;
                }
            } else {
                printf("REJECTED\n");
                return 0;
            }
        }
    }

    if (top == 0 && stack[0] == 'Z' && state == 1) {
        state = 2;
        printf("STEP %d q2 ε Z\n", step++);
        printf("ACCEPTED\n");
    } else {
        printf("REJECTED\n");
    }
    return 0;
}
