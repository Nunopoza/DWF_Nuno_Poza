# Makefile - Part 2: Binance API Parser (C)
# Author: Nuno Poza

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# External libraries (libcurl + cJSON)
LIBS = -lcurl -lcjson

# Source and header files
SRC = src/main.c src/api.c src/parser.c src/webserver.c
HDR = src/api.h src/parser.h src/timer.h

# Executable name
TARGET = binance_api

# Build rules
#################

# Default rule: build the executable
$(TARGET): $(SRC) $(HDR)
	@echo "Compiling $(TARGET)..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)
	@echo "Build completed."

# Run the program with Binance API (fetch and parse)
run: $(TARGET)
	@echo "Running Binance API parser..."
	./$(TARGET)
	@echo "Execution finished."

# Clean compiled binaries
clean:
	@echo "Cleaning build files..."
	rm -f $(TARGET)
	@echo "Cleanup done."