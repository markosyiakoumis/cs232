#include "latin_square.h"
#include "file_handler.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Invalid syntax!");
        return EXIT_FAILURE;
    }

    LatinSquare *latin_square = NULL;
    if (read_latin_square(argv[1], &latin_square) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    
    if (latin_square_solve(latin_square) == EXIT_FAILURE) {
        latin_square_free(&latin_square);
        return EXIT_FAILURE;
    }
    
    latin_square_free(&latin_square);
    return EXIT_SUCCESS;
}