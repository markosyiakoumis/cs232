#ifndef LATIN_SQUARE_H
#define LATIN_SQUARE_H

typedef struct {
    int size;
    int **square;
} LatinSquare;

int latin_square_init(LatinSquare **const latin_square, int const size);

int latin_square_free(LatinSquare **const latin_square);

int latin_square_copy(LatinSquare *const source, LatinSquare **const destination);

int latin_square_insert(LatinSquare *latin_square, int const row, int const column, int const value);

int latin_square_clear(LatinSquare *latin_square, int const row, int const column);

int latin_square_solve(LatinSquare *latin_square);

int latin_square_print(LatinSquare *const latin_square);

#endif