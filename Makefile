# ===== Connect-4 Makefile =====
CC      := gcc
WARN    := -Wall -Wextra -Wpedantic
OPT     := -O2
DBG     := -g
CFLAGS  := $(WARN) $(OPT) $(DBG)
LDFLAGS :=

SRC     := main.c board.c game.c
OBJ     := $(SRC:.c=.o)
BIN     := connect4

.PHONY: all run debug release valgrind clean

# Default build
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# Generic compile rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the game
run: $(BIN)
	./$(BIN)

# Debug build (no optimization)
debug: CFLAGS = $(WARN) -O0 -g
debug: clean all

# Release build (optimized)
release: CFLAGS = $(WARN) -O2
release: clean all

# Memory check (valgrind)
valgrind: $(BIN)
	valgrind --leak-check=full ./$(BIN)

# Cleanup
clean:
	rm -f $(OBJ) $(BIN)
