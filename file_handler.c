#include "file_handler.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#ifdef DEBUG_FILE_HANDLER
int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Invalid syntax!");
        return EXIT_FAILURE;
    }
    LatinSquare *latin_square = NULL;
    read_latin_square(argv[1], &latin_square);
    latin_square_print(latin_square);
    latin_square_free(&latin_square);
    return EXIT_SUCCESS;
}
#endif

int read_latin_square(char *const file_name, LatinSquare **latin_square) {
    FILE *file_pointer = fopen(file_name, "r");
    if (!file_pointer) {
        return EXIT_FAILURE;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file_pointer);
    int size = 0;
    for (int index = 0; index < strlen(buffer) - 1; index++) {
        if (isdigit(buffer[index])) {
            size = size * 10 + buffer[index] - '0';
        } else {
            perror("Invalid malakia sto proto line");
            fclose(file_pointer);
            return EXIT_FAILURE;
        }
    }

    int row_index = 0;
    latin_square_init(latin_square, size);
    while (fgets(buffer, sizeof(buffer), file_pointer)) {
        int value = 0;
        int column_index = 0;
        for (int index = 0; index < strlen(buffer) - 1; index++) {
            if (buffer[index] == '-') {
                if (index >= strlen(buffer) - 1) {
                    //SASTAAA
                    return EXIT_FAILURE;
                }
                index++;
            }
            if (isdigit(buffer[index])) {
                if (buffer[index] == '0' && (index < strlen(buffer) - 1 || !isdigit(buffer[index + 1]))) {
                    continue;
                }
                value = value * 10 + buffer[index] - '0';
                if (index > 0 && buffer[index - 1] == '-') {
                    value *= -1;
                }
            } else if (buffer[index] == ' ') {
                if (value != 0) {
                    latin_square_insert(*latin_square, row_index, column_index, value);
                }
                
                value = 0;
                column_index++;
            } else {
                printf("CHAR %d", (int)buffer[index]);
                perror("Invalid malakia sto file");
                fclose(file_pointer);
                latin_square_free(latin_square);
                return EXIT_FAILURE;
            }
        }
        row_index++;
        if (row_index > size) {
            perror("POLLA PRAMATA sto file");
            fclose(file_pointer);
            latin_square_free(latin_square);
            return EXIT_FAILURE;
        } 
    }

    return EXIT_SUCCESS;
}