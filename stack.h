#ifndef STACK_H
#define STACK_H

#include "node.h"
#include <stdbool.h>

/**
 * @brief A structure representing a stack.
 * 
 * This stack structure is implemented using a linked list where each node
 * contains a reference to a LatinSquare, along with its associated row, column,
 * and value. The stack has a top pointer to the most recently pushed node and
 * keeps track of its size.
 */
typedef struct {
    Node *top; /**< Pointer to the top node in the stack. */
    int size;  /**< The number of elements in the stack. */
} Stack;

/**
 * @brief Initializes an empty stack.
 * 
 * This function allocates memory for the stack and initializes its properties
 * (top pointer to NULL and size to 0).
 * 
 * @param stack A pointer to the pointer of the stack that needs to be initialized.
 * @return EXIT_SUCCESS if the stack is successfully initialized, 
 *         EXIT_FAILURE if memory allocation fails.
 */
int stack_init(Stack **const stack);

/**
 * @brief Frees the memory associated with the stack.
 * 
 * This function frees all the nodes in the stack and then frees the stack
 * structure itself. After this function is called, the stack pointer is set to NULL.
 * 
 * @param stack A pointer to the pointer of the stack to be freed.
 * @return EXIT_SUCCESS if the stack is successfully freed, 
 *         EXIT_FAILURE if the stack pointer is NULL.
 */
int stack_free(Stack **const stack);

/**
 * @brief Checks if the stack is empty.
 * 
 * This function checks whether the stack is empty by verifying if the size
 * of the stack is 0.
 * 
 * @param stack A pointer to the stack to be checked.
 * @param is_empty A pointer to a boolean value where the result will be stored.
 *                 The value will be set to true if the stack is empty, false otherwise.
 * @return EXIT_SUCCESS if the check is successful, 
 *         EXIT_FAILURE if the stack pointer is NULL.
 */
int stack_is_empty(const Stack *const stack, bool *const is_empty);

/**
 * @brief Removes all elements from the stack.
 * 
 * This function removes all elements from the stack, making the stack empty.
 * It calls the `stack_pop` function repeatedly until the stack size is 0.
 * 
 * @param stack A pointer to the stack to be emptied.
 * @return EXIT_SUCCESS if the stack is successfully emptied, 
 *         EXIT_FAILURE if the stack pointer is NULL.
 */
int stack_make_empty(Stack *const stack);

/**
 * @brief Retrieves the top element of the stack.
 * 
 * This function retrieves the top element of the stack without removing it. The
 * details of the top element (LatinSquare, row, column, and value) are stored
 * in the provided parameters.
 * 
 * @param stack A pointer to the stack from which the top element is retrieved.
 * @param latin_square A pointer to store the retrieved LatinSquare from the top node.
 * @param row A pointer to store the row of the top element.
 * @param column A pointer to store the column of the top element.
 * @param value A pointer to store the value of the top element.
 * @return EXIT_SUCCESS if the top element is successfully retrieved, 
 *         EXIT_FAILURE if the stack is empty or the stack pointer is NULL.
 */
int stack_top(Stack *const stack, LatinSquare **latin_square, int *const row, int *const column, int *const value);

/**
 * @brief Pushes an element onto the stack.
 * 
 * This function creates a new node and adds it to the top of the stack. The node
 * stores a reference to a LatinSquare along with its associated row, column, and value.
 * 
 * @param stack A pointer to the stack onto which the element will be pushed.
 * @param latin_square A pointer to the LatinSquare to be stored in the new node.
 * @param row The row of the value to be stored in the node.
 * @param column The column of the value to be stored in the node.
 * @param value The value to be stored in the node.
 * @return EXIT_SUCCESS if the element is successfully pushed onto the stack, 
 *         EXIT_FAILURE if memory allocation for the node fails.
 */
int stack_push(Stack *const stack, LatinSquare *latin_square, const int row, const int column, const int value);

/**
 * @brief Pops the top element from the stack.
 * 
 * This function removes the top element from the stack and stores its details 
 * (LatinSquare, row, column, value) in the provided parameters.
 * 
 * @param stack A pointer to the stack from which the element will be popped.
 * @param latin_square A pointer to store the LatinSquare of the popped element.
 * @param row A pointer to store the row of the popped element.
 * @param column A pointer to store the column of the popped element.
 * @param value A pointer to store the value of the popped element.
 * @return EXIT_SUCCESS if the element is successfully popped from the stack, 
 *         EXIT_FAILURE if the stack is empty or the stack pointer is NULL.
 */
int stack_pop(Stack *const stack, LatinSquare **latin_square, int *const row, int *const column, int *const value);

/**
 * @brief Prints all elements in the stack.
 * 
 * This function prints the details of each element in the stack, starting from
 * the top element down to the bottom.
 * 
 * @param stack A pointer to the stack to be printed.
 * @return EXIT_SUCCESS if the stack is successfully printed, 
 *         EXIT_FAILURE if the stack pointer is NULL.
 */
int stack_print(Stack *const stack);

#endif
