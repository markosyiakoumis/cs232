#include "file_handler.h"

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#ifdef DEBUG_FILE_HANDLER
int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Invalid syntax!");
        return EXIT_FAILURE;
    }
    LatinSquare *latin_square = NULL;
    if (read_latin_square(argv[1], &latin_square)) {
        return EXIT_FAILURE;
    }
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
            perror("Invalid size found in file!");
            fclose(file_pointer);
            return EXIT_FAILURE;
        }
    }

    latin_square_init(latin_square, size);
    for (int row_index = 0; row_index < size; row_index++) {
        if (!fgets(buffer, sizeof(buffer), file_pointer)) {
            return EXIT_FAILURE;
        }

        int value = 0,
            buffer_index = 0,
            column_index = 0;
        while (buffer_index < strlen(buffer)) {
            if (buffer[buffer_index] == '-') {
                if (buffer_index >= strlen(buffer) - 1 || !isdigit(buffer[buffer_index + 1])) {
                    return EXIT_FAILURE;
                }

                buffer_index++;
            } else if (isdigit(buffer[buffer_index])) {
                value = value * 10 + buffer[buffer_index] - '0';
                value = buffer_index > 0 && buffer[buffer_index - 1] == '-' ? value * -1 : value;

                buffer_index++;
            } else if (buffer[buffer_index] == ' ' || (buffer_index == strlen(buffer) - 1 && buffer[buffer_index] == '\n')) {
                if (value != 0) {
                    if (latin_square_insert(*latin_square, row_index, column_index, value) == EXIT_FAILURE) {
                        perror("File contains invalid values!");
                        fclose(file_pointer);
                        latin_square_free(latin_square);
                    }
                }

                value = 0;
                column_index++;
                buffer_index++;
            } else {
                perror("Invalid file syntax!");
                fclose(file_pointer);
                latin_square_free(latin_square);
                return EXIT_FAILURE;
            }
        }

        if (column_index != size) {
            perror("too few columns found in row");
            fclose(file_pointer);
            latin_square_free(latin_square);
                return EXIT_FAILURE;
        }
    }

    if (fgets(buffer, sizeof(buffer), file_pointer)) {
        perror("File contains more data than expected!");
        fclose(file_pointer);
        latin_square_free(latin_square);
        return EXIT_FAILURE;
    }

    fclose(file_pointer);
    return EXIT_SUCCESS;
}