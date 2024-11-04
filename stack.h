#ifndef STACK_H
#define STACK_H

#include "node.h"

#include <stdbool.h>

typedef struct {
    Node *top;
    int length;
} Stack;

int stack_init(Stack **const stack);

int stack_free(Stack **const stack);

int stack_length(Stack *const stack, int *const length);

int stack_is_empty(const Stack *const stack, bool *const is_empty);

int stack_make_empty(Stack *const stack);

int stack_top(Stack *const stack, int *const data);

int stack_push(Stack *const stack, int *const data);

int stack_pop(Stack *const stack, int *const data);

int stack_print(Stack *const stack);

#endif