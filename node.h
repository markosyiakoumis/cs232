#ifndef NODE_H
#define NODE_H

typedef struct node {
    int **square;
    int row;
    int column;
    struct node *next;
} Node;

int node_init(Node **node, int **square, const int row, const int column, Node *next);

int node_free(Node **node);

#endif