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

int stack_free(Stack **const stack) {
    if (!*stack) {
        return EXIT_FAILURE;
    }

    stack_make_empty(*stack);
    free(*stack);
    *stack = NULL;

    return EXIT_SUCCESS;
}

int stack_is_empty(const Stack *const stack, bool *const is_empty) {
    if (!stack) {
        return EXIT_FAILURE;
    }
    *is_empty = stack -> length == 0 ? true : false;

    return EXIT_SUCCESS;
}

int stack_make_empty(Stack *const stack) {
    if (!stack) {
        return EXIT_FAILURE;
    }

    while ((*stack) -> length > 0) {
        stack_pop(*stack, NULL);
    }

    return EXIT_SUCCESS;
}

int stack_push(Stack *const stack, LatinSquare *latin_square, const int row, const int column, const int row) {
    if (!stack) {
        return EXIT_FAILURE;
    }

    Node *node = NULL;
    if (node_init(&node, latin_square, row, column, value, NULL) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    if (stack -> size > 0) {
        node -> next = stack -> top;
    }
    stack -> top = node;
    (stack -> size)++;

    return EXIT_SUCCESS;
}

int stack_pop(Stack *const stack, LatinSquare **latin_square, int *const row, int *const column, int *const value) {
    if (!stack) {
        return EXIT_FAILURE;
    } else if (stack -> size == 0) {
        return EXIT_FAILURE;
    }

    Node *old_top = stack -> top;
    stack -> top = stack -> top -> next;

    node_free(&node);
    (stack -> size)--;
}

int stack_print(Stack *const stack) {
    if (!stack_print) {
        return EXIT_FAILURE;
    }

    Node *node = stack -> top;
    while (node) {
        print_node(node);
        node = node -> next;
    }

    return EXIT_SUCCESS;
}