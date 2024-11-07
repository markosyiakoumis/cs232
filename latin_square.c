#include "latin_square.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef DEBUG_LATIN_SQUARE
#include <assert.h>
int main(void) {
    printf("Initializing a 3x3 latin square...\n");
    LatinSquare *latin_square = NULL;
    latin_square_init(&latin_square, 3);
    latin_square_print(latin_square);

    printf("Executing 1,2 = -2...\n");
    latin_square_insert(latin_square, 0, 1, -2);
    latin_square_print(latin_square);

    printf("Executing 2,1 = -2...\n");
    latin_square_insert(latin_square, 1, 0, -2);
    latin_square_print(latin_square);

    // printf("Executing 2,1 = -2...\n");
    // latin_square_insert(latin_square, 1, 0, -2);
    // latin_square_print(latin_square);

    // printf("Testing latin_square_copy\n");
    // LatinSquare *copied_square=NULL;
    // if (latin_square_copy(latin_square, &copied_square) == EXIT_SUCCESS) {
    //     printf("Copy successfull,printing the copied square:\n");
    //     latin_square_print(copied_square);
    //     latin_square_insert(copied_square,2,2,1);
    //     latin_square_print(copied_square);
    //     latin_square_print(latin_square);
        
    // } else {
    //     printf("Copy failed.\n");
    // }

    printf("Solving the latin square...\n");
    latin_square_solve(latin_square);
    return EXIT_SUCCESS;
}
#endif

static
bool check_bounds(LatinSquare *latin_square, int const row, int const column, int const value) {
    if (row > latin_square -> size - 1 || column > latin_square -> size - 1 || abs(value) > latin_square -> size) {
        printf("Error: i,j or val are outside the allowed range [1..%d]\n", latin_square -> size);
        return false;
    }

    return true;
}

static
bool check_occupation(LatinSquare *latin_square, int const row, int const column) {
    if (latin_square -> square[row][column] != 0) {
        printf("Error: cell is already occupied!\n");
        return false;
    }

    return true;
}

static
bool check_valid_insert(LatinSquare *latin_square, int const row, int const column, int const value) {
    for (int index = 0; index < latin_square -> size; index++) {
        if (abs(latin_square -> square[index][column]) == abs(value) || abs(latin_square -> square[row][index]) == abs(value)) {
            printf("Error: illegal value insertion!\n");
            return false;
        }
    }

    return true;
}

static
bool check_valid_clear(LatinSquare *latin_square, int const row, int const column) {
    if (latin_square -> square[row][column] < 0) {
        printf("Error: illegal to clear cell!\n");
        return false;
    }

    return true;
}

static
void print_horizontal_border(int size) {
    for (int counter = 1; counter <= size; counter++) {
        printf("+-----");
    }
    printf("+\n");
}

int latin_square_init(LatinSquare **const latin_square, int const size) {
    if (*latin_square) {
        return EXIT_FAILURE;
    }
    *latin_square = (LatinSquare *)malloc(1 * sizeof(LatinSquare));
    if (!*latin_square) {
        return EXIT_FAILURE;
    }
    (*latin_square) -> size = size;

    (*latin_square) -> square = (int **)malloc(size * sizeof(int *));
    if (!(*latin_square) -> square) {
        return EXIT_FAILURE;
    }

    for (int row_index = 0; row_index < size; row_index++) {
        (*latin_square) -> square[row_index] = (int *)malloc(size * sizeof(int));
        if (!(*latin_square) -> square[row_index]) {
            return EXIT_FAILURE;
        }
        for (int column_index = 0; column_index < size; column_index++) {
            (*latin_square) -> square[row_index][column_index] = 0;
        }
    }
    return EXIT_SUCCESS;
}

int latin_square_free(LatinSquare **const latin_square) {
    if (!*latin_square) {
        return EXIT_FAILURE; 
    }
    for (int row_index = 0; row_index < (*latin_square) -> size; row_index++) {
        free((*latin_square) -> square[row_index]);
        (*latin_square) -> square[row_index] = NULL;
    }
    free((*latin_square) -> square);
    (*latin_square) -> square = NULL;

    free(*latin_square);
    *latin_square = NULL;
    
    return EXIT_SUCCESS;
}
int latin_square_copy(LatinSquare *const source, LatinSquare **const destination) {
    if (!source) {
        perror("Source latin square is not initialized!");
        return EXIT_FAILURE;
    } else if (*destination) {
        perror("Destination latin square is already initialized!");
        return EXIT_FAILURE;
    }

    latin_square_init(destination, source -> size);
    for(int row_index = 0; row_index < (*destination) -> size; row_index++) {
        for (int column_index = 0; column_index < (*destination) -> size; column_index++) {
            (*destination) -> square[row_index][column_index] = source -> square[row_index][column_index];
        }
    }

    return EXIT_SUCCESS;
}
int latin_square_insert(LatinSquare *latin_square, int const row, int const column, int const value) {
    if (!latin_square) {
        return EXIT_FAILURE;
    }

    if (!check_bounds(latin_square, row, column, value)) {
        return EXIT_FAILURE;
    } else if (!check_occupation(latin_square, row, column)) {
        return EXIT_FAILURE;
    } else if (!check_valid_insert(latin_square, row, column, value)) {
        return EXIT_FAILURE;
    }
    latin_square -> square[row][column] = value;

    return EXIT_SUCCESS;
}

