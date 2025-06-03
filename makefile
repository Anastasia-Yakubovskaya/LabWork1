TARGET = BMPProcessing

CXX = g++

CXXFLAGS = -I./include -std=c++17 -Wall -Wextra -Wpedantic -O3 -march=native -fopenmp
LDFLAGS = -fopenmp

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
DOCS_DIR = docs

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Основная сборка
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/bmp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(DOCS_DIR)

docs:
	doxygen Doxyfile

.PHONY: all clean docs
