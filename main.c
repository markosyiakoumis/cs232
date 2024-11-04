#include "latin_square.h"
#include "file_handler.h"
//#include "latin_square_solver.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, int argv) {
    if (argc != 2) {
        printf("Invalid syntax!");
        return EXIT_FAILURE;
    }

    LatinSquare *latin_square = NULL;
    read_latin_square(argv[1], &latin_square);

    return EXIT_SUCCESS;
}