/**
 * @file latin_square.h
 * @brief Provides functions to initialize, manipulate, and solve Latin squares.
 */

#ifndef LATIN_SQUARE_H
#define LATIN_SQUARE_H

/**
 * @struct LatinSquare
 * @brief Represents a Latin square.
 *
 * A Latin square is a grid of size `size x size` filled with integers such that:
 * - Each integer appears exactly once in each row.
 * - Each integer appears exactly once in each column.
 *
 * The structure contains:
 * - `size`: The size of the Latin square (number of rows/columns).
 * - `square`: A 2D array representing the grid of integers.
 */
typedef struct {
    int size;      /**< The size of the Latin square. */
    int **square;  /**< A pointer to the 2D array representing the Latin square. */
} LatinSquare;

/**
 * @brief Initializes a Latin square of a given size.
 *
 * Allocates memory for a Latin square and sets all cells to 0.
 *
 * @param latin_square Pointer to the Latin square to initialize.
 * @param size The size of the Latin square (number of rows/columns).
 * @return EXIT_SUCCESS if initialization is successful, otherwise EXIT_FAILURE.
 */
int latin_square_init(LatinSquare **const latin_square, int const size);

/**
 * @brief Frees the memory allocated for a Latin square.
 *
 * Deallocates memory and sets the pointer to NULL.
 *
 * @param[in,out] latin_square Pointer to the Latin square to free.
 * @return EXIT_SUCCESS if the operation is successful, otherwise EXIT_FAILURE.
 */
int latin_square_free(LatinSquare **const latin_square);

/**
 * @brief Creates a copy of a Latin square.
 *
 * Allocates memory for a new Latin square and copies the contents of the source Latin square into it.
 *
 * @param source The source Latin square to copy.
 * @param destination Pointer to the destination Latin square.
 * @return EXIT_SUCCESS if the operation is successful, otherwise EXIT_FAILURE.
 */
int latin_square_copy(LatinSquare *const source, LatinSquare **const destination);

/**
 * @brief Inserts a value into a specific cell of a Latin square.
 *
 * Validates the row, column, and value before insertion. Values must be unique in their row and column.
 *
 * @param latin_square Pointer to the Latin square.
 * @param row The row index of the cell (0-based).
 * @param column The column index of the cell (0-based).
 * @param value The value to insert (positive for fixed values, negative for mutable).
 * @return EXIT_SUCCESS if the insertion is successful, otherwise EXIT_FAILURE.
 */
int latin_square_insert(LatinSquare *latin_square, int const row, int const column, int const value);

/**
 * @brief Clears a specific cell of a Latin square.
 *
 * Ensures that the cell is mutable before clearing its value.
 *
 * @param latin_square Pointer to the Latin square.
 * @param row The row index of the cell (0-based).
 * @param column The column index of the cell (0-based).
 * @return EXIT_SUCCESS if the operation is successful, otherwise EXIT_FAILURE.
 */
int latin_square_clear(LatinSquare *latin_square, int const row, int const column);

/**
 * @brief Solves a Latin square.
 *
 * Attempts to fill the Latin square with values such that the conditions of a Latin square are met.
 * Uses backtracking to find a solution.
 *
 * @param latin_square Pointer to the Latin square to solve.
 * @return EXIT_SUCCESS if the square is successfully solved, otherwise EXIT_FAILURE.
 */
int latin_square_solve(LatinSquare *latin_square);

/**
 * @brief Prints the Latin square to the standard output.
 *
 * Displays the Latin square in a formatted grid. Fixed cells are shown as negative values.
 *
 * @param latin_square Pointer to the Latin square to print.
 * @return EXIT_SUCCESS if the operation is successful, otherwise EXIT_FAILURE.
 */
int latin_square_print(LatinSquare *const latin_square);

#endif // LATIN_SQUARE_H
