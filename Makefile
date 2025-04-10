# Makefile for building and cleaning the project

# Variables
BUILD_DIR = build

# Default target
all: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean target
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
