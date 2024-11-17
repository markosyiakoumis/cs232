#include "latin_square.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef DEBUG_LATIN_SQUARE
#include <assert.h>
int main(void) {
      printf("Starting tests for Latin Square...\n");

    LatinSquare *latin_square = NULL;

    // Test 1: Initialization
    printf("Test 1: Initializing a 3x3 Latin Square...\n");
    assert(latin_square_init(&latin_square, 3) == EXIT_SUCCESS);
    assert(latin_square != NULL);
    assert(latin_square->size == 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(latin_square->square[i][j] == 0);
        }
    }
    printf("Test 1 Passed!\n");

    // Test 2: Insert valid values
    printf("Test 2: Inserting valid values...\n");
    assert(latin_square_insert(latin_square, 0, 0, 1) == EXIT_SUCCESS);
    assert(latin_square->square[0][0] == 1);
    assert(latin_square_insert(latin_square, 0, 1, 2) == EXIT_SUCCESS);
    assert(latin_square->square[0][1] == 2);
    printf("Test 2 Passed!\n");

    // Test 3: Insert invalid value (duplicate in row)
    printf("Test 3: Inserting duplicate value in row...\n");
    assert(latin_square_insert(latin_square, 0, 2, 1) == EXIT_FAILURE);
    printf("Test 3 Passed!\n");

    // Test 4: Insert invalid value (out of bounds)
    printf("Test 4: Inserting out-of-bounds value...\n");
    assert(latin_square_insert(latin_square, 0, 3, 1) == EXIT_FAILURE); // Invalid column
    assert(latin_square_insert(latin_square, 3, 0, 1) == EXIT_FAILURE); // Invalid row
    assert(latin_square_insert(latin_square, 0, 0, 5) == EXIT_FAILURE); // Value exceeds size
    printf("Test 4 Passed!\n");

    // Test 5: Clear valid cell
    printf("Test 5: Clearing a valid cell...\n");
    assert(latin_square_clear(latin_square, 0, 1) == EXIT_SUCCESS);
    assert(latin_square->square[0][1] == 0);
    printf("Test 5 Passed!\n");

    // Test 6: Clear invalid cell (fixed cell)
    printf("Test 6: Clearing a fixed cell...\n");
    latin_square->square[0][0] = -1; // Mark cell as fixed
    assert(latin_square_clear(latin_square, 0, 0) == EXIT_FAILURE);
    printf("Test 6 Passed!\n");

    // Test 7: Solve a simple Latin square
    printf("Test 7: Solving a Latin Square...\n");
    latin_square_insert(latin_square, 0, 1, 2);
    latin_square_insert(latin_square, 0, 2, 3);
    assert(latin_square_solve(latin_square) == EXIT_SUCCESS);
    printf("Solved Latin Square:\n");
  
    printf("Test 7 Passed!\n");

    // Test 8: Free the Latin square
    printf("Test 8: Freeing the Latin Square...\n");
    assert(latin_square_free(&latin_square) == EXIT_SUCCESS);
    assert(latin_square == NULL);
    printf("Test 8 Passed!\n");

    printf("All tests passed successfully!\n");
    return EXIT_SUCCESS;
}
#endif

/**
 * @brief Checks whether the given row, column, and value are within the allowed bounds.
 * 
 * This function verifies that the provided row, column, and value are within the 
 * valid range for the Latin Square. The valid range for row and column is [0..size-1], 
 * and the valid range for the value is [1..size].
 * 
 * @param latin_square A pointer to the Latin Square.
 * @param row The row index to check.
 * @param column The column index to check.
 * @param value The value to check.
 * @return true if all parameters are within the allowed bounds, false otherwise.
 */
static
bool check_bounds(LatinSquare *latin_square, int const row, int const column, int const value) {
    if (row > latin_square -> size - 1 || column > latin_square -> size - 1 || abs(value) > latin_square -> size) {
        printf("Error: i,j or val are outside the allowed range [1..%d]\n", latin_square -> size);
        return false;
    }

    return true;
}

/**
 * @brief Checks whether the cell at the given row and column is already occupied.
 * 
 * This function checks if the specified cell in the Latin Square is already occupied 
 * by a non-zero value.
 * 
 * @param latin_square A pointer to the Latin Square.
 * @param row The row index to check.
 * @param column The column index to check.
 * @return true if the cell is unoccupied (value is 0), false otherwise.
 */
