# Compiler 
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Directories 
SRC_DIR := src
BIN_DIR := bin

# Source files
SRCS := \
$(SRC_DIR)/main.cpp \
$(SRC_DIR)/memory_manager.cpp \
$(SRC_DIR)/allocator/first_fit.cpp \
$(SRC_DIR)/allocator/best_fit.cpp \
$(SRC_DIR)/allocator/worst_fit.cpp \
$(SRC_DIR)/allocator/buddy_allocator.cpp \
$(SRC_DIR)/cache/cache.cpp

# Output 
TARGET := $(BIN_DIR)/memsim

# Default target 
all: $(TARGET)

# Link 
$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)
	@echo "Build successful: $(TARGET)"

# Clean 
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean