#include "node.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG_NODE
int main(void) {
    printf("Intializing a node...\n");
    Node *node = NULL;
    int **square = (int **)malloc(3 * sizeof(int *));
    node_init(&node, square, 1, 2, NULL);

    printf("Freeing the node...\n");
    node_free(&node);

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

    free((*node) -> latin_square);
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