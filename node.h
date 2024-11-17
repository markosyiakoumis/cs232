#ifndef NODE_H
#define NODE_H

#include "latin_square.h"

/**
 * @brief A structure representing a node in a linked list.
 * 
 * Each node stores a reference to a `LatinSquare`, the position (row, column), 
 * a value for that position, and a pointer to the next node in the list.
 */
typedef struct node {
    LatinSquare *latin_square; /**< Pointer to the associated Latin Square. */
    int row;                   /**< Row position of the value in the Latin Square. */
    int column;                /**< Column position of the value in the Latin Square. */
    int value;                 /**< The value to be stored in the node. */
    struct node *next;         /**< Pointer to the next node in the linked list. */
} Node;

/**
 * @brief Initializes a new node.
 * 
 * This function allocates memory for a new node, sets its values, and 
 * links it to the provided LatinSquare.
 * 
 * @param node A pointer to the node pointer that will hold the initialized node.
 * @param latin_square The LatinSquare associated with this node.
 * @param row The row index for the node.
 * @param column The column index for the node.
 * @param value The value to be stored at the given position in the Latin Square.
 * @param next A pointer to the next node in the linked list (can be NULL).
 * @return EXIT_SUCCESS if the node is successfully initialized, 
 *         EXIT_FAILURE if memory allocation fails or node is already initialized.
 */
int node_init(Node **node, LatinSquare *latin_square, const int row, const int column, const int value, Node *next);

/**
 * @brief Frees the memory associated with a node.
 * 
 * This function frees the memory allocated for the node and the associated 
 * LatinSquare (if applicable). After calling this function, the node pointer
 * is set to NULL.
 * 
 * @param node A pointer to the node pointer that needs to be freed.
 * @return EXIT_SUCCESS if the node is successfully freed, EXIT_FAILURE if node is NULL.
 */
int node_free(Node **node);

/**
 * @brief Prints the content of the node.
 * 
 * This function prints the associated Latin Square, followed by the row, column, 
 * and value of the node.
 * 
 * @param node The node whose contents are to be printed.
 * @return EXIT_SUCCESS if the node is successfully printed, 
 *         EXIT_FAILURE if the node is NULL.
 */
int node_print(Node *node);

#endif
