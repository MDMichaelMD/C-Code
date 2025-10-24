# Compiler and flags
CC = gcc
CFLAGS = -O2 -fopenmp -std=c99

# Target executable
TARGET = pso

# Build target
$(TARGET): pso.c
	$(CC) $(CFLAGS) -o $@ $^

# Clean target
.PHONY: clean
clean:
	rm -f $(TARGET)
