# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable
TARGET = mt-collatz

# Build rule
$(TARGET): mt-collatz.cpp
	$(CXX) $(CXXFLAGS) mt-collatz.cpp -o $(TARGET) -pthread

# Clean rule
clean:
	rm -f $(TARGET)