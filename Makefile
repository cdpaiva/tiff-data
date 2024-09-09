SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objs

CFLAGS = -Wall -Wextra -I$(SRC_DIR) -I$(UNITY_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

EXEC = $(BUILD_DIR)/tiff_data

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# # Compiler
# CC = gcc
#
# # Directories
# SRC_DIR = src
# TEST_DIR = test
# UNITY_DIR = unity
# BUILD_DIR = build
# OBJ_DIR = $(BUILD_DIR)/objs
#
# # Flags
# CFLAGS = -Wall -Wextra -I$(SRC_DIR) -I$(UNITY_DIR)
#
# # Source files
# SRCS = $(wildcard $(SRC_DIR)/*.c)
# TEST_SRCS = $(wildcard $(TEST_DIR)/test*.c)
# UNITY_SRC = $(UNITY_DIR)/unity.c
#
# # Executable names
# EXEC = $(BUILD_DIR)/tiff_data
# TEST_EXEC = $(BUILD_DIR)/test_runner
#
# # Object files
# OBJS = $(SRCS:.c=.o)
# # OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# #
# TEST_OBJS = $(TEST_SRCS:.c=.o)
# # TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))
# # TEST_OBJS = $(TEST_SRCS:%=$(BUILD_DIR)/*.o)
# #
# #
# # Default target
# all: build
#
# # Build command
# build: $(EXEC)
#
# $(EXEC): $(OBJS)
# 	printf $(OBJS)
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
#
# # Test command
# test: $(TEST_EXEC)
# 	./$(TEST_EXEC)
#
# FILTERED_SRCS = $(filter-out src/main.c, $(SRCS))
# $(info $(BUILD_DIR))
# $(TEST_EXEC): $(TEST_SRCS) $(UNITY_SRC) $(FILTERED_SRCS)
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(CFLAGS) $(TEST_SRCS) $(UNITY_SRC) $(FILTERED_SRCS) -o $(TEST_EXEC)
#
# # Clean command
# clean:
# 	rm -rf $(BUILD_DIR)/*.o $(EXEC) $(TEST_EXEC)
#
