#ifndef STACK_H
#define STACK_H

#include "node.h"

#include <stdbool.h>

typedef struct {
    Node *top;
    int size;
} Stack;

int stack_init(Stack **const stack);

int stack_free(Stack **const stack);

int stack_is_empty(const Stack *const stack, bool *const is_empty);

int stack_make_empty(Stack *const stack);

int stack_top(Stack *const stack, LatinSquare **latin_square, int *const row, int *const column, int *const value);

int stack_push(Stack *const stack, LatinSquare *latin_square, const int row, const int column, const int value);

int stack_pop(Stack *const stack, LatinSquare **latin_square, int *const row, int *const column, int *const value);

int stack_print(Stack *const stack);

#endif