# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -g

# Executable
TARGET = dungeon_game

# Source files
SRC = main.c

# Build rules
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)

