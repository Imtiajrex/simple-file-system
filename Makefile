# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source directory
SRC_DIR = src

# Output directory
OUT_DIR = build

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/filesystem.c \
       $(SRC_DIR)/file_operations.c \
       $(SRC_DIR)/file_utils.c \
       $(SRC_DIR)/search_filter.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

# Executable name
EXEC = $(OUT_DIR)/filesystem

# Default target
all: $(OUT_DIR) $(EXEC)

# Create output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Link object files
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OUT_DIR)

# Phony targets
.PHONY: all clean