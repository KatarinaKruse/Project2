# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable
TARGET = mt-collatz

# Build rule
$(TARGET): mt-collatz.cpp
	$(CXX) $(CXXFLAGS) mt-collatz.cpp -o $(TARGET) -pthread

# Data files produced by runs
DATA_FILES = histogram_locked.csv histogram_nolock.csv \
             timing_locked.csv timing_nolock.csv \
             timing_locked_manyT.csv timing_locked_avg.csv \
			 tmp_locked.csv timing_nolock_manyT.csv \
             timing_all.csv histogram_diff.csv

# Clean rule
clean:
	rm -f $(TARGET) $(DATA_FILES)

.PHONY: clean