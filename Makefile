CC = gcc
CFLAGS = -Wall -g
run: main.o board.o game.o
	$(CC) $(CFLAGS) -o run main.o board.o game.o

main.o: main.c board.h game.h
	$(CC) $(CFLAGS) -c main.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

clean:
	rm -rf *.o run