int latin_square_clear(LatinSquare *latin_square, int const row, int const column) {
    if (!latin_square) {
        return EXIT_FAILURE;
    }

    if (!check_bounds(latin_square, row, column, 0)) {
        return EXIT_FAILURE;
    } else if (!check_valid_clear(latin_square, row, column)) {
        return EXIT_FAILURE;
    }
    latin_square -> square[row][column] = 0;

    return EXIT_SUCCESS;
}
int latin_square_solve(LatinSquare *latin_square) {
    if (!latin_square) {
        return EXIT_FAILURE;
    }

    Stack *stack = NULL;
    stack_init(&stack);
    stack_push(stack, latin_square, 0, 0, 0);  // Start at cell (0,0) with value 0
    
    bool is_empty = false;
    bool is_solved = false;
    int push_counter = 0;
    int pop_counter = 0;

    while (!is_empty && !is_solved) {
        LatinSquare *top_latin_square;
        int top_row, top_column, top_value;
        stack_top(stack, &top_latin_square, &top_row, &top_column, &top_value);

        LatinSquare *current_latin_square = NULL;
        latin_square_copy(top_latin_square, &current_latin_square);

        bool found_empty_cell = false;

        for (int row_index = top_row; row_index < current_latin_square->size; row_index++) {
            int column_index = (row_index == top_row) ? top_column : 0;

            for (; column_index < current_latin_square->size; column_index++) {
                if (current_latin_square->square[row_index][column_index] == 0) {
                    found_empty_cell = true;

                    int value = (row_index == top_row && column_index == top_column) ? top_value + 1 : 1;
                    bool value_found = false;

                    while (value <= current_latin_square->size) {
                        if (latin_square_insert(current_latin_square, row_index, column_index, value) == EXIT_SUCCESS) {
                            value_found = true;
                            break;
                        }
                        value++;
                    }

                    if (value_found) {
                        push_counter++;
                        stack_push(stack, current_latin_square, row_index, column_index, value);
                        printf("PUSH: STEP %d\n", push_counter + pop_counter);
                        latin_square_print(current_latin_square);
                    } else {
                        latin_square_free(&current_latin_square);
                        current_latin_square=NULL;
                        int popped_row, popped_column, popped_value;
                        stack_pop(stack, NULL, &popped_row, &popped_column, &popped_value);
                        stack_is_empty(stack, &is_empty);
                        if (!is_empty) {
                            stack->top->row = popped_row;
                            stack->top->column = popped_column;
                            stack->top->value = popped_value;
                        }
                        pop_counter++;
                        printf("POP: STEP %d\n", push_counter + pop_counter);
                    }
                    break;
                  
                }
            }
            if (found_empty_cell) break;
        }

        if (!found_empty_cell) {
            latin_square_free(&current_latin_square);
                        current_latin_square=NULL;
            is_solved = true;
            printf("SOLVED\n");
        }
        stack_is_empty(stack, &is_empty);
    }
       
        printf("PUSH NUM:%d \n",push_counter);
        printf("POP  NUM:%d \n",pop_counter);
    stack_free(&stack);
    return EXIT_SUCCESS;
}


int latin_square_print(LatinSquare *const latin_square) {
    if (!latin_square) {
        return EXIT_FAILURE;
    }

    for (int row_index = 0; row_index < latin_square -> size; row_index++) {
        print_horizontal_border(latin_square -> size);
        for (int column_index = 0; column_index < latin_square -> size; column_index++) {
            int temporary = abs(latin_square -> square[row_index][column_index]);
            int digits = temporary == 0 ? 1 : 0;
            while (temporary != 0) {
                digits++;
                temporary /= 10;
            }

            printf("|");
            if (latin_square -> square[row_index][column_index] >= 0) {
                for (int space_counter = 0; space_counter < 3 - digits; space_counter++) {
                    printf(" ");
                }
                printf("%d", latin_square -> square[row_index][column_index]);
                for (int space_counter = 0; space_counter < 2; space_counter++) {
                    printf(" ");
                }
            } else {
                for (int space_counter = 0; space_counter < 3 - digits - 1; space_counter++) {
                    printf(" ");
                }
                printf("(%d)", latin_square -> square[row_index][column_index] * -1);
                for (int space_counter = 0; space_counter < 2 - 1; space_counter++) {
                    printf(" ");
                }
            }
        }
        printf("|\n");
    }
    print_horizontal_border(latin_square -> size);

    return EXIT_SUCCESS;
}