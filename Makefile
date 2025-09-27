# ===== Connect-4 Makefile (Sprint 1) =====
CC      := gcc
WARN    := -Wall -Wextra -Wpedantic
OPT     := -O2
DBG     := -g
CFLAGS  := $(WARN) $(OPT) $(DBG)
LDFLAGS :=

# If your .c files live in the repo root:
SRC := main.c board.c game.c
# If they live under src/, use this instead:
# SRC := src/main.c src/board.c src/game.c

OBJ := $(SRC:.c=.o)
BIN := connect4

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

# Debug build (1)
debug: CFLAGS := $(WARN) -O0 -g
debug: clean all

# Release build (2)
release: CFLAGS := $(WARN) -O2
release: clean all

# Valgrind memory check (required by spec)
valgrind: $(BIN)
	valgrind --leak-check=full ./$(BIN)

# Cleanup
clean:
	rm -f $(OBJ) $(BIN)
