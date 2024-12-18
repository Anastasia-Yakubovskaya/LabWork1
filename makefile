TARGET = BMPProcessing 

CXX = g++ 

CXXFLAGS = -I. -std=c++17 -g -fPIC -Wall -Werror -Wpedantic -O2 

SRCS = main.cpp bmp.cpp 

OBJS = $(SRCS:.cpp=.o) 

all: $(TARGET) 

$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $^ 
	
%.o: %.cpp bmp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
	
clean: 
	rm -f $(OBJS) $(TARGET) 
	
.PHONY: all clean

