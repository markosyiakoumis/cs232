#ifndef NODE_H
#define NODE_H

#include "latin_square.h"

typedef struct node {
    LatinSquare *latin_square;
    int row;
    int column;
    int value;
    struct node *next;
} Node;

int node_init(Node **node, LatinSquare **latin_square, const int row, const int column, const int value, Node *next);

int node_free(Node **node);

int node_print(Node *node);

#endif