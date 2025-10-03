# ===== Connect-4 Makefile =====
CC      := gcc
STD     := -std=c11
WARN    := -Wall -Wextra -Wpedantic
OPT     := -O2
DBG     := -g
CFLAGS  := $(STD) $(WARN) $(OPT) $(DBG)
LDFLAGS :=

SRC     := src/main.c src/board.c src/game.c
OBJ     := $(SRC:.c=.o)
DEP     := $(OBJ:.o=.d)
BIN     := connect4

.PHONY: all run debug release valgrind clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# Pattern rule with dep generation (-MMD -MP)
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(BIN)
	./$(BIN)

debug: CFLAGS := $(STD) $(WARN) -O0 -g
debug: clean all

release: CFLAGS := $(STD) $(WARN) -O2
release: clean all

valgrind: $(BIN)
	valgrind --leak-check=full ./$(BIN)

clean:
	rm -f $(OBJ) $(DEP) $(BIN)

# Include auto-generated header deps if present
-include $(DEP)
