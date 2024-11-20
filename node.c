#include "node.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG_NODE
#include <assert.h>
int main(void) {
    printf("Initializing a node...\n");

    // Create a dummy LatinSquare for testing purposes
    LatinSquare *latin_square = NULL;
    latin_square_init(&latin_square, 3);  // Assuming this function initializes the LatinSquare

    Node *node = NULL;
    assert(node_init(&node, latin_square, 1, 2, 5, NULL) == EXIT_SUCCESS);  // Initialize node

    // Assert the node has been properly initialized
    assert(node != NULL);  // Ensure node is not NULL
    assert(node->latin_square == latin_square);  // Check that the latin_square pointer matches
    assert(node->row == 1);  // Check row value
    assert(node->column == 2);  // Check column value
    assert(node->value == 5);  // Check value stored in the node
    assert(node->next == NULL);  // Check that next pointer is NULL (since no other node is linked)

    printf("Node initialized successfully!\n");

    // Test printing the node
    printf("Printing the node...\n");
    assert(node_print(node) == EXIT_SUCCESS);  // Assert that the node prints successfully

    // Test freeing the node
    printf("Freeing the node...\n");
    assert(node_free(&node) == EXIT_SUCCESS);  // Free the node
    assert(node == NULL);  // After freeing, node should be NULL

    // Test freeing a NULL node
    printf("Testing freeing a NULL node...\n");
    assert(node_free(&node) == EXIT_FAILURE);  // Trying to free a NULL node should fail

    printf("All tests passed successfully!\n");

    
    return EXIT_SUCCESS;
}
#endif

int node_init(Node **node, LatinSquare *latin_square, const int row, const int column, const int value, Node *next) {
    if (*node) {
        return EXIT_FAILURE;
    }

    *node = (Node *)malloc(1 * sizeof(Node));
    if (!node) {
        return EXIT_FAILURE;
    }

    (*node) -> latin_square = latin_square;
    (*node) -> row = row;
    (*node) -> column = column;
    (*node) -> value = value;
    (*node) -> next = next;

    return EXIT_SUCCESS;
}

int node_free(Node **node) {
    if (!*node) {
        return EXIT_FAILURE;
    }

    latin_square_free(&(*node) -> latin_square);
    (*node) -> latin_square = NULL;
    free(*node);
    *node = NULL;

    return EXIT_SUCCESS;
}

int node_print(Node *node) {
    if (!node) {
        return EXIT_FAILURE;
    }

    latin_square_print(node -> latin_square);
    printf("%d %d %d\n", node -> row, node -> column, node -> value);

    return EXIT_SUCCESS;
}