# Project name
PROJ = latinsolver

CC = gcc
C_FLAGS = -std=c99 -Wall -O -Wuninitialized -Wunreachable-code -pedantic
L_FLAGS = -lm

# Doxygen
DOXYGEN = doxygen

# Direcotires
BUILD_DIR = build

# Source files
NODE_SRC = single_node.c
STACK_SRC = stack.c
MAIN_SRC = main.c

# Object files
NODE_OBJ = ${BUILD_DIR}/node.o
STACK_OBJ = ${NODE_OBJ} ${BUILD_DIR}/stack.o
MAIN_OBJ = ${BUILD_DIR}/main.o

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

${BUILD_DIR}/main.o: ${MAIN_SRC}
	$(CC) ${C_FLAGS} -c ${MAIN_SRC} -o ${BUILD_DIR}/main.o

# Targets to build individual executables
node: clean ${BUILD_DIR} ${NODE_OBJ}
	$(CC) ${C_FLAGS} -c ${NODE_SRC} -DDEBUG_NODE -o ${NODE_OBJ}
	$(CC) $(L_FLAGS) ${C_FLAGS} -o debug_node ${NODE_OBJ}

stack: clean ${BUILD_DIR} ${STACK_OBJ}
	$(CC) ${C_FLAGS} -c ${STACK_SRC} -DDEBUG_STACK -o ${STACK_OBJ}
	$(CC) $(L_FLAGS) ${C_FLAGS} -o debug_stack ${STACK_OBJ}

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
	rm -rf html ${BUILD_DIR} ${PROJ} debug_node debug_stack