static
bool check_occupation(LatinSquare *latin_square, int const row, int const column) {
    if (latin_square -> square[row][column] != 0) {
        printf("Error: cell is already occupied!\n");
        return false;
    }

    return true;
}
/**
 * @brief Validates whether inserting a value into the given cell is allowed.
 * 
 * This function ensures that the value to be inserted into the specified cell 
 * does not violate Latin Square constraints, i.e., no duplicate values 
 * in the row or column.
 * 
 * @param latin_square A pointer to the Latin Square.
 * @param row The row index to check.
 * @param column The column index to check.
 * @param value The value to be inserted.
 * @return true if the insertion is valid, false otherwise.
 */
static
bool check_valid_insert(LatinSquare *latin_square, int const row, int const column, int const value) {
    for (int index = 0; index < latin_square -> size; index++) {
        if (abs(latin_square -> square[index][column]) == abs(value) || abs(latin_square -> square[row][index]) == abs(value)) {
          //  printf("%d %d %d %d \n",row,column,index,value);
            printf("Error: illegal value insertion!\n");
            return false;
        }
    }

    return true;
}
/**
 * @brief Validates whether a value in a cell can be cleared.
 * 
 * This function ensures that a value can only be cleared if it is not a fixed value 
 * (i.e., negative values).
 * 
 * @param latin_square A pointer to the Latin Square.
 * @param row The row index to check.
 * @param column The column index to check.
 * @return true if the cell can be cleared, false otherwise.
 */
static
bool check_valid_clear(LatinSquare *latin_square, int const row, int const column) {
    if (latin_square -> square[row][column] < 0) {
        printf("Error: illegal to clear cell!\n");
        return false;
    }

    return true;
}

/**
 * @brief Prints a horizontal border for the Latin Square grid.
 * 
 * This function prints a horizontal border line with the specified length, 
 * used to separate rows in the printed Latin Square.
 * 
 * @param size The size of the Latin Square (determines the number of columns).
 */
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
    LatinSquare *initial_latin_square = NULL;
    latin_square_copy(latin_square, &initial_latin_square);
    stack_push(stack, initial_latin_square, 0, 0, 0);  // Start at cell (0,0) with value 0
    
    bool is_empty = false;
    bool is_solved = false;
    int push_counter = 0;
    int pop_counter = 0;
        int top_row, top_column, top_value;
        top_row=0,top_column=0,top_value=0;
    while (!is_empty && !is_solved) {
        LatinSquare *top_latin_square;
        stack_top(stack, &top_latin_square, NULL, NULL, NULL);
        LatinSquare *current_latin_square = NULL;
        latin_square_copy(top_latin_square, &current_latin_square);

        bool found_empty_cell = false;

        for (int row_index = top_row; row_index < current_latin_square -> size; row_index++) {
            int column_index = (row_index == top_row) ? top_column : 0;

            for (; column_index < current_latin_square -> size; column_index++) {
                if (current_latin_square -> square[row_index][column_index] == 0) {
                    found_empty_cell = true;

                    int value = (row_index == top_row && column_index == top_column) ? top_value + 1 : 1;
                    while (value <= current_latin_square -> size && latin_square_insert(current_latin_square, row_index, column_index, value) == EXIT_FAILURE) {
                        value++;
                    }

                    if (value <= current_latin_square -> size) {
                        push_counter++;
                        printf("PUSH: STEP %d\n", push_counter + pop_counter);
                        latin_square_print(current_latin_square);

                        stack_push(stack, current_latin_square, row_index, column_index, value);
                    } else {
                        stack_is_empty(stack, &is_empty);
                        if (!is_empty) {
                            pop_counter++;
                            printf("POP: STEP %d\n", push_counter + pop_counter);
                            latin_square_print(current_latin_square);
                            latin_square_free(&current_latin_square);

                            stack_pop(stack, NULL, &top_row, &top_column, &top_value);
                        } else {
                            //
                        }
                    }

                    break;
                }
            }
            if (found_empty_cell) break;
        }

        if (!found_empty_cell) {
            latin_square_free(&current_latin_square);

            is_solved = true;
        }
        stack_is_empty(stack, &is_empty);
    }
       
        printf("PUSH NUM: %d \n",push_counter);
        printf("POP  NUM: %d \n",pop_counter);
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