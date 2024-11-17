#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "latin_square.h"

/**
 * @brief Reads a Latin square from a file and initializes the given LatinSquare structure.
 *
 * This function reads a Latin square from a specified file, parses the square's size, 
 * and inserts the values row by row into the given LatinSquare structure.
 *
 * The expected format of the file:
 * - The first line contains an integer indicating the size of the Latin square.
 * - Subsequent lines contain the values of the Latin square, with each value separated by spaces. 
 *   Values can be negative integers as well.
 * - The file should not contain any extra data beyond the square.
 *
 * @param file_name A string representing the name of the file to read the Latin square from.
 * @param latin_square A pointer to a pointer of a LatinSquare structure where the data will be stored.
 * @return EXIT_SUCCESS if the file is successfully read and the Latin square is initialized.
 * @return EXIT_FAILURE if an error occurs during file reading or parsing.
 */
int read_latin_square(char *const file_name, LatinSquare **latin_square);

#endif // FILE_HANDLER_H
