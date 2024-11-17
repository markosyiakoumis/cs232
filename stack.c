#include "stack.h"

#include <stdlib.h>
#ifdef DEBUG_STACK
#include <stdio.h>
#include <assert.h>

int main(void) {
      // Step 1: Initialize the stack
    printf("Initializing a stack...\n");
    Stack *stack = NULL;
    int result = stack_init(&stack);
    assert(result == EXIT_SUCCESS && "Stack initialization failed.");
    assert(stack != NULL && "Stack pointer should not be NULL after initialization.");
    assert(stack->size == 0 && "Stack size should be 0 after initialization.");

    // Step 2: Create and initialize a 3x3 Latin Square
    printf("Initializing a 3x3 Latin Square...\n");
    LatinSquare *latin_square = NULL;
    result = latin_square_init(&latin_square, 3);
    assert(result == EXIT_SUCCESS && "Latin square initialization failed.");

    // Step 3: Insert values into the Latin Square
    printf("Inserting values into the Latin Square...\n");
    result = latin_square_insert(latin_square, 0, 1, -2);
    assert(result == EXIT_SUCCESS && "Failed to insert value into Latin Square.");
    latin_square_print(latin_square);

    // Step 4: Push the Latin Square to the stack
    printf("Pushing the Latin Square to the stack...\n");
    result = stack_push(stack, latin_square, 0, 0, 0);
    assert(result == EXIT_SUCCESS && "Failed to push Latin Square to stack.");
    assert(stack->size == 1 && "Stack size should be 1 after pushing.");

    // Step 5: Check if the stack is empty (it should not be)
    bool is_empty = false;
    result = stack_is_empty(stack, &is_empty);
    assert(result == EXIT_SUCCESS && "Failed to check if stack is empty.");
    assert(is_empty == false && "Stack should not be empty.");

    // Step 6: Pop the top element from the stack
    printf("Popping the top element from the stack...\n");
    LatinSquare *popped_latin_square = NULL;
    int row = 0, column = 0, value = 0;
    result = stack_pop(stack, &popped_latin_square, &row, &column, &value);
    assert(result == EXIT_SUCCESS && "Failed to pop from stack.");
    assert(stack->size == 0 && "Stack size should be 0 after popping.");
    assert(popped_latin_square == latin_square && "Popped Latin Square does not match the pushed one.");
    assert(row == 0 && column == 0 && value == 0 && "Popped values do not match the expected ones.");

    // Step 7: Ensure that the stack is empty after popping
    result = stack_is_empty(stack, &is_empty);
    assert(result == EXIT_SUCCESS && "Failed to check if stack is empty after popping.");
    assert(is_empty == true && "Stack should be empty after popping all elements.");

    // Step 8: Free the stack memory
    result = stack_free(&stack);
    assert(result == EXIT_SUCCESS && "Failed to free the stack.");
    assert(stack == NULL && "Stack pointer should be NULL after freeing.");

    printf("All assertions passed successfully.\n");

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