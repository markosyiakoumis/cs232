#include "latin_square.h"
#include "file_handler.h"
//#include "latin_square_solver.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Invalid syntax!");
        return EXIT_FAILURE;
    }
    LatinSquare *latin_square = NULL;
    read_latin_square(argv[1], &latin_square);
    
    if(latin_square_solve(latin_square))
    return EXIT_SUCCESS;
    return EXIT_FAILURE;
}