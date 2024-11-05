# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = bmp_program
SRC = main.cpp BMPReader.cpp BMPWriter.cpp
OBJ = $(SRC:.cpp=.o)&lt;br&gt;&lt;br&gt;# Default target to build the program&lt;br&gt;all: $(TARGET)

# Build the target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $&lt; -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
