# Author: Nuno Poza

# Compiler
CC = gcc

# Compiling flags
CFLAGS = -Wall -Wextra -std=c11 -O2

# Source files
SRC = src/main.c src/hashtable.c src/webserver.c
HDR = src/hashtable.h src/webserver.h

TARGET = hash_table

DATA = data/98-0.txt

SIZE = 100003

# Default target: compile the executable
$(TARGET): $(SRC) $(HDR)
	@echo "Compiling $(TARGET)..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo " Compilation finished."

# Run the program with the dataset
run: $(TARGET)
	@echo "Running program with dataset..."
	./$(TARGET) $(SIZE) $(DATA)
	@echo "Execution finished."

# Remove compiled binaries
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
	@echo "Cleanup done."