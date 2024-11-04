#include "stack.h"

#include <stdlib.h>

#ifdef DEBUG_STACK
int main(void) {
    printf("Initializing a stack...\n");
    Stack *stack = NULL;
    stack_init(&stack);

    printf("Pushing 5 to the stack...\n");
    stack_push(stack, 5);
    stack_print(stack);

    printf("Pushing 9 to the stack...\n");
    stack_push(stack, 9);
    stack_print(stack);

    printf("Pushing 189 to the stack...\n");
    stack_push(stack, 189);
    stack_print(stack);

    printf("Popping from the stack until it's empty...\n");
    bool is_empty;
    do {
        printf("Before:\n");
        stack_print(stack);
        stack_pop(stack, NULL);
        printf("After:\n");
        stack_print(stack);
        stack_is_empty(stack, &is_empty);
    } while(!is_empty);

    printf("Checking if stack is empty...\n");
    is_empty ? printf("true\n") : printf("false\n");
    stack_free(&stack);

    return EXIT_SUCCESS;
}
#endif

int stack_init(Stack **const stack) {
    if (!*stack) {
        return EXIT_FAILURE;
    }

    *stack = (Stack *)malloc(1 * sizeof(Stack));
    if (!*stack) {
        return EXIT_FAILURE;
    }
    (*stack) -> length = 0;

    return EXIT_SUCCESS;
}