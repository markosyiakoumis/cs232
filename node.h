#ifndef NODE_H
#define NODE_H

#include "latin_square.h"

typedef struct node {
    LatinSquare *latin_square;
    int row;
    int column;
    struct node *next;
} Node;

int node_init(Node **node, LatinSquare **latin_square, const int row, const int column, Node *next);

int node_free(Node **node);

#endif