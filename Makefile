# Project name
PROJ = latinsolver

CC = gcc
C_FLAGS = -std=c99 -Wall -O -Wuninitialized -Wunreachable-code -Wno-unused-result -pedantic
L_FLAGS = -lm

# Doxygen
DOXYGEN = doxygen

# Direcotires
BUILD_DIR = build

# Source files
NODE_SRC = node.c
LATIN_SQUARE_SRC = latin_square.c
STACK_SRC = stack.c
FILE_HANDLER_SRC = file_handler.c
MAIN_SRC = main.c

# Object files
NODE_OBJ = ${BUILD_DIR}/node.o
LATIN_SQUARE_OBJ = ${STACK_OBJ} ${BUILD_DIR}/latin_square.o
STACK_OBJ = ${NODE_OBJ} ${BUILD_DIR}/stack.o
FILE_HANDLER_OBJ = ${LATIN_SQUARE_OBJ} ${BUILD_DIR}/file_handler.o
MAIN_OBJ = ${FILE_HANDLER_OBJ} ${BUILD_DIR}/main.o

# Define the default target
${PROJ}: clean ${BUILD_DIR} ${MAIN_OBJ}
	$(CC) $(L_FLAGS) ${C_FLAGS} -o ${PROJ} ${MAIN_OBJ}

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile object files
${BUILD_DIR}/node.o: ${NODE_SRC}
	$(CC) ${C_FLAGS} -c ${NODE_SRC} -o ${BUILD_DIR}/node.o

${BUILD_DIR}/stack.o: ${STACK_SRC}
	$(CC) ${C_FLAGS} -c ${STACK_SRC} -o ${BUILD_DIR}/stack.o

${BUILD_DIR}/latin_square.o: ${LATIN_SQUARE_SRC}
	$(CC) ${C_FLAGS} -c ${LATIN_SQUARE_SRC} -o ${BUILD_DIR}/latin_square.o

${BUILD_DIR}/file_handler.o: ${FILE_HANDLER_SRC}
	$(CC) ${C_FLAGS} -c ${FILE_HANDLER_SRC} -o ${BUILD_DIR}/file_handler.o

${BUILD_DIR}/main.o: ${MAIN_SRC}
	$(CC) ${C_FLAGS} -c ${MAIN_SRC} -o ${BUILD_DIR}/main.o

# Targets to build individual executables
node: clean
	${CC} ${C_FLAGS} $(L_FLAGS) -o debug_node -DDEBUG_NODE node.c latin_square.c stack.c

stack: clean
	${CC} ${C_FLAGS} $(L_FLAGS) -o debug_stack -DDEBUG_STACK node.c latin_square.c stack.c

latin_square: clean ${BUILD_DIR} ${LATIN_SQUARE_OBJ}
	$(CC) ${C_FLAGS} -c ${LATIN_SQUARE_SRC} -DDEBUG_LATIN_SQUARE -o ${BUILD_DIR}/latin_square.o
	$(CC) $(L_FLAGS) ${C_FLAGS} -o debug_latin_square ${LATIN_SQUARE_OBJ}

file_handler: clean ${BUILD_DIR} ${FILE_HANDLER_OBJ}
	$(CC) ${C_FLAGS} -c ${FILE_HANDLER_SRC} -DDEBUG_FILE_HANDLER -o ${BUILD_DIR}/file_handler.o
	$(CC) $(L_FLAGS) ${C_FLAGS} -o debug_file_handler ${FILE_HANDLER_OBJ}

# Check for any memory leaks on the specified executable
memory:
	valgrind --leak-check=full \
			--show-leak-kinds=all \
         	--track-origins=yes \
         	--verbose \
        	--log-file=valgrind.txt \
        	./$(EXECUTABLE)

# Generate docs
docs:
	doxygen {DOXYGEN}.conf

# Clean up build files and executables
clean:
	rm -rf html ${BUILD_DIR} ${PROJ} debug_node debug_stack debug_latin_square debug_file_handler valgrind.txt