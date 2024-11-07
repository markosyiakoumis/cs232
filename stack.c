#include "stack.h"

#include <stdlib.h>
#ifdef DEBUG_STACK
#include <stdio.h>
#include <assert.h>

int main(void) {
    printf("Initializing a stack...\n");
    Stack *stack = NULL;
    stack_init(&stack);

    printf("Initializing a 3x3 latin square...\n");
    LatinSquare *latin_square = NULL;
    latin_square_init(&latin_square, 3);
    latin_square_print(latin_square);

    printf("Executing 1,2 = -2...\n");
    latin_square_insert(latin_square, 0, 1, -2);
    latin_square_print(latin_square);

    printf("Pushing the latin square to the stack...\n");
    stack_push(stack, latin_square, 0, 0, 0);
    stack_print(stack);

    stack_free(&stack);
    return EXIT_SUCCESS;
}
#endif

int stack_init(Stack **const stack) {
    if (*stack) {
        return EXIT_FAILURE;
    }

    *stack = (Stack *)malloc(1 * sizeof(Stack));
    if (!*stack) {
        return EXIT_FAILURE;
    }
    (*stack) -> size = 0;

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
    *is_empty = stack -> size == 0 ? true : false;

    return EXIT_SUCCESS;
}

int stack_make_empty(Stack *const stack) {
    if (!stack) {
        return EXIT_FAILURE;
    }

    while (stack -> size > 0) {
        stack_pop(stack, NULL, NULL, NULL, NULL);
    }

    return EXIT_SUCCESS;
}

int stack_top(Stack *const stack, LatinSquare **latin_square, int *const row, int *const column, int *const value) {
    if (!stack) {
        return EXIT_FAILURE;
    } else if (stack -> size == 0) {
        return EXIT_FAILURE;
    }

    if (latin_square) {
        *latin_square = stack -> top -> latin_square;
    }
    if (row) {
        *row = stack -> top -> row;
    }
    if (column) {
        *column = stack -> top -> column;
    }
    if (value) {
        *value = stack -> top -> value;
    }
    return EXIT_SUCCESS;
}

int stack_push(Stack *const stack, LatinSquare *latin_square, const int row, const int column, const int value) {
    if (!stack) {
        return EXIT_FAILURE;
    }

    Node *node = NULL;
    node_init(&node, latin_square, row, column, value, NULL);    

    if (stack -> size > 0) {
        node -> next = stack -> top;
    }
    stack -> top = node;
    (stack -> size)++;
    

    return EXIT_SUCCESS;
}

int stack_pop(Stack *const stack, LatinSquare **latin_square, int *const row, int *const column, int *const value) {
    stack_top(stack, latin_square, row, column, value);
    
    Node *old_top = stack -> top;
    stack -> top = stack -> top -> next;
    node_free(&old_top);
    (stack -> size)--;
    
    return EXIT_SUCCESS;
}

int stack_print(Stack *const stack) {
    if (!stack) {
        return EXIT_FAILURE;
    }

    Node *node = stack -> top;
    while (node) {
        node_print(node);
        node = node -> next;
    }

    return EXIT_SUCCESS;
}