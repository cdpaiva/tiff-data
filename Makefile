# Compiler
CC = gcc

# Directories
SRC_DIR = src
TEST_DIR = test
UNITY_DIR = unity
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objs

# Flags
CFLAGS = -Wall -Wextra -I$(SRC_DIR) -I$(UNITY_DIR)

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/test*.c)
UNITY_SRC = $(UNITY_DIR)/unity.c

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))

# Executables
EXEC = $(BUILD_DIR)/tiff_data
TEST_EXEC = $(BUILD_DIR)/test_runner

# Default target: build the executable
build: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Workaround until I setup the tests properly
FILTERED_SRCS = $(filter-out src/main.c, $(SRCS))
$(TEST_EXEC): $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(FILTERED_SRCS) $(UNITY_SRC) -o $(TEST_EXEC)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(UNITY)